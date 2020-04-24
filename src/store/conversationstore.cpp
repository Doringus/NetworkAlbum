#include "conversationstore.h"

#include "../base/action.h"
#include "../action/actiontypes.h"
#include "../base/dispatcher.h"
#include "sessionsstore.h"

ConversationStore::ConversationStore() {
    m_ConversationModel = nullptr;
}


void ConversationStore::process(const QSharedPointer<Action> &action) {
    switch (action->getType<ActionType>()) {
        case ActionType::OPEN_ALBUM: {
            m_ConversationModel = SessionsStore::get().getCurrentSession().getConversation();
            break;
        }
        case ActionType::SEND_MESSAGE: {
            processSendMessage(action->getData<QString>());
            break;
        }

    }
}

void ConversationStore::processSendMessage(const QString& message) {
    if(m_ConversationModel == nullptr) {
        return;
    }
    m_ConversationModel->add(message, true);
    networkMessage_t networkMessage;
    networkMessage.clientLink = SessionsStore::get().getCurrentSession().getSessionId();
    networkMessage.data = message.trimmed();
    Dispatcher::get().dispatch(new Action(ActionType::SEND_MESSAGE, QVariant::fromValue(networkMessage)));
}
