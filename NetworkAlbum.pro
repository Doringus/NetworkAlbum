QT += quick quickcontrols2 qml widgets concurrent widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGSs

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/action/actionprovider.cpp \
        src/albumslistmodel.cpp \
        src/base/dispatcher.cpp \
        src/changeshistorymodel.cpp \
        src/conversationmodel.cpp \
        src/core.cpp \
        src/imageconverter.cpp \
        src/imagemover.cpp \
        src/main.cpp \
        src/middleware/clientnetworkaccessmiddleware.cpp \
        src/middleware/linkmiddleware.cpp \
        src/middleware/networkaccessmiddleware.cpp \
        src/middleware/sessionfactory.cpp \
        src/network/albumclient.cpp \
        src/network/server.cpp \
        src/network/serverconnection.cpp \
        src/network/tcpconnection.cpp \
        src/network/worker.cpp \
        src/session.cpp \
        src/store/albumsstore.cpp \
        src/store/albumstore.cpp \
        src/store/clientstore.cpp \
        src/store/conversationstore.cpp \
        src/store/eastereggstore.cpp \
        src/store/rootstore.cpp \
        src/store/serveralbumstore.cpp \
        src/store/servernotificationstore.cpp \
        src/store/sessionsstore.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/action/actionprovider.h \
    src/action/actiontypes.h \
    src/albumslistmodel.h \
    src/base/action.h \
    src/base/dispatcher.h \
    src/base/middleware.h \
    src/base/store.h \
    src/changeshistorymodel.h \
    src/conversationmodel.h \
    src/core.h \
    src/imageconverter.h \
    src/imagemover.h \
    src/middleware/clientnetworkaccessmiddleware.h \
    src/middleware/linkmiddleware.h \
    src/middleware/networkaccessmiddleware.h \
    src/middleware/sessionfactory.h \
    src/network/albumclient.h \
    src/network/networkactiontypes.h \
    src/network/server.h \
    src/network/serverconnection.h \
    src/network/tcpconnection.h \
    src/network/worker.h \
    src/session.h \
    src/store/albumsstore.h \
    src/store/albumstore.h \
    src/store/clientstore.h \
    src/store/conversationstore.h \
    src/store/eastereggstore.h \
    src/store/rootstore.h \
    src/store/serveralbumstore.h \
    src/store/servernotificationstore.h \
    src/store/sessionsstore.h
