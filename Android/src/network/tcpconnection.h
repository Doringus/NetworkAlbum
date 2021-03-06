#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>

/*!
 *      \brief The TcpConnection class is QTcpSocket wrapper
 *      Class handles QTcpSocket signals
 */
class TcpConnection : public QObject {
    Q_OBJECT
public:
    explicit TcpConnection(QObject *parent = nullptr);
    void sendMessage(QString message);
signals:
    void messageReady(QString message);
    void connected();
    void disconnected();
protected:
    void setSocketDescriptor(quintptr desc);
private slots:
    void onReadyRead();
protected:
    QTcpSocket *m_Socket;
    QDataStream m_IncomingMessage;
};
