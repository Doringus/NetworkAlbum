#include "albumclient.h"

#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

#include "networkactiontypes.h"

AlbumClient::AlbumClient(QObject *parent, quintptr descriptor) : QObject(parent) {
    m_HasAuth = false;
    m_Socket = new QTcpSocket(this);
    if(!m_Socket->setSocketDescriptor(descriptor)) {
        qDebug() << "FAILED TO SET SOCKET" << this;
    }
    connect(m_Socket, &QTcpSocket::readyRead, this, &AlbumClient::onReadyRead);
    connect(m_Socket, &QTcpSocket::connected, this, &AlbumClient::onConnected);
    connect(m_Socket, &QTcpSocket::disconnected, this, &AlbumClient::onDisconnected);
    m_IncomingMessage.setDevice(m_Socket);
    m_IncomingMessage.setVersion(QDataStream::Qt_5_13);
}

void AlbumClient::sendMessage(QString message) {
    qDebug() << this << "Sending message";
    QByteArray buf;
    QDataStream out(&buf, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_13);
    out << message;
    m_Socket->write(buf);
    m_Socket->flush();
}

void AlbumClient::onReadyRead() {
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if(socket == nullptr) {
        return;
    }
    m_Socket->waitForBytesWritten();
    QString message;
    m_IncomingMessage.startTransaction();
    m_IncomingMessage >> message;
    if(!m_IncomingMessage.commitTransaction()) {
        return;
    }
    handleMessage(message);
}

void AlbumClient::onConnected() {
}

void AlbumClient::onDisconnected() {

}

void AlbumClient::disconnectClient() {

}

void AlbumClient::handleMessage(QString message) {
    qDebug() << this << "Recieved message";
    QJsonDocument messageDocument = QJsonDocument::fromJson(message.toUtf8());
    if(messageDocument.isNull()) {
        disconnectClient();
    }
    QJsonObject messageObject = messageDocument.object();
    int type = messageObject.value("MessageType").toInt();
    if(m_HasAuth) {
        emit messageRecieved(type, messageObject.value("MessageValue").toVariant());
    } else {
        if(static_cast<NetworkActionTypes>(type) != NetworkActionTypes::AUTHORIZATION) {
            disconnectClient();
        }
        emit authorizationRequired(messageObject.value("MessageValue").toString());
    }
}
