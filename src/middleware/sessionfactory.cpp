#include "sessionfactory.h"

#include "../action/actiontypes.h"
#include "../session.h"
#include "../base/action.h"

SessionFactory::SessionFactory(QObject *parent) : QObject(parent) {

}

SessionFactory::~SessionFactory() {

}

QSharedPointer<Action> SessionFactory::process(const QSharedPointer<Action>& action) {
    switch (action->getType<ActionType>()) {
        case ActionType::CREATE_SESSION: {
            QString errorString = validateUrl(action->getData<QList<QVariant>>().at(0).toUrl());
            Session session = processCreateSession(action->getData<QList<QVariant>>());
            QVariant sessionData = QVariant::fromValue(session);
            QSharedPointer<Action> action(new Action(ActionType::CREATE_SESSION, sessionData));
            action.data()->setErrorString(errorString);
            return action;
        }
    }


    return action;
}

Session SessionFactory::processCreateSession(QList<QVariant> data) {
    Session session(data.at(0).toUrl(), data.at(1).toBool(), data.at(2).toDouble(), "");
    return session;
}

QString SessionFactory::validateUrl(QUrl url) {
    if(url.isEmpty()) {
        return "Не указана папка альбома!";
    } else {
        return QString();
    }
}
