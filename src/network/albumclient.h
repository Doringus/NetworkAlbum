#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QJsonObject>

class AlbumClient : public QObject {
    Q_OBJECT
public:
    explicit AlbumClient(QObject *parent = nullptr, quintptr descriptor = 0);
    bool scaled();
    Q_INVOKABLE void setAuth(bool auth);
public slots:
    void sendImages(const QList<QJsonObject>& images);
    void sendConversation(const QString& message);
    void sendCloseSession();
private slots:
    void onReadyRead();
    void onConnected();
    void onDisconnected();
    void disconnectClient();
signals:
    void disconnected(const QString& link);
    void authorizationRequired(const QString& link, AlbumClient *client);
    void syncImages(const QString& link, const QVariant& data);
    void imagesRequired(const QString& link, bool scaled);
    void conversationReceived(const QString& link, const QString& message);
private:
    void handleMessage(const QString& message);
    void sendMessage(const QString& message);
    QJsonObject createMessage(int type, const QJsonValue& value);
private:
    QTcpSocket *m_Socket;
    QDataStream m_IncomingMessage;
    bool m_HasAuth, m_Scaled;
    QString m_Link;
};

