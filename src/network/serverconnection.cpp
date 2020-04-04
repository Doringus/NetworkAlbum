#include "serverconnection.h"

#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QImage>

ServerConnection::ServerConnection(QObject *parent) : TcpConnection(parent) {
    connect(this, &TcpConnection::messageReady, [=](QString message){
        emit messageReady(message);
        qDebug() << "Message recied" << message;
        QJsonObject obj = QJsonDocument::fromJson(message.toUtf8()).object();
        QJsonArray images = obj.value("Images").toArray();
        for(int i = 0; i < images.size(); ++i) {
            QJsonObject imageObject = images.at(i).toObject();
            auto encoded = imageObject.value("Data").toString().toLatin1();
            QImage image;
            image.loadFromData(QByteArray::fromBase64(encoded), "JPG");
            image.save("test.jpg");
        }
    });
}

void ServerConnection::connectToServer(QString ip, int port) {
    m_Socket->connectToHost(ip, port);
}
