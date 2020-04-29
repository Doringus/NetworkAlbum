#pragma once

#include "tcpconnection.h"

class ServerConnection : public TcpConnection {
    Q_OBJECT
public:
    ServerConnection(QObject *parent = nullptr);
    void connectToServer(QString ip, int port, bool reconnect);
    void setScaled(bool scaled);
    void setId(const QString& id);

    void sendSyncData(const QList<QPair<QString, QString>>& data);
    void sendChatMessage(const QString& message);
signals:
    void sessionClosed();
private slots:
    void handleMessage(const QString& message);
    void sendAuth();
    void onDisconnected();
private:
    void onAuth(bool auth);
    QJsonObject createMessage(int type, const QJsonValue &value);
private:
    bool m_Scaled, m_Auth = false, m_Reconnect;
    QString m_Id;
};

