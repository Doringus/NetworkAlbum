#pragma once

#include <QObject>

#include "../base/store.h"
#include "../conversationmodel.h"

/*!
 * \brief The ConversationStore class stores conversation model for current album
 */
class ConversationStore : public QObject, public Store {
    Q_OBJECT
public:
    ConversationStore(const ConversationStore&) = delete;
    ConversationStore& operator=(const ConversationStore&) = delete;

    static ConversationStore& get() {
        static ConversationStore instance;
        return instance;
    }
    void process(const QSharedPointer<Action>& action);
signals:

private:
    ConversationStore();
    void processSendMessage(const QString& message);
private:
    ConversationModel* m_ConversationModel;
};

