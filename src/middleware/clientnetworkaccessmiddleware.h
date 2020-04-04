#pragma once

#include <QObject>

#include "../base/middleware.h"
#include "../network/serverconnection.h"

class ClientNetworkAccessMiddleware : public QObject, public Middleware {
    Q_OBJECT
public:
    explicit ClientNetworkAccessMiddleware(QObject *parent = nullptr);
     QSharedPointer<Action> process(const QSharedPointer<Action>& action) override;
public slots:
     void onRecieveMessage(QString message);
private:
     void processConnectToAlbum(QString link);
private:
     ServerConnection *m_ServerConnection;
};

