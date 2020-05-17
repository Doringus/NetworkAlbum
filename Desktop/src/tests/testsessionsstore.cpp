#include "testsessionsstore.h"

#include "../session.h"
#include "../store/sessionsstore.h"
#include "../base/action.h"
#include "../action/actiontypes.h"

TestSessionsStore::TestSessionsStore(QObject *parent) : QObject(parent) {

}

void TestSessionsStore::testOpenAlbum() {
    Session session(QUrl("TestUrl"), false, 25.0);
    session.setSessionId("test2");
    QSharedPointer<Action> p(new Action(ActionType::CREATE_SESSION, QVariant::fromValue(session)));
    SessionsStore::get().process(p);
    QSharedPointer<Action> p2(new Action(ActionType::OPEN_ALBUM, 0));
    SessionsStore::get().process(p2);
    QCOMPARE(SessionsStore::get().getCurrentIndex(), 0);
}

void TestSessionsStore::testCreateAlbum() {
    int k = SessionsStore::get().getSessionsCount();
    Session session(QUrl("TestUrl"), false, 25.0);
    session.setSessionId("test3");
    QSharedPointer<Action> p(new Action(ActionType::CREATE_SESSION, QVariant::fromValue(session)));
    SessionsStore::get().process(p);
    QCOMPARE(k++, SessionsStore::get().getSessionsCount());
}

void TestSessionsStore::testGetSessionIndex() {
    QCOMPARE(SessionsStore::get().getSessionIndex("WRONGLINK"), -1);
    QVERIFY(SessionsStore::get().getSessionIndex("test2") != -1);
}
