#include "conversationstore.h"

#include "../base/action.h"
#include "../action/actiontypes.h"
#include "../base/dispatcher.h"

ConversationStore::ConversationStore() {
    m_Conversation = new ConversationModel(this);
}

void ConversationStore::process(const QSharedPointer<Action> &action) {
    switch (action->getType<ActionType>()) {
        case ActionType::BEGIN_SEND_MESSAGE: {
            processSendMessage(action->getData<QString>());
            break;
        }
        case ActionType::RECEIVE_MESSAGE: {
            processReceiveMessage(action->getData<QString>());
            break;
        }
    }
}

QAbstractListModel *ConversationStore::getConversationModel() {
    return m_Conversation;
}

void ConversationStore::processSendMessage(const QString &message) {
    m_Conversation->add(message, true);
    Dispatcher::get().dispatch(new Action(ActionType::SEND_MESSAGE, message.trimmed()));
}

void ConversationStore::processReceiveMessage(const QString &message) {
    m_Conversation->add(message, false);
}
