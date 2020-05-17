#include "server.h"

#include <QThread>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDataStream>
#include <QJsonArray>
#include <QImage>
#include <QImageIOHandler>

#include "worker.h"
#include "networkactiontypes.h"
#include "albumclient.h"
#include "../base/dispatcher.h"
#include "../action/actiontypes.h"

Server::Server(QObject *parent) : QTcpServer(parent) {
    for(int i = 0; i < THREAD_COUNT; ++i) {
        QThread *thread = new QThread(this);
        m_Threads.append(thread);
        thread->start();
    }
}

Server::~Server() {
    foreach(QThread *thread, m_Threads) {
        thread->quit();
        thread->wait();
    }
}

void Server::incomingConnection(qintptr descriptor) {
    QThread *thread = m_Threads.at(m_QueueNumber % THREAD_COUNT);
    AlbumClient *client = new AlbumClient(nullptr, descriptor);
    connect(client, &AlbumClient::authorizationRequired, this, &Server::onAuthClient, Qt::QueuedConnection);
    connect(client, &AlbumClient::imagesRequired, this, &Server::onClientNeedImages, Qt::QueuedConnection);
    connect(client, &AlbumClient::syncImages, this, &Server::onSyncImages, Qt::QueuedConnection);
    connect(client, &AlbumClient::disconnected, this, &Server::onClientDisconnected, Qt::QueuedConnection);
    connect(client, &AlbumClient::conversationReceived, this, &Server::onClientChatMessage, Qt::QueuedConnection);
    connect(client, &AlbumClient::albumInfoRequired, this, &Server::onClientNeedAlbumInfo, Qt::QueuedConnection);
    client->moveToThread(thread);
    m_QueueNumber++;
}

void Server::addSessionLink(const QString& link) {
    m_Links.append(link);
}

void Server::removeSessionLink(int index) {
    if(m_Clients.contains(m_Links.at(index))) {
        QMetaObject::invokeMethod(m_Clients.value(m_Links.at(index)), "sendCloseSession", Qt::QueuedConnection);
        m_Clients.remove(m_Links.at(index));
    }
    m_Links.removeAt(index);
}

void Server::sendImages(const networkMessage_t& message) {
    qDebug() << "Sending images";
    QJsonObject messageObject;
    messageObject.insert("MessageType", static_cast<int>(NetworkActionTypes::ALBUM_IMAGES));
    QList<QJsonObject> images = message.data.value<QList<QJsonObject>>();
    QMetaObject::invokeMethod(m_Clients.value(message.clientLink), "sendImages", Qt::QueuedConnection,
                              Q_ARG(QList<QJsonObject>, images));
}

void Server::sendMessage(const networkMessage_t &message) {
    qDebug() << "Sending message" << message.clientLink << message.data;
    QMetaObject::invokeMethod(m_Clients.value(message.clientLink), "sendConversation", Qt::QueuedConnection,
                              Q_ARG(QString, message.data.toString()));
}

void Server::sendAlbumInfo(const networkMessage_t &message) {
    QPair<QString, int> data = message.data.value<QPair<QString, int>>();
    QMetaObject::invokeMethod(m_Clients.value(message.clientLink), "sendAlbumInfo", Qt::QueuedConnection,
                              Q_ARG(QString, data.first), Q_ARG(int, data.second));
}

void Server::onClientNeedImages(const QString& link, bool scaled) {
    networkMessage_t message;
    message.clientLink = link;
    message.data = scaled;
    Dispatcher::get().dispatch(new Action(ActionType::BEGIN_SEND_IMAGES, QVariant::fromValue(message)));
}

void Server::onAuthClient(const QString& link, AlbumClient *client) {
    qDebug() << "Auth client" << link << thread();
    if(m_Links.contains(link) && !m_Clients.contains(link)) {
        QMetaObject::invokeMethod(client, "setAuth", Qt::QueuedConnection, Q_ARG(bool, true));
        m_Clients.insert(link, client);
    } else {
        QMetaObject::invokeMethod(client, "setAuth", Qt::QueuedConnection, Q_ARG(bool, false));
    }
}

void Server::onClientChatMessage(const QString& link, const QString& message) {
    networkMessage_t networkMessage;
    networkMessage.clientLink = link;
    networkMessage.data = message;
    Dispatcher::get().dispatch(new Action(ActionType::RECEIVE_MESSAGE, QVariant::fromValue(networkMessage)));
}

void Server::onSyncImages(const QString& link, const QVariant& data) {
    networkMessage_t message;
    message.clientLink = link;
    message.data = data;
    Dispatcher::get().dispatch(new Action(ActionType::RECEIVE_SYNC_DATA, QVariant::fromValue(message)));
}

void Server::onClientDisconnected(const QString& link) {
    m_Clients.remove(link);
}

void Server::onClientNeedAlbumInfo(const QString &link) {
    networkMessage_t message;
    message.clientLink = link;
    Dispatcher::get().dispatch(new Action(ActionType::BEGIN_SEND_ALBUM_INFO, QVariant::fromValue(message)));
}



