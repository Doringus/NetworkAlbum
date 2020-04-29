#pragma once

#include <QObject>
#include <QJsonObject>

#include "../base/middleware.h"
#include "../network/serverconnection.h"

class ClientNetworkAccessMiddleware : public QObject, public Middleware {
    Q_OBJECT
public:
    explicit ClientNetworkAccessMiddleware(QObject *parent = nullptr);
    QSharedPointer<Action> process(const QSharedPointer<Action>& action) override;
private slots:
    void onServerClosedSession();
private:
    void processConnectToAlbum(QString link, bool scaled);
    void processSendSyncData(QList<QPair<QString, QString>> data);
    void processSendMessage(const QString& message);
    void processReconnectToAlbum();
private:
    ServerConnection *m_ServerConnection;
    bool m_Scaled;
    QString m_Id;
    QString m_Ip;
    int m_Port;
};

