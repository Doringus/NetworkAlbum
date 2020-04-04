#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>

class AlbumClient : public QObject {
    Q_OBJECT
public:
    explicit AlbumClient(QObject *parent = nullptr, quintptr descriptor = 0);
    void sendMessage(QString message);
public slots:
    void onReadyRead();
    void onConnected();
    void onDisconnected();
    void disconnectClient();
signals:
    void authorizationRequired(QString link);
    void messageRecieved(int messageType, QVariant message);
private:
    void handleMessage(QString message);
private:
    QTcpSocket *m_Socket;
    QDataStream m_IncomingMessage;
    bool m_HasAuth;
};

