#include "session.h"

Session::Session(QUrl albumPath, bool hasCopy, double compress)
    : m_AlbumPath(albumPath), m_HasCopy(hasCopy), m_Compress(compress) {

}

QUrl Session::getAlbumPath() const {
    return m_AlbumPath;
}

bool Session::hasCopy() const {
    return m_HasCopy;
}

double Session::getCompression() const {
    return m_Compress;
}

void Session::setAlbumPath(QUrl url) {
    m_AlbumPath = url;
}
