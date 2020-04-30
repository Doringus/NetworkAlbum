#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QJsonObject>

/*!
 *      \brief The AlbumClient class provides network protocol implementation for server
 */
class AlbumClient : public QObject {
    Q_OBJECT
public:
    explicit AlbumClient(QObject *parent = nullptr, quintptr descriptor = 0);
    bool scaled();
    /*!
     * Sets result of auth
     */
    Q_INVOKABLE void setAuth(bool auth);
public slots:
    /*!
     * Sends images to client
     */
    void sendImages(const QList<QJsonObject>& images);
    /*!
     * Sends chat message to client
     */
    void sendConversation(const QString& message);
    /*!
     * Sends close session notification to client
     */
    void sendCloseSession();
private slots:
    /*!
     * Slot handles raw message from tcp connection
     */
    void onReadyRead();
    /*!
     * Slot handles new tcp connection
     */
    void onConnected();
    /*!
     * Slot handles disconnected signal
     */
    void onDisconnected();
    /*!
     * Slot manually disconnects client from server
     */
    void disconnectClient();
signals:
    void disconnected(const QString& link);
    void authorizationRequired(const QString& link, AlbumClient *client);
    void syncImages(const QString& link, const QVariant& data);
    void imagesRequired(const QString& link, bool scaled);
    void conversationReceived(const QString& link, const QString& message);
private:
    /*!
     * Slot handles prepared message
     */
    void handleMessage(const QString& message);

    /*!
     * Slot sends message via tcp
     */
    void sendMessage(const QString& message);

    /*!
     * Slot creates Json message from given type and content
     */
    QJsonObject createMessage(int type, const QJsonValue& value);
private:
    QTcpSocket *m_Socket;
    QDataStream m_IncomingMessage;
    bool m_HasAuth, m_Scaled;
    QString m_Link;
};

