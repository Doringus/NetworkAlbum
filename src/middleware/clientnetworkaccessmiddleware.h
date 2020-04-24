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
public slots:
    void onReceiveMessage(QString message);
private:
    void processConnectToAlbum(QString link, bool scaled);
    void processSendSyncData(QList<QPair<QString, QString>> data);
    void processAuth(bool auth);
    QJsonObject createMessage(int type, const QJsonValue& value);
    void processSendMessage(const QString& message);
private:
    ServerConnection *m_ServerConnection;
    bool m_Scaled;
};

