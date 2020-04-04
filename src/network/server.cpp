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
#include "../base/dispatcher.h"
#include "../action/actiontypes.h"

Server::Server(QObject *parent, AlbumLinkFactory *factory) : QTcpServer(parent) {
    for(int i = 0; i < THREAD_COUNT; ++i) {
        QThread *thread = new QThread(this);
        Worker *worker = new Worker(nullptr, factory, i);
        worker->moveToThread(thread);
        connect(worker, &Worker::clientConnected, this, &Server::onClientConnected, Qt::QueuedConnection);
        connect(thread, &QThread::finished, worker, &QObject::deleteLater);
        m_Threads.append(thread);
        m_Workers.append(worker);
        thread->start();
    }
}

Server::~Server() {
    foreach(QThread *thread, m_Threads) {
        thread->quit();
        thread->wait();
    }
}

void Server::onClientConnected(QString link, int workerIndex) {
    networkMessage_t message;
    message.workerIndex = workerIndex;
    message.clientLink = link;
    Dispatcher::get().dispatch(new Action(ActionType::CLIENT_CONNECTED, QVariant::fromValue(message)));
}

void Server::sendImages(networkMessage_t message) {
    qDebug() << "Sending images";
    QJsonObject messageObject;
    messageObject.insert("MessageType", static_cast<int>(NetworkActionTypes::ALBUM_IMAGES));
    QList<QJsonObject> images = message.data.value<QList<QJsonObject>>();
    QJsonArray jsonImages;
    foreach(QJsonObject imageJson, images) {
        jsonImages << imageJson;
    }
    messageObject.insert("Images", jsonImages);
    Worker *worker = m_Workers.at(message.workerIndex);
    QMetaObject::invokeMethod(worker, "sendMessage", Qt::QueuedConnection,
                              Q_ARG(QString, message.clientLink),
                              Q_ARG(QString, QString(QJsonDocument(messageObject).toJson(QJsonDocument::Compact))));
}

void Server::incomingConnection(qintptr descriptor) {
    Worker *worker = m_Workers.at(m_QueueNumber % THREAD_COUNT);
    QMetaObject::invokeMethod(worker, "addClientConnection", Qt::QueuedConnection, Q_ARG(qintptr, descriptor));
    m_QueueNumber++;
}
