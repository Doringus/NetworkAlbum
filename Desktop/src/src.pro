QT += quick quickcontrols2 qml widgets concurrent widgets testlib

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGSs


SOURCES += \
        action/actionprovider.cpp \
        albumslistmodel.cpp \
        base/dispatcher.cpp \
        changeshistorymodel.cpp \
        conversationmodel.cpp \
        core.cpp \
        imageconverter.cpp \
        imagemover.cpp \
        main.cpp \
        middleware/clientnetworkaccessmiddleware.cpp \
        middleware/linkmiddleware.cpp \
        middleware/networkaccessmiddleware.cpp \
        middleware/sessionfactory.cpp \
        network/albumclient.cpp \
        network/server.cpp \
        network/serverconnection.cpp \
        network/tcpconnection.cpp \
        network/worker.cpp \
        session.cpp \
        store/albumsstore.cpp \
        store/albumstore.cpp \
        store/clientstore.cpp \
        store/conversationstore.cpp \
        store/eastereggstore.cpp \
        store/rootstore.cpp \
        store/serveralbumstore.cpp \
        store/servernotificationstore.cpp \
        store/sessionsstore.cpp \
        tests/testalbumsstore.cpp \
        tests/testsessionfactory.cpp \
        tests/testsessionsstore.cpp

HEADERS += \
    action/actionprovider.h \
    action/actiontypes.h \
    albumslistmodel.h \
    base/action.h \
    base/dispatcher.h \
    base/middleware.h \
    base/store.h \
    changeshistorymodel.h \
    conversationmodel.h \
    core.h \
    imageconverter.h \
    imagemover.h \
    middleware/clientnetworkaccessmiddleware.h \
    middleware/linkmiddleware.h \
    middleware/networkaccessmiddleware.h \
    middleware/sessionfactory.h \
    network/albumclient.h \
    network/networkactiontypes.h \
    network/server.h \
    network/serverconnection.h \
    network/tcpconnection.h \
    network/worker.h \
    session.h \
    store/albumsstore.h \
    store/albumstore.h \
    store/clientstore.h \
    store/conversationstore.h \
    store/eastereggstore.h \
    store/rootstore.h \
    store/serveralbumstore.h \
    store/servernotificationstore.h \
    store/sessionsstore.h \
    tests/testalbumsstore.h \
    tests/testsessionfactory.h \
    tests/testsessionsstore.h

RESOURCES += ../qml.qrc
MOC_DIR = $${BUILD_PATH}/moc/
