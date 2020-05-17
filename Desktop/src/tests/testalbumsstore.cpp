#include "testalbumsstore.h"

#include "../store/albumsstore.h"
#include "../session.h"
#include "../base/action.h"
#include "../action/actiontypes.h"
#include "../albumslistmodel.h"
#include "../network/networkactiontypes.h"
#include "../store/sessionsstore.h"

TestAlbumsStore::TestAlbumsStore(QObject *parent) : QObject(parent) {

}

void TestAlbumsStore::testCreateSession() {
    Session session(QUrl::fromLocalFile("E:/test"), false, 25.0f);
    QSharedPointer<Action> p(new Action(ActionType::CREATE_SESSION, QVariant::fromValue(session)));
    AlbumsStore::get().process(p);
    AlbumsListModel *model = (AlbumsListModel*)AlbumsStore::get().getAlbumsModel();
    QCOMPARE(model->count(), 1);
}

void TestAlbumsStore::testOpenAlbum() {
    Session session(QUrl::fromLocalFile("E:/test"), false, 25.0f);
    QSharedPointer<Action> p(new Action(ActionType::CREATE_SESSION, QVariant::fromValue(session)));
    AlbumsStore::get().process(p);
    QSharedPointer<Action> p2(new Action(ActionType::CREATE_SESSION, 0));
    AlbumsListModel *model = (AlbumsListModel*)AlbumsStore::get().getAlbumsModel();
    QCOMPARE(model->getNotificationCount(0), 0);
    QCOMPARE(model->getNotificationCount(10), -1);
}

void TestAlbumsStore::testReceiveMessage() {
    Session session(QUrl::fromLocalFile("E:/test"), false, 25.0f);
    session.setSessionId("test");
    QSharedPointer<Action> p(new Action(ActionType::CREATE_SESSION, QVariant::fromValue(session)));
    AlbumsStore::get().process(p);
    SessionsStore::get().process(p);
    networkMessage_t message;
    message.clientLink = "test";
    QSharedPointer<Action> p2(new Action(ActionType::RECEIVE_MESSAGE, QVariant::fromValue(message)));
    AlbumsStore::get().process(p2);
    AlbumsListModel *model = (AlbumsListModel*)AlbumsStore::get().getAlbumsModel();
    QCOMPARE(model->getNotificationCount(0), 1);
}

