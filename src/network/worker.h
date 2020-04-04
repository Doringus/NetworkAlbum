#pragma once

#include <QObject>
#include <QMap>
#include <QVariant>

class AlbumLinkFactory;
class AlbumClient;

class Worker : public QObject {
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr, AlbumLinkFactory *factory = nullptr, int index = -1);
    Q_INVOKABLE void addClientConnection(qintptr descriptor);
    Q_INVOKABLE void sendMessage(QString link, QString message);
public slots: 
    void onAuthClient(QString link);
    void onClientMessage(int type, QVariant message);
    void onClientDisconnected(QString clientLink);
signals:
    void clientConnected(QString link, int threadIndex);
private:
    QMap<QString, AlbumClient*> m_Clients;
    AlbumLinkFactory *m_AlbumLinkFactory;
    int m_Index;
};

