#include "linkmiddleware.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QHostAddress>
#include <QNetworkInterface>

#include "../action/actiontypes.h"
#include "../session.h"
#include "../base/action.h"

LinkMiddleware::LinkMiddleware(QObject *parent) : QObject(parent) {
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, [=](QNetworkReply *reply) {
        QByteArray data=reply->readAll();
        qInfo() << this << "Public IP = " << QString::fromUtf8(data);
        m_PublicIp = QString::fromUtf8(data);
    });
    manager->get(QNetworkRequest(QUrl("https://api.ipify.org")));
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
             m_LocalIp = address.toString();
    }
}

QSharedPointer<Action> LinkMiddleware::process(const QSharedPointer<Action> &action) {
    switch (action->getType<ActionType>()) {
        case ActionType::CREATE_SESSION: {
            Session session = action->getData<Session>();
            processCreateLink(session);
            action->setData(QVariant::fromValue<Session>(session));
        }
    }
    return action;
}

void LinkMiddleware::processCreateLink(Session &session) {
    QString sessionId = QString::number(m_Counter).toUtf8().toBase64();
    session.setSessionId(sessionId);
    session.setGlobalLink(m_PublicIp + ":" + sessionId);
    session.setLocalLink(m_LocalIp + ":" + sessionId);
    m_Counter++;
}
