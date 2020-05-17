#include "eastereggstore.h"

#include "../base/action.h"
#include "../action/actiontypes.h"
#include "../base/dispatcher.h"

void EasterEggStore::process(const QSharedPointer<Action> &action) {
    switch (action->getType<ActionType>()) {
        case ActionType::BEGIN_SEND_MESSAGE: {
            processSendMessage(action->getData<QString>());
            break;
        }
        case ActionType::HIDE_EASTER_EGG_POPUP: {
            m_ShowEasterEgg = false;
            emit showEasterEggChanged();
            break;
        }
    }
}

bool EasterEggStore::getShowEasterEgg() {
    return m_ShowEasterEgg;
}

void EasterEggStore::processSendMessage(const QString &message) {
    if(message.trimmed() == "primo victoria") {
        m_ShowEasterEgg = true;
        emit showEasterEggChanged();
    }
}
