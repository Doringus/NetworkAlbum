#pragma once

#include <QObject>
#include <QAbstractListModel>
#include <QPair>

/*!
 * \brief The ChangesHistoryModel class provides simple list model for changes history popup
 */
class ChangesHistoryModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit ChangesHistoryModel(QObject *parent = nullptr);
    enum Roles {
        FromRole = Qt::UserRole + 1,
        ToRole,

    };
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &parent, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    void add(QString from, QString to);
private:
    QList<QPair<QString, QString>> m_Data;
};

