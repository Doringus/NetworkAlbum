#include "serverconnection.h"

#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QImage>

ServerConnection::ServerConnection(QObject *parent) : TcpConnection(parent) {

}

void ServerConnection::connectToServer(QString ip, int port) {
    m_Socket->connectToHost(ip, port);
}
