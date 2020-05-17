#include "testsessionfactory.h"

#include "../session.h"
#include "../middleware/sessionfactory.h"
#include "../base/action.h"
#include "../action/actiontypes.h"

TestSessionFactory::TestSessionFactory(QObject *parent) : QObject(parent) {

}

void TestSessionFactory::testCreateSession() {
    SessionFactory factory;
    Session session(QUrl("TestUrl"), false, 25.0);
    QList<QVariant> args = {QVariant(QUrl("TestUrl")), QVariant(false), QVariant(25.0)};
    QSharedPointer<Action> p(new Action(ActionType::CREATE_SESSION, args));
    p = factory.process(p);
    QCOMPARE(p->getErrorString(), "");
    QCOMPARE(p->getData<Session>().getAlbumPath(), session.getAlbumPath());
    QCOMPARE(p->getData<Session>().getCompression(), session.getCompression());
    QCOMPARE(p->getData<Session>().hasCopy(), session.hasCopy());
}

void TestSessionFactory::testCreateDublicateSession() {
    SessionFactory factory;
    QList<QVariant> args = {QVariant(QUrl("TestUrl")), QVariant(false), QVariant(25.0)};
    QSharedPointer<Action> p(new Action(ActionType::CREATE_SESSION, args));
    factory.process(p);
    QSharedPointer<Action> p2(new Action(ActionType::CREATE_SESSION, args));
    p2 = factory.process(p2);
    QCOMPARE(p2->getErrorString(), "Папка уже используется!");
}

void TestSessionFactory::testCreateEmptySession() {
    SessionFactory factory;
    QList<QVariant> args = {QVariant(QUrl()), QVariant(false), QVariant(25.0)};
    QSharedPointer<Action> p(new Action(ActionType::CREATE_SESSION, args));
    p = factory.process(p);
    QCOMPARE(p->getErrorString(), "Не указана папка альбома!");
}

