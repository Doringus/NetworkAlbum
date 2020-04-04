#include "worker.h"

#include <QDebug>

#include "albumlinkfactory.h"
#include "albumclient.h"

Worker::Worker(QObject *parent, AlbumLinkFactory *factory, int index) : QObject(parent),
                                    m_AlbumLinkFactory(factory), m_Index(index) {

}

void Worker::addClientConnection(qintptr descriptor) {
    AlbumClient *client = new AlbumClient(this, descriptor);
    connect(client, &AlbumClient::authorizationRequired, this, &Worker::onAuthClient);
}

void Worker::sendMessage(QString link, QString message) {
    qDebug() << this << "Sending message" << message;
    AlbumClient *client = m_Clients.value(link, nullptr);
    if(client != nullptr) {
        m_Clients.value(link)->sendMessage(message);
    }
}

void Worker::onAuthClient(QString link) {
    AlbumClient *client = qobject_cast<AlbumClient*>(sender());
    bool result = QMetaObject::invokeMethod(m_AlbumLinkFactory, "availableLink", Qt::BlockingQueuedConnection,
                                            Q_RETURN_ARG(bool,result), Q_ARG(QString, link));
    if(result) {
        qDebug() << "Auth completed";
        m_Clients.insert(link, client);
        emit clientConnected(link, m_Index);
    } else {
        qWarning() << "Auth failed" << client;
        client->disconnectClient();
        client->deleteLater();
    }
}

void Worker::onClientMessage(int type, QVariant message) {

}

void Worker::onClientDisconnected(QString clientLink) {
    m_Clients.remove(clientLink);
}
