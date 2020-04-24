#include "networkaccessmiddleware.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "../network/server.h"
#include "../network/albumlinkfactory.h"
#include "../base/action.h"
#include "../action/actiontypes.h"
#include "../session.h"

NetworkAccessMiddleware::NetworkAccessMiddleware(QObject *parent) : QObject(parent) {
    m_Server = new Server(this);
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
            m_Server->sendMessage(action->getData<networkMessage_t>());
            break;
        }
        case ActionType::REGISTER_LINK: {
            m_Server->addSessionLink(action->getData<QString>());
            qDebug() << this << "Link registered" << action->getData<QString>();
            break;
        }
        case ActionType::START_SERVER: {
            m_Server->listen(QHostAddress::Any, 22222);
            break;
        }
    }
    return action;
}
