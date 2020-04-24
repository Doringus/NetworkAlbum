#pragma once

#include <QObject>

#include "middleware/networkaccessmiddleware.h"
#include "middleware/sessionfactory.h"
#include "middleware/clientnetworkaccessmiddleware.h"
#include "middleware/linkmiddleware.h"

class Core : public QObject {
    Q_OBJECT
public:
    explicit Core(QObject *parent = nullptr);
private slots:
    void onSessionCreated();
    void onConnectedToAlbum();
private:
    SessionFactory *m_SessionFactory;
    NetworkAccessMiddleware *m_NetworkAccessMiddleware;
    ClientNetworkAccessMiddleware *m_ClientNetworkMiddleware;
    LinkMiddleware *m_LinkMiddleware;
};

