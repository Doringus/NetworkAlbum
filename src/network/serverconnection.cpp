#include "serverconnection.h"

#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QImage>

#include "../network/networkactiontypes.h"
#include "../base/dispatcher.h"
#include "../base/action.h"
#include "../action/actiontypes.h"

ServerConnection::ServerConnection(QObject *parent) : TcpConnection(parent) {
    connect(this, &ServerConnection::messageReady, this, &ServerConnection::handleMessage);
    connect(this, &ServerConnection::connected, this, &ServerConnection::sendAuth);
    connect(this, &ServerConnection::disconnected, this, &ServerConnection::onDisconnected);
}

void ServerConnection::connectToServer(QString ip, int port, bool reconnect) {
    m_Reconnect = reconnect;
    if(m_Reconnect) {
        m_Socket->disconnectFromHost();
    }
    m_Socket->connectToHost(ip, port);
    if(!m_Socket->waitForConnected()) {
        QSharedPointer<Action> action(new Action(ActionType::CLIENT_CONNECTED));
        action->setErrorString("Не удалось подключиться к серверу. Проверьте интернет соединение");
        Dispatcher::get().dispatch(action);
    }
}

void ServerConnection::setScaled(bool scaled) {
    m_Scaled = scaled;
}

void ServerConnection::setId(const QString &id) {
    m_Id = id;
}

void ServerConnection::sendSyncData(const QList<QPair<QString, QString>>& data) {
    qDebug() << "Sending synch data" << data;
    QJsonObject messageObject;
    messageObject.insert("MessageType", static_cast<int>(NetworkActionTypes::SYNC));
    QJsonArray images;
    foreach(QPair changes, data) {
        QJsonObject change;
        change.insert("NewPath", changes.first);
        change.insert("OldPath", changes.second);
        images.append(change);
    }
    messageObject.insert("MessageValue", images);
    sendMessage(QJsonDocument(messageObject).toJson(QJsonDocument::Compact));
}

void ServerConnection::sendChatMessage(const QString& message) {
    sendMessage(QJsonDocument(createMessage(static_cast<int>(NetworkActionTypes::CONVERSATION), message))
                .toJson(QJsonDocument::Compact));
}

void ServerConnection::handleMessage(const QString &message) {
    QJsonObject messageObject = QJsonDocument::fromJson(message.toUtf8()).object();
    int type = messageObject.value("MessageType").toInt();
    QJsonValue messageValue = messageObject.value("MessageValue");
    switch (static_cast<NetworkActionTypes>(type)) {
        case NetworkActionTypes::AUTHORIZATION: {
            onAuth(messageValue.toBool());
            break;
        }
        case NetworkActionTypes::ALBUM_IMAGES: {
            Dispatcher::get().dispatch(new Action(ActionType::IMAGES_RECEIVED, QVariant::fromValue<QJsonObject>(messageObject)));
            break;
        }
        case NetworkActionTypes::CONVERSATION: {
             Dispatcher::get().dispatch(new Action(ActionType::RECEIVE_MESSAGE, messageValue.toString()));
             break;
        }
        case NetworkActionTypes::DISCONNECT: {
            emit sessionClosed();
            break;
        }
    }
}

void ServerConnection::sendAuth() {
        sendMessage(QJsonDocument(createMessage(static_cast<int>(NetworkActionTypes::AUTHORIZATION), m_Id))
                                    .toJson(QJsonDocument::Compact));
}

void ServerConnection::onDisconnected() {
    if(m_Auth) {
        Dispatcher::get().dispatch(new Action(ActionType::CLIENT_DISCONNECTED));
    }
}

void ServerConnection::onAuth(bool auth) {
    if(!auth) {
        QSharedPointer<Action> action(new Action(ActionType::CLIENT_CONNECTED));
        action->setErrorString("Не удалось подключиться к альбому");
        Dispatcher::get().dispatch(action);
    } else if(!m_Reconnect){
        m_Auth = true;
        sendMessage(QJsonDocument(createMessage(static_cast<int>(NetworkActionTypes::ALBUM_IMAGES), m_Scaled))
                                    .toJson(QJsonDocument::Compact));
    } else {
        Dispatcher::get().dispatch(new Action(ActionType::HIDE_RECONNECT_POPUP));
    }
}

QJsonObject ServerConnection::createMessage(int type, const QJsonValue &value) {
    QJsonObject object;
    object.insert("MessageType", type);
    object.insert("MessageValue", value);
    return object;
}
