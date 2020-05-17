#pragma once

#include <QObject>
#include <QMap>
#include <QVariant>

/*class AlbumLinkFactory;
class AlbumClient;

class Worker : public QObject {
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr, int index = -1);
    Q_INVOKABLE void addClientConnection(AlbumClient *client);
    Q_INVOKABLE void sendMessage(QString link, QString message);
public slots: 
    void onAuthClient(QString link);
    void onClientMessage(QString link, int type, QVariant message);
    void onClientDisconnected(QString clientLink);
signals:
    void clientConnected(QString link, int threadIndex, bool scaled);
    void syncImages(QString link, int workerIndex, QVariant data);
private:
    QMap<QString, AlbumClient*> m_Clients;
    AlbumLinkFactory *m_AlbumLinkFactory;
    int m_Index;
};*/

