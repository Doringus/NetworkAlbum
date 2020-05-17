#pragma once

#include "albumstore.h"

/*!
 * \brief The ServerAlbumStore class is server implementation for album page
 */
class ServerAlbumStore : public AlbumStore {
    Q_OBJECT
public:
    Q_PROPERTY(QString albumReserveFolder READ albumReserveFolder NOTIFY albumReserveFolderChanged)
    Q_PROPERTY(QAbstractListModel* historyModel READ getHistoryModel NOTIFY historyModelChanged)
public:
    ServerAlbumStore(const ServerAlbumStore&) = delete;
    ServerAlbumStore& operator=(const ServerAlbumStore&) = delete;

    static ServerAlbumStore& get() {
        static ServerAlbumStore instance;
        return instance;
    }

    virtual void process(const QSharedPointer<Action>& action);

    QString albumReserveFolder();
    QAbstractListModel* getHistoryModel();
signals:
    void albumReserveFolderChanged();
    void historyModelChanged();
private:
    ServerAlbumStore() = default;
    void processOpenAlbum();
    void processOpenReserveAlbum();
private:
    ChangesHistoryModel *m_ChangesHistory;
    QString m_AlbumReserveFolder;
};


