#pragma once

#include <QObject>

#include "../conversationmodel.h"
#include "../base/store.h"

class ConversationStore : public QObject, public Store {
    Q_OBJECT
public:
    Q_PROPERTY(QAbstractListModel* conversationModel READ getConversationModel NOTIFY conversationModelChanged)
public:
    ConversationStore(const ConversationStore&) = delete;
    ConversationStore& operator=(const ConversationStore&) = delete;

    static ConversationStore& get() {
        static ConversationStore instance;
        return instance;
    }

    void process(const QSharedPointer<Action>& action);
    QAbstractListModel* getConversationModel();

signals:
    void conversationModelChanged();
private:
    ConversationStore();
    void processSendMessage(const QString& message);
    void processReceiveMessage(const QString& message);
private:
    ConversationModel *m_Conversation;
};

