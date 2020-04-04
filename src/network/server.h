#pragma once

#include <QObject>
#include <QTcpServer>

#include "networkactiontypes.h"

class Worker;
class AlbumLinkFactory;

class Server : public QTcpServer {
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr, AlbumLinkFactory *factory = nullptr);
    ~Server();
public slots:
    void onClientConnected(QString link, int workerIndex);
    void sendImages(networkMessage_t message);
protected:
    virtual void incomingConnection(qintptr descriptor) override;
private:
    QVector<QThread*> m_Threads;
    QVector<Worker*> m_Workers;
    const int THREAD_COUNT = 2;
    int m_QueueNumber = 0;
};
