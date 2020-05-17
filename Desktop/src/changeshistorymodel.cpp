#include "changeshistorymodel.h"

ChangesHistoryModel::ChangesHistoryModel(QObject *parent) : QAbstractListModel(parent) {

}

int ChangesHistoryModel::rowCount(const QModelIndex &parent) const {
    if(parent.isValid()) {
        return 0;
    }
    return m_Data.size();
}

QVariant ChangesHistoryModel::data(const QModelIndex &parent, int role) const {
    if(!parent.isValid()) {
        return QVariant();
    }
    switch (role) {
        case FromRole: {
            return m_Data.at(parent.row()).first;
        }
        case ToRole: {
            return m_Data.at(parent.row()).second;
        }
        default: {
            return QVariant();
        }
    }
}

QHash<int, QByteArray> ChangesHistoryModel::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[FromRole] = "from";
    roles[ToRole] = "to";
    return roles;
}

void ChangesHistoryModel::add(QString from, QString to) {
    beginInsertRows(QModelIndex(), m_Data.size(), m_Data.size());
    m_Data.append({from, to});
    endInsertRows();
    QModelIndex index = createIndex(0, 0, static_cast<void*>(0));
    emit dataChanged(index, index);
}
