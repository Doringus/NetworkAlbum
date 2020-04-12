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
    connect(m_ServerConnection, &TcpConnection::messageReady, this, &ClientNetworkAccessMiddleware::onRecieveMessage);
}

QSharedPointer<Action> ClientNetworkAccessMiddleware::process(const QSharedPointer<Action> &action) {
    switch(action->getType<ActionType>()) {
        case ActionType::CONNECT_TO_ALBUM: {
            processConnectToAlbum("TEST");
            break;
        }
    }
    return action;
}

void ClientNetworkAccessMiddleware::onRecieveMessage(QString message) {
    QJsonObject obj = QJsonDocument::fromJson(message.toUtf8()).object();
    QJsonArray images = obj.value("Images").toArray();
    Dispatcher::get().dispatch(new Action(ActionType::IMAGES_RECIEVED, QVariant::fromValue<QJsonObject>(obj)));
}

void ClientNetworkAccessMiddleware::processConnectToAlbum(QString link) {
    m_ServerConnection->connectToServer("192.168.0.3", 22222);
    connect(m_ServerConnection, &ServerConnection::connected, this, [=](){
        qDebug() << "Connected to album";
        QJsonObject messageObject;
        messageObject.insert("MessageType", static_cast<int>(NetworkActionTypes::AUTHORIZATION));
        messageObject.insert("MessageValue", link);
        m_ServerConnection->sendMessage(QJsonDocument(messageObject).toJson(QJsonDocument::Compact));
    });
}
