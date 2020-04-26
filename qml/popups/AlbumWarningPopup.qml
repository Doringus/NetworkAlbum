import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

import "../baseComponents"

Popup {
    id: root

    signal closeAlbum()

    anchors.centerIn: parent
    width: 430
    height: 300
    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    clip: true

    Overlay.modal: Rectangle {
            color: "#51000000"
    }
    background: Rectangle {
        radius: 8
        color: "#36393F"
    }
    contentItem: Rectangle {
        anchors.fill: parent
        radius: 8
        color: "#36393F"
        Label {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.leftMargin: 20
            anchors.topMargin: 20
            color: "white"
            text: "Удалить альбом"
            font.weight: Font.Bold
            font.pointSize: 18
        }
        Rectangle {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 20
            anchors.rightMargin: 20
            height: 90
            color: "#E19517"
            radius: 8
            Label {
                anchors.fill: parent
                font.pointSize: 14
                color: "white"
                text: "Вы уверены, что хотите удалить альбом? Это действие отключит активного клиента."
                padding: 10
                wrapMode: Text.WordWrap
                textFormat: Text.AutoText
                font.weight: Font.Medium
            }
        }

        NButton {
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.margins: 20
            color: "#F04747"
            hoverColor: "#D84040"
            pressColor: "#C03939"
            text: "Удалить"
            onClicked: root.closeAlbum()
        }
        NButton {
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.margins: 20
            color: "transparent"
            hoverColor: "transparent"
            pressColor: "transparent"
            text: "Отмена"
            onClicked: root.close()
        }
    }
}
