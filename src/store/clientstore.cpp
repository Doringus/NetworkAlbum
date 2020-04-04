#include "clientstore.h"

void ClientStore::process(const QSharedPointer<Action> &action) {

}

QUrl ClientStore::getAlbumUrl() {
    return m_CurrentAlbumUrl;
}

QUrl ClientStore::getCurrentFolderUrl() {
    return m_CurrentFolderUrl;
}

QUrl ClientStore::getImageUrl() {
    return m_ImageUrl;
}

