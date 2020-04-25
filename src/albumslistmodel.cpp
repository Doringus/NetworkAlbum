#include "albumslistmodel.h"

#include <QUrl>
#include <QDebug>

AlbumsListModel::AlbumsListModel(QObject *parent) : QAbstractListModel(parent) {

}

int AlbumsListModel::rowCount(const QModelIndex &parent) const {
    if(parent.isValid()) {
        return 0;
    }
    return m_Data.size();
}

QVariant AlbumsListModel::data(const QModelIndex &parent, int role) const {
    if(!parent.isValid()) {
        return QVariant();
    }
    switch (role) {
        case NameRole: {
            return m_Data.at(parent.row()).first;
        }
        case ImageRole: {
            return m_Data.at(parent.row()).second;
        }
        case NotificationCountRole: {
            return QString::number(m_NotificationCount.at(parent.row()));
        }
        default: {
            return QVariant();
        }
    }
}

QHash<int, QByteArray> AlbumsListModel::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[NameRole] = "albumName";
    roles[ImageRole] = "titleImage";
    roles[NotificationCountRole] = "notifications";
    return roles;
}

void AlbumsListModel::add(QString albumName, QUrl titlePath) {
    beginInsertRows(QModelIndex(), m_Data.size(), m_Data.size());
    m_Data.append({albumName, titlePath});
    m_NotificationCount.append(0);
    endInsertRows();
    QModelIndex index = createIndex(0, 0, static_cast<void*>(0));
    emit dataChanged(index, index);
}

void AlbumsListModel::addNotification(int index) {
    QModelIndex modelIndex = createIndex(index, 0, static_cast<void*>(0));
    m_NotificationCount[modelIndex.row()]++;
    emit dataChanged(modelIndex, modelIndex);
}

void AlbumsListModel::clearNotifications(int index) {
    QModelIndex modelIndex = createIndex(index, 0, static_cast<void*>(0));
    m_NotificationCount[modelIndex.row()] = 0;
    emit dataChanged(modelIndex, modelIndex);
}
