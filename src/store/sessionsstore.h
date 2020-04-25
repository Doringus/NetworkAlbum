#pragma once

#include <QObject>

#include "../base/store.h"
#include "../albumslistmodel.h"
#include "../session.h"
#include "../network/networkactiontypes.h"
#include "../imagemover.h"

/*! \brief Generic store. Stores sessions data.
    Manages link popup
*/
class SessionsStore : public QObject, public Store  {
    Q_OBJECT 
public:
    SessionsStore(const SessionsStore&) = delete;
    SessionsStore& operator=(const SessionsStore&) = delete;

    static SessionsStore& get() {
        static SessionsStore instance;
        return instance;
    }
    void process(const QSharedPointer<Action>& action);
    const Session& getCurrentSession();
    const Session& getSession(int index);
    int getCurrentIndex();
    int getSessionIndex(const QString& link);
signals:

private:
    SessionsStore();
    void processCreateSession(const Session& session);
    void processSendImages(networkMessage_t&& message);
    void processReceiveSync(const networkMessage_t&& message);
    void processSendMessage(const QString& message);
    void processReceiveMessage(const networkMessage_t&& message);
    bool copyFolder(const QString& from, const QString& to);
private:
    QList<Session> m_Sessions;
    int m_CurrentAlbumIndex;
    ImageMover *m_ImageMover;
};

