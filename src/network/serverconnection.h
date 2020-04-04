#pragma once

#include "tcpconnection.h"

class ServerConnection : public TcpConnection {
    Q_OBJECT
public:
    ServerConnection(QObject *parent = nullptr);
    void connectToServer(QString ip, int port);
public slots:

};

