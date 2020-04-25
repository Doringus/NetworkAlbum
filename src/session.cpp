#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QFileInfo>

#include "session.h"

Session::Session(QUrl albumPath, bool hasCopy, double compress)
    : m_AlbumPath(albumPath), m_HasCopy(hasCopy), m_Compress(compress) {
    m_Conversation = new ConversationModel();
    QFileInfo info(albumPath.toLocalFile());
    if(hasCopy) {
        QString reserveFolder = info.absoluteDir().path() + "/" + info.fileName() + "_res";
        m_AlbumReserveFolder = QUrl(reserveFolder);
    }
}

Session::~Session() {

}

Session::Session(const Session &other)
    : m_AlbumPath(other.getAlbumPath()),
      m_HasCopy(other.hasCopy()),
      m_Compress(other.getCompression()),
      m_GlobalLink(other.getGlobalLink()),
      m_LocalLink(other.getLocalLink()),
      m_SessionId(other.getSessionId()),
      m_Conversation(other.getConversation()),
      m_AlbumReserveFolder(other.getAlbumReservePath()){

}

void Session::closeSession() {
    m_Conversation->deleteLater();
}

QUrl Session::getAlbumPath() const {
    return m_AlbumPath;
}

QUrl Session::getAlbumReservePath() const {
    return m_AlbumReserveFolder;
}

bool Session::hasCopy() const {
    return m_HasCopy;
}

double Session::getCompression() const {
    return m_Compress;
}

QString Session::getGlobalLink() const {
    return m_GlobalLink;
}

QString Session::getLocalLink() const {
    return m_LocalLink;
}

QString Session::getSessionId() const {
    return m_SessionId;
}

QString Session::getReserveFolder() const {
    return m_ReserveFolder;
}

ConversationModel *Session::getConversation() const {
    return m_Conversation;
}

void Session::setAlbumPath(const QUrl& url) {
    m_AlbumPath = url;
}

void Session::setLocalLink(const QString &link) {
    m_LocalLink = link;
}

void Session::setGlobalLink(const QString& link) {
    m_GlobalLink = link;
}

void Session::setConversation(ConversationModel *conversation) {
    m_Conversation = conversation;
}

void Session::setSessionId(const QString &id) {
    m_SessionId = id;
}

