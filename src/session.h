#pragma once

#include <QObject>
#include <QUrl>
#include <QHash>

#include "conversationmodel.h"

class Session {
public:
    explicit Session(QUrl albumPath = QUrl(), bool hasCopy = false, double compress = 50.0f);
    ~Session();
    Session(const Session& other);

    void closeSession();

    QUrl getAlbumPath() const;
    QUrl getAlbumReservePath() const;
    bool hasCopy() const;
    double getCompression() const;
    QString getGlobalLink() const;
    QString getLocalLink() const;
    QString getSessionId() const;
    ConversationModel* getConversation() const;

    void setAlbumPath(const QUrl& url);
    void setGlobalLink(const QString& link);
    void setLocalLink(const QString& link);
    void setConversation(ConversationModel *conversation);
    void setSessionId(const QString& id);
    void setHasCopy(bool copy);
    void setIndex(int index);

    friend bool operator==(const Session& left, const Session& right) {
        return left.getAlbumPath() == right.getAlbumPath();
    }
private:
    void markImages();
private:
    QUrl m_AlbumPath, m_AlbumReserveFolder;
    bool m_HasCopy;
    double m_Compress;
    QString m_GlobalLink, m_SessionId, m_LocalLink;
    ConversationModel *m_Conversation;
};

Q_DECLARE_METATYPE(Session)
