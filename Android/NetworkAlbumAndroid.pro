QT += quick widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/action/actionprovider.cpp \
        src/base/dispatcher.cpp \
        main.cpp \
        src/conversationmodel.cpp \
        src/core.cpp \
        src/middleware/clientnetworkaccessmiddleware.cpp \
        src/network/serverconnection.cpp \
        src/network/tcpconnection.cpp \
        src/store/albuminfostore.cpp \
        src/store/albumstore.cpp \
        src/store/changesstore.cpp \
        src/store/conversationstore.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

HEADERS += \
    src/action/actionprovider.h \
    src/action/actiontypes.h \
    src/base/action.h \
    src/base/dispatcher.h \
    src/base/middleware.h \
    src/base/store.h \
    src/conversationmodel.h \
    src/core.h \
    src/middleware/clientnetworkaccessmiddleware.h \
    src/network/networkactiontypes.h \
    src/network/serverconnection.h \
    src/network/tcpconnection.h \
    src/store/albuminfostore.h \
    src/store/albumstore.h \
    src/store/changesstore.h \
    src/store/conversationstore.h
