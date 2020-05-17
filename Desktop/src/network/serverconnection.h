#pragma once

#include "tcpconnection.h"

/*!
 *      \brief The ServerConnection class provides network protocol implementation for client.
 *      ServerConnection generates actions for application dispatcher
 */
class ServerConnection : public TcpConnection {
    Q_OBJECT
public:
    ServerConnection(QObject *parent = nullptr);

    /*!
     * Connects or reconnects to server
     */
    void connectToServer(QString ip, int port, bool reconnect);

    /*!
     * Sets scaled param to connection
     */
    void setScaled(bool scaled);

    /*!
     * Sets session id
     */
    void setId(const QString& id);

    /*!
     * Sends sync data
     */
    void sendSyncData(const QList<QPair<QString, QString>>& data);

    /*!
     *  Sends chat message
     */
    void sendChatMessage(const QString& message);

    /*!
     * Sends get images request
     */
    void getImages();
signals:
    /*!
     * Signal emits when server closes session
     */
    void sessionClosed();
private slots:
    /*!
     * Handles network message
     */
    void handleMessage(const QString& message);

    /*!
     * Sends authorization params to server
     */
    void sendAuth();

    /*!
     * Slot handles tcp connection disconnected signal
     */
    void onDisconnected();
private:
    /*!
     * Handles server auth answer
     */
    void onAuth(bool auth);

    /*!
     * Slot creates Json message from given type and content
     */
    QJsonObject createMessage(int type, const QJsonValue &value);
private:
    bool m_Scaled, m_Auth = false, m_Reconnect;
    QString m_Id;
};

