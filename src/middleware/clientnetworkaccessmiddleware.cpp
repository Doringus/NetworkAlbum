#include "clientnetworkaccessmiddleware.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include "../action/actiontypes.h"
#include "../base/action.h"
#include "../network/networkactiontypes.h"
#include "../base/dispatcher.h"

ClientNetworkAccessMiddleware::ClientNetworkAccessMiddleware(QObject *parent) : QObject(parent) {
    m_ServerConnection = new ServerConnection(this);
    connect(m_ServerConnection, &TcpConnection::messageReady, this, &ClientNetworkAccessMiddleware::onReceiveMessage);
}

QSharedPointer<Action> ClientNetworkAccessMiddleware::process(const QSharedPointer<Action> &action) {
    switch(action->getType<ActionType>()) {
        case ActionType::CONNECT_TO_ALBUM: {
            QPair<QString, bool> data = action->getData<QPair<QString, bool>>();
            processConnectToAlbum(data.first, data.second);
            break;
        }
        case ActionType::SEND_SYNC_DATA: {
            processSendSyncData(action->getData<QList<QPair<QString, QString>>>());
        }
        case ActionType::SEND_MESSAGE: {
            processSendMessage(action->getData<QString>());
        }
    }
    return action;
}

void ClientNetworkAccessMiddleware::onReceiveMessage(QString message) {
    qDebug() << this << message;
    QJsonObject messageObject = QJsonDocument::fromJson(message.toUtf8()).object();
    int type = messageObject.value("MessageType").toInt();
    QJsonValue messageValue = messageObject.value("MessageValue");
    switch (static_cast<NetworkActionTypes>(type)) {
        case NetworkActionTypes::AUTHORIZATION: {
            processAuth(messageValue.toBool());
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
    }
}

void ClientNetworkAccessMiddleware::processConnectToAlbum(QString link, bool scaled) {
    QStringList parts = link.split(':');
    m_ServerConnection->connectToServer(parts.first(), 22222);
    m_Scaled = scaled;
    connect(m_ServerConnection, &ServerConnection::connected, this, [=](){
        QJsonObject messageObject;
        messageObject.insert("MessageType", static_cast<int>(NetworkActionTypes::AUTHORIZATION));
        messageObject.insert("MessageValue", parts.at(1));
        messageObject.insert("Scaled", scaled);
        m_ServerConnection->sendMessage(QJsonDocument(messageObject).toJson(QJsonDocument::Compact));
    });
}

void ClientNetworkAccessMiddleware::processSendSyncData(QList<QPair<QString, QString>> data) {
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
    m_ServerConnection->sendMessage(QJsonDocument(messageObject).toJson(QJsonDocument::Compact));
}

void ClientNetworkAccessMiddleware::processAuth(bool auth) {
    if(!auth) {

    } else {
        m_ServerConnection->sendMessage(QJsonDocument(createMessage(static_cast<int>(NetworkActionTypes::ALBUM_IMAGES), m_Scaled))
                                    .toJson(QJsonDocument::Compact));
    }
}

QJsonObject ClientNetworkAccessMiddleware::createMessage(int type, const QJsonValue &value) {
    QJsonObject object;
    object.insert("MessageType", type);
    object.insert("MessageValue", value);
    return object;
}

void ClientNetworkAccessMiddleware::processSendMessage(const QString &message) {
    m_ServerConnection->sendMessage(QJsonDocument(createMessage(static_cast<int>(NetworkActionTypes::CONVERSATION), message))
                                    .toJson(QJsonDocument::Compact));
}
