#pragma once

#include <QObject>
#include <QTcpServer>
#include <QMap>

#include "networkactiontypes.h"

class Worker;
class AlbumClient;

class Server : public QTcpServer {
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();
    void addSessionLink(const QString& link);
    void removeSessionLink(int index);
    void sendImages(const networkMessage_t& message);
    void sendMessage(const networkMessage_t& message);
public slots:
    void onClientNeedImages(const QString& link, bool scaled);
    void onAuthClient(const QString& link, AlbumClient *client);
    void onClientChatMessage(const QString& link, const QString& message);
    void onSyncImages(const QString& link, const QVariant& data);
    void onClientDisconnected(const QString& link);
protected:
    virtual void incomingConnection(qintptr descriptor) override;
private:
    QList<QString> m_Links;
    QVector<QThread*> m_Threads;
    QMap<QString, AlbumClient*> m_Clients;
    const int THREAD_COUNT = 2;
    int m_QueueNumber = 0;
};
