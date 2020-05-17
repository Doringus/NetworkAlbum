#pragma once

#include <QObject>


/*!
 *      \brief The Core class manages all application.
 *      It creates stores and middlewares. Provides them to qml layer and dispatcher
 */

class ClientNetworkAccessMiddleware;

class Core : public QObject {
    Q_OBJECT
public:
    explicit Core(QObject *parent = nullptr);
private slots:
    void onSessionCreated();
    void onConnectedToAlbum();
private:
    ClientNetworkAccessMiddleware *m_ClientNetworkMiddleware;
};

