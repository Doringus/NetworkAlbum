#include "clientnetworkaccessmiddleware.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMessageBox>
#include <QApplication>

#include "../action/actiontypes.h"
#include "../base/action.h"
#include "../network/networkactiontypes.h"
#include "../base/dispatcher.h"

ClientNetworkAccessMiddleware::ClientNetworkAccessMiddleware(QObject *parent) : QObject(parent) {
    m_ServerConnection = new ServerConnection(this);
    connect(m_ServerConnection, &ServerConnection::sessionClosed, this, &ClientNetworkAccessMiddleware::onServerClosedSession);
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
            break;
        }
        case ActionType::SEND_MESSAGE: {
            processSendMessage(action->getData<QString>());
            break;
        }
        case ActionType::RECONNECT_TO_ALBUM: {
            processReconnectToAlbum();
        }
    }
    return action;
}

void ClientNetworkAccessMiddleware::onServerClosedSession() {
    QMessageBox box;
    box.setText("Сессия закрыта");
    box.setInformativeText("Сервер закрыл сессию, дальнейшая работа невозможна. Все фотографии будут сохранены.");
    box.setIcon(QMessageBox::Warning);
    box.setStandardButtons(QMessageBox::Ok);
    box.exec();
    QApplication::quit();
}

void ClientNetworkAccessMiddleware::processConnectToAlbum(QString link, bool scaled) {
    QStringList parts = link.split(':');
    m_ServerConnection->setScaled(scaled);
    m_ServerConnection->setId(parts.at(1));
    m_Ip = parts.first();
    m_Port = 22222;
    m_ServerConnection->connectToServer(parts.first(), 22222, false);
    m_Scaled = scaled;
    m_Id = parts.at(1);
}

void ClientNetworkAccessMiddleware::processSendSyncData(QList<QPair<QString, QString>> data) {
    m_ServerConnection->sendSyncData(data);
}

void ClientNetworkAccessMiddleware::processSendMessage(const QString &message) {
    m_ServerConnection->sendChatMessage(message);
}

void ClientNetworkAccessMiddleware::processReconnectToAlbum() {
    m_ServerConnection->connectToServer(m_Ip, m_Port, true);
}
