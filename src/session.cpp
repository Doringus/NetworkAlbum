#include "session.h"

Session::Session(QUrl albumPath, bool hasCopy, double compress, QString link)
    : m_AlbumPath(albumPath), m_HasCopy(hasCopy), m_Compress(compress), m_Link(link) {

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

QString Session::getLink() const {
    return m_Link;
}

void Session::setAlbumPath(QUrl url) {
    m_AlbumPath = url;
}

void Session::setLink(QString link) {
    m_Link = link;
}

