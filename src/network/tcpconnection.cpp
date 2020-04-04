#include "tcpconnection.h"

TcpConnection::TcpConnection(QObject *parent) : QObject(parent) {
    m_Socket = new QTcpSocket(this);
    connect(m_Socket, &QTcpSocket::readyRead, this, &TcpConnection::onReadyRead);
    connect(m_Socket, &QTcpSocket::connected, this, &TcpConnection::connected);
    connect(m_Socket, &QTcpSocket::disconnected, this, &TcpConnection::disconnected);
    m_IncomingMessage.setDevice(m_Socket);
    m_IncomingMessage.setVersion(QDataStream::Qt_5_13);
}

void TcpConnection::sendMessage(QString message) {
    QByteArray block;
    QDataStream outcomingMessage(&block, QIODevice::WriteOnly);
    outcomingMessage.setVersion(QDataStream::Qt_5_13);
    outcomingMessage << message;
    m_Socket->write(block);
    m_Socket->flush();
}

void TcpConnection::setSocketDescriptor(quintptr desc) {
    m_Socket->setSocketDescriptor(desc);
}

void TcpConnection::onReadyRead() {
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
    emit messageReady(message);
}
