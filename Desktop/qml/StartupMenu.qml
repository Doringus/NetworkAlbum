import QtQuick 2.13
import QtQuick.Controls 2.12

import "baseComponents"
import NetworkAlbum 1.0

Item {
    id: element

    Rectangle {
        anchors.fill: parent
        color: "#252526"
    }

    Label {
        id: header1Label
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20
        text: "Сетевой фотоальбом"
        color: "#F1F1F1"
        font.pointSize: 20
    }
    Label {
        id: header2Label
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: header1Label.bottom
        anchors.topMargin: 10
        text: "Начало работы"
        color: "#F1F1F1"
        font.pointSize: 15
    }

    MenuButton {
        id: serverBtn
        anchors.top: header2Label.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 30
        height: 110
        width: 340
        btnTitle: "Поделиться фотографиями"
        btnSubText: "Выберите существующую папку, чтобы поделиться ее содержимым"
        btnIcon: "\uf1e0"
        onClicked: {
            ActionProvider.openCreateSessionPopup()
        }
    }

    MenuButton {
        id: connectBtn
        anchors.top: serverBtn.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 10
        height: 110
        width: 340
        btnTitle: "Открыть альбом"
        btnSubText: "При помощи специального кода, подключайтесь и просматривайте, редактируйте и скачивайте содержимое"
        btnIcon: "\uf08e"
        onClicked: {
            ActionProvider.showOpenPopup()
        }
    }
}
