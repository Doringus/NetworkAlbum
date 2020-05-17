#pragma once

#include <QObject>
#include <QJsonObject>

#include "../base/middleware.h"
#include "../network/serverconnection.h"

/*!
 *      \brief The ClientNetworkAccessMiddleware class is network interface for client
 *      Class provides network functionality for client
 */
class ClientNetworkAccessMiddleware : public QObject, public Middleware {
    Q_OBJECT
public:
    explicit ClientNetworkAccessMiddleware(QObject *parent = nullptr);
    QSharedPointer<Action> process(const QSharedPointer<Action>& action) override;
private slots:
    /*!
     * Slot handles closing session. When invoked it closes application
     */
    void onServerClosedSession();
private:
    /*!
     * Gets ip and session id from link and connects to server
     */
    void processConnectToAlbum(QString link, bool scaled);

    /*!
     * Sends sync data
     * \param data List of changes in format <newPath, oldPath>
     */
    void processSendSyncData(QList<QPair<QString, QString>> data);

    /*!
     * Sends chat message
     */
    void processSendMessage(const QString& message);
    /*!
     * Reconnects to album
     */
    void processReconnectToAlbum();
private:
    ServerConnection *m_ServerConnection;
    bool m_Scaled;
    QString m_Id;
    QString m_Ip;
    int m_Port;
};

