#include "serveralbumstore.h"

#include "../base/action.h"
#include "../action/actiontypes.h"
#include "../base/dispatcher.h"
#include "sessionsstore.h"

void ServerAlbumStore::process(const QSharedPointer<Action> &action) {
    AlbumStore::process(action);
    switch (action->getType<ActionType>()) {
        case ActionType::OPEN_ALBUM: {
            processOpenAlbum();
            break;
        }
        case ActionType::OPEN_RESERVE_ALBUM: {
            processOpenReserveAlbum();
            break;
        }
    }
}

QString ServerAlbumStore::albumReserveFolder() {
    return m_AlbumReserveFolder;
}

QAbstractListModel *ServerAlbumStore::getHistoryModel() {
    return m_ChangesHistory;
}

void ServerAlbumStore::processOpenAlbum() {
    QUrl albumPath = SessionsStore::get().getCurrentSession().getAlbumPath();
    setAlbumUrl(albumPath);
    setCurrentFolderUrl(albumPath);
    setAlbumPageTitle(albumPath.fileName());
    m_Conversation = SessionsStore::get().getCurrentSession().getConversation();
    m_ChangesHistory = SessionsStore::get().getCurrentSession().getChangesHistory();
    emit conversationModelChanged();
    emit historyModelChanged();
}

void ServerAlbumStore::processOpenReserveAlbum() {
    QUrl albumPath = SessionsStore::get().getCurrentSession().getAlbumPath();
    QUrl reserve = SessionsStore::get().getCurrentSession().getAlbumReservePath();
    setAlbumUrl(reserve);
    setCurrentFolderUrl(reserve);
    setAlbumPageTitle(albumPath.fileName());
    m_Conversation = SessionsStore::get().getCurrentSession().getConversation();
    m_ChangesHistory = SessionsStore::get().getCurrentSession().getChangesHistory();
    m_AlbumReserveFolder = reserve.toLocalFile();
    emit conversationModelChanged();
    emit albumReserveFolderChanged();
    emit historyModelChanged();
}
