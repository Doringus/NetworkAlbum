#include "networkaccessmiddleware.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "../network/server.h"
#include "../network/albumlinkfactory.h"
#include "../base/action.h"
#include "../action/actiontypes.h"
#include "../session.h"

NetworkAccessMiddleware::NetworkAccessMiddleware(QObject *parent) : QObject(parent) {
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, [=](QNetworkReply *reply) {
        QByteArray data=reply->readAll();
        qInfo() << this << "Public IP = " << QString::fromUtf8(data);
        m_AlbumLinkFactory = new AlbumLinkFactory(this, QString::fromUtf8(data));
        m_Server = new Server(this, m_AlbumLinkFactory);
    });
    manager->get(QNetworkRequest(QUrl("https://api.ipify.org")));
}

QSharedPointer<Action> NetworkAccessMiddleware::process(const QSharedPointer<Action> &action) {
    switch(action->getType<ActionType>()) {
        case ActionType::SEND_IMAGES: {
            if(action->getErrorString() == "") {
                m_Server->sendImages(action->getData<networkMessage_t>());
            }
            break;
        }
        case ActionType::SEND_MESSAGE: {
            break;
        }
        case ActionType::CREATE_SESSION: {
            Session session = action->getData<Session>();
            session.setLink(m_AlbumLinkFactory->getLink());
            action->setData(QVariant::fromValue(session));
            break;
        }
        case ActionType::START_SERVER: {
            m_Server->listen(QHostAddress::Any, 22222);
            break;
        }
    }
    return action;
}
