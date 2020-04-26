#include "albumclient.h"

#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

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

void AlbumClient::sendMessage(const QString& message) {
    qDebug() << this << "Sending message";
    QByteArray buf;
    QDataStream out(&buf, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_13);
    out << message;
    m_Socket->write(buf);
    m_Socket->flush();
}

QJsonObject AlbumClient::createMessage(int type, const QJsonValue &value) {
    QJsonObject object;
    object.insert("MessageType", type);
    object.insert("MessageValue", value);
    return object;
}

bool AlbumClient::scaled() {
    return m_Scaled;
}

void AlbumClient::setAuth(bool auth) {
    sendMessage(QJsonDocument(createMessage(static_cast<int>(NetworkActionTypes::AUTHORIZATION), auth))
                                            .toJson(QJsonDocument::Compact));
    if(!auth) {
        disconnectClient();
    } else {
        m_HasAuth = auth;
    }
}

void AlbumClient::sendImages(const QList<QJsonObject>& images) {
    QJsonArray jsonImages;
    foreach(QJsonObject imageJson, images) {
        jsonImages << imageJson;
    }
    sendMessage(QJsonDocument(createMessage(static_cast<int>(NetworkActionTypes::ALBUM_IMAGES), jsonImages))
                .toJson(QJsonDocument::Compact));
}

void AlbumClient::sendConversation(const QString &message) {
    sendMessage(QJsonDocument(createMessage(static_cast<int>(NetworkActionTypes::CONVERSATION), message))
                .toJson(QJsonDocument::Compact));
}

void AlbumClient::sendCloseSession() {
    sendMessage(QJsonDocument(createMessage(static_cast<int>(NetworkActionTypes::DISCONNECT), ""))
                .toJson(QJsonDocument::Compact));
    m_Socket->disconnect();
    deleteLater();
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
    disconnectClient();
}

void AlbumClient::disconnectClient() {
    m_Socket->disconnect();
    if(m_HasAuth) {
        emit disconnected(m_Link);
    }
    deleteLater();
}

void AlbumClient::handleMessage(const QString& message) {
    QJsonDocument messageDocument = QJsonDocument::fromJson(message.toUtf8());
    if(messageDocument.isNull()) {
        disconnectClient();
    }
    QJsonObject messageObject = messageDocument.object();
    int type = messageObject.value("MessageType").toInt();
    qDebug() << this << "Received message" << messageObject;
    if(m_HasAuth) {
        switch (static_cast<NetworkActionTypes>(type)) {
            case NetworkActionTypes::SYNC: {
                emit syncImages(m_Link, messageObject.value("MessageValue").toVariant());
                break;
            }
            case NetworkActionTypes::ALBUM_IMAGES: {
                emit imagesRequired(m_Link, messageObject.value("MessageValue").toBool());
                break;
            }
            case NetworkActionTypes::CONVERSATION: {
                emit conversationReceived(m_Link, messageObject.value("MessageValue").toString());
                break;
            }
        }
    } else {
        if(static_cast<NetworkActionTypes>(type) != NetworkActionTypes::AUTHORIZATION) {
            disconnectClient();
        }
        m_Link = messageObject.value("MessageValue").toString();
        emit authorizationRequired(m_Link, this);
    }
}
