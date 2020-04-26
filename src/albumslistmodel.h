#pragma once

#include <QObject>
#include <QAbstractListModel>
#include <QPair>
#include <QUrl>

class AlbumsListModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit AlbumsListModel(QObject *parent = nullptr);
    enum Roles {
        NameRole = Qt::UserRole + 1,
        ImageRole,
        NotificationCountRole,
        SyncNotyfication
    };
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &parent, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    void add(QString albumName, QUrl titlePath, bool hasReserve);
    void addNotification(int index);
    void addSynchNotification(int index);
    void clearNotifications(int index, bool reserve);
    void removeAlbum(int index);
private:
    QList<QPair<QString, QUrl>> m_Data;
    QList<int> m_NotificationCount;
    QList<bool> m_SynchNotifications;
    QList<bool> m_HasReserve;
};

