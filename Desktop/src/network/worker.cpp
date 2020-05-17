#include "worker.h"

#include <QDebug>
#include "albumclient.h"
#include "networkactiontypes.h"

/*Worker::Worker(QObject *parent, int index) : QObject(parent),
                                     m_Index(index) {

}

void Worker::addClientConnection(AlbumClient *client) {
    //client->moveToThread(this->thread());
    connect(client, &AlbumClient::authorizationRequired, this, &Worker::onAuthClient);
    connect(client, &AlbumClient::messageReceived, this, &Worker::onClientMessage);
}

void Worker::sendMessage(QString link, QString message) {
    AlbumClient *client = m_Clients.value(link, nullptr);
    if(client != nullptr) {
        m_Clients.value(link)->sendMessage(message);
    }
}

void Worker::onAuthClient(QString link) {

}

void Worker::onClientMessage(QString link, int type, QVariant message) {
    switch (static_cast<NetworkActionTypes>(type)) {
        case NetworkActionTypes::SYNC: {
            emit syncImages(link, m_Index, message);
            break;
        }
    }
}

void Worker::onClientDisconnected(QString clientLink) {
    m_Clients.remove(clientLink);
}
*/
