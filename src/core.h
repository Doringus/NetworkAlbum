#pragma once

#include <QObject>

#include "middleware/networkaccessmiddleware.h"
#include "middleware/sessionfactory.h"
#include "middleware/clientnetworkaccessmiddleware.h"

class Core : public QObject {
    Q_OBJECT
public:
    explicit Core(QObject *parent = nullptr);

signals:
private:
    SessionFactory *m_SessionFactory;
    NetworkAccessMiddleware *m_NetworkAccessMiddleware;
    ClientNetworkAccessMiddleware *m_ClientNetworkMiddleware;
};

