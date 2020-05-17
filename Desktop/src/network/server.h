#pragma once

#include <QObject>
#include <QTcpServer>
#include <QMap>

#include "networkactiontypes.h"

class Worker;
class AlbumClient;

/*!
 * \brief The Server class provides tcp based multithreaded server
 * Server handles client requests and creates actions for application dispatcher
 */
class Server : public QTcpServer {
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

    /*!
     * Saves session link from created session for futher auth
     */
    void addSessionLink(const QString& link);

    /*!
     * Removes session link, when session closed
     */
    void removeSessionLink(int index);

    /*!
     * Finds right client and invokes it`s sendImages method
     */
    void sendImages(const networkMessage_t& message);

    /*!
     * Finds right client and invokes it`s sendConversation method
     */
    void sendMessage(const networkMessage_t& message);
    /*!
     * Finds right client and invokes it`s sendAlbumInfo method
     */
    void sendAlbumInfo(const networkMessage_t& message);
public slots:
    void onClientNeedImages(const QString& link, bool scaled);
    void onAuthClient(const QString& link, AlbumClient *client);
    void onClientChatMessage(const QString& link, const QString& message);
    void onSyncImages(const QString& link, const QVariant& data);
    void onClientDisconnected(const QString& link);
    void onClientNeedAlbumInfo(const QString& link);
protected:
    /*!
     * Handles raw incoming connection
     */
    virtual void incomingConnection(qintptr descriptor) override;
private:
    QList<QString> m_Links;
    QVector<QThread*> m_Threads;
    QMap<QString, AlbumClient*> m_Clients;
    const int THREAD_COUNT = 2;
    int m_QueueNumber = 0;
};
