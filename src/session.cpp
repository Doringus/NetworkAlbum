#include <QFileInfo>
#include <QDir>
#include <QDebug>

#include "session.h"

Session::Session(QUrl albumPath, bool hasCopy, double compress)
    : m_AlbumPath(albumPath), m_HasCopy(hasCopy), m_Compress(compress) {
    m_Conversation = new ConversationModel();
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
      m_Conversation(other.getConversation()){

}

void Session::closeSession() {
    m_Conversation->deleteLater();
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

QString Session::getGlobalLink() const {
    return m_GlobalLink;
}

QString Session::getLocalLink() const {
    return m_LocalLink;
}

QString Session::getSessionId() const {
    return m_SessionId;
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

