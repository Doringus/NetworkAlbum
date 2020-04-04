#pragma once

#include <QObject>
#include <QMap>
#include <QVariant>

#include "../base/middleware.h"
#include "../network/albumclient.h"

class Server;
class AlbumLinkFactory;

class NetworkAccessMiddleware : public QObject, public Middleware {
    Q_OBJECT
public:
    explicit NetworkAccessMiddleware(QObject *parent = nullptr);
    QSharedPointer<Action> process(const QSharedPointer<Action>& action) override;
public slots:
signals:
private:
   Server *m_Server;
   AlbumLinkFactory *m_AlbumLinkFactory;
};


