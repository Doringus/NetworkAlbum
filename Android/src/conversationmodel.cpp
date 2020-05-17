#include "conversationmodel.h"

ConversationModel::ConversationModel(QObject *parent, QList<QPair<QString, bool>> conversation) : QAbstractListModel(parent) {
    m_Data = conversation;
}

int ConversationModel::rowCount(const QModelIndex &parent) const {
    if(parent.isValid()) {
        return 0;
    }
    return m_Data.size();
}

QVariant ConversationModel::data(const QModelIndex &parent, int role) const {
    if(!parent.isValid()) {
        return QVariant();
    }
    switch (role) {
        case MessageRole: {
            return m_Data.at(parent.row()).first;
        }
        case SenderRole: {
            return m_Data.at(parent.row()).second;
        }
        default: {
            return QVariant();
        }
    }
}

QHash<int, QByteArray> ConversationModel::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[MessageRole] = "message";
    roles[SenderRole] = "owner";
    return roles;
}

void ConversationModel::add(const QString& message, bool owner) {
    beginInsertRows(QModelIndex(), 0, 0);
    m_Data.prepend({message, owner});
    endInsertRows();
    QModelIndex index = createIndex(0, 0, static_cast<void*>(0));
    emit dataChanged(index, index);
}

QList<QPair<QString, bool>> ConversationModel::getConversation() {
    return m_Data;
}

void ConversationModel::setConverstaion(const QList<QPair<QString, bool> > &conversation) {
    beginResetModel();
    m_Data = conversation;
    endResetModel();
}
