#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QDebug>
#include <QSystemTrayIcon>
#include <QApplication>

#include "base/action.h"
#include "base/dispatcher.h"
#include "action/actionprovider.h"
#include "middleware/sessionfactory.h"
#include "core.h"

#include "tests/testsessionfactory.h"
#include "tests/testalbumsstore.h"
#include "tests/testsessionsstore.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    Core core;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
  //  QTest::qExec(new TestSessionFactory, argc, argv);
  //  QTest::qExec(new TestAlbumsStore, argc, argv);
  //  QTest::qExec(new TestSessionsStore, argc, argv);
    return app.exec();
}
