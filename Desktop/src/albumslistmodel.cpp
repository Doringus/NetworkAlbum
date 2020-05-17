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

int AlbumsListModel::count() {
    return m_Data.size();
}

int AlbumsListModel::getNotificationCount(int index) {
    if(index < m_NotificationCount.size()) {
        return m_NotificationCount.at(index);
    }
    return -1;
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
        case SyncNotyfication: {
            return m_SynchNotifications.at(parent.row());
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
    roles[SyncNotyfication] = "isSync";
    return roles;
}

void AlbumsListModel::add(QString albumName, QUrl titlePath, bool hasReserve) {
    beginInsertRows(QModelIndex(), m_Data.size(), m_Data.size());
    m_HasReserve.append(hasReserve);
    m_Data.append({albumName, titlePath});
    m_NotificationCount.append(0);
    m_SynchNotifications.append(false);
    endInsertRows();
    QModelIndex index = createIndex(0, 0, static_cast<void*>(0));
    emit dataChanged(index, index);
}

void AlbumsListModel::addNotification(int index) {
    QModelIndex modelIndex = createIndex(index, 0, static_cast<void*>(0));
    m_NotificationCount[modelIndex.row()]++;
    emit dataChanged(modelIndex, modelIndex);
}

void AlbumsListModel::addSynchNotification(int index) {
    QModelIndex modelIndex = createIndex(index, 0, static_cast<void*>(0));
    m_SynchNotifications[modelIndex.row()] = true;
    emit dataChanged(modelIndex, modelIndex);
}

void AlbumsListModel::clearNotifications(int index, bool reserve) {
    QModelIndex modelIndex = createIndex(index, 0, static_cast<void*>(0));
    m_NotificationCount[modelIndex.row()] = 0;
    if(!m_HasReserve.at(modelIndex.row()) || (reserve && m_HasReserve.at(modelIndex.row()))) {
        m_SynchNotifications[modelIndex.row()] = false;
    }
    emit dataChanged(modelIndex, modelIndex);
}

void AlbumsListModel::removeAlbum(int index) {
    QModelIndex modelIndex = createIndex(index, 0, static_cast<void*>(0));
    beginRemoveRows(QModelIndex(), index, index);
    m_Data.removeAt(modelIndex.row());
    m_NotificationCount.removeAt(modelIndex.row());
    endRemoveRows();
    emit dataChanged(modelIndex, modelIndex);
}
