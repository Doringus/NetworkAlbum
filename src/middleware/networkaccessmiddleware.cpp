#include "networkaccessmiddleware.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMessageBox>
#include <QApplication>

#include "../network/server.h"
#include "../base/action.h"
#include "../action/actiontypes.h"
#include "../session.h"

NetworkAccessMiddleware::NetworkAccessMiddleware(QObject *parent) : QObject(parent) {
    m_Server = new Server(this);
}

QSharedPointer<Action> NetworkAccessMiddleware::process(const QSharedPointer<Action> &action) {
    switch(action->getType<ActionType>()) {
        case ActionType::CREATE_SESSION: {
            if(action->getErrorString() == "") {
                m_Server->addSessionLink(action->getData<Session>().getSessionId());
            }
            break;
        }
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
        case ActionType::START_SERVER: {
            if(!m_Server->listen(QHostAddress::Any, 22222)){
                QMessageBox box;
                box.setText("Ошибка");
                box.setInformativeText("Не удалось запустить сервер");
                box.setIcon(QMessageBox::Critical);
                box.setStandardButtons(QMessageBox::Ok);
                box.exec();
                QApplication::quit();
            }
            break;
        }
        case ActionType::CLOSE_SESSION: {
            m_Server->removeSessionLink(action->getData<int>());
            break;
        }
    }
    return action;
}
