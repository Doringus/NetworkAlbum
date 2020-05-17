#pragma once

#include <QObject>

#include "middleware/networkaccessmiddleware.h"
#include "middleware/sessionfactory.h"
#include "middleware/clientnetworkaccessmiddleware.h"
#include "middleware/linkmiddleware.h"

/*!
 *      \brief The Core class manages all application.
 *      It creates stores and middlewares. Provides them to qml layer and dispatcher
 */
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

