#pragma once

#include <QObject>
#include <QAbstractListModel>
#include <QPair>
#include <QUrl>

/*!
 * \brief The ConversationModel class provides simple list model for chat
 */
class ConversationModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit ConversationModel(QObject *parent = nullptr, QList<QPair<QString, bool>> conversation = QList<QPair<QString, bool>>());
    enum Roles {
        MessageRole = Qt::UserRole + 1,
        SenderRole
    };
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &parent, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    void add(const QString& message, bool owner);
    QList<QPair<QString, bool>> getConversation();
    void setConverstaion(const QList<QPair<QString, bool>>& conversation);
private:
    QList<QPair<QString, bool>> m_Data;
};

