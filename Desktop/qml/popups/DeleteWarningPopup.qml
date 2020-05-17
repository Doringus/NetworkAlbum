import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

import "../baseComponents"

Popup {
    id: root
    anchors.centerIn: parent
    width: 430
    height: 280
    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    clip: true

    signal clicked()

    Overlay.modal: Rectangle {
            color: "#51000000"
    }
    background: Rectangle {
        radius: 8
        color: "#36393F"
    }
    contentItem: Rectangle {
        radius: 8
        color: "#36393F"
        anchors.fill: parent
        Column {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 80
            spacing: 30
            Label {
                anchors.left: parent.left
                anchors.leftMargin: 20
                color: "white"
                text: "Удалить"
                font.weight: Font.Bold
                font.pointSize: 18
            }
            Label {
                anchors.left: parent.left
                anchors.leftMargin: 20
                color: "white"
                text: "Только пустая папка будет удалена"
                font.pointSize: 14
            }
        }

        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            radius: 8
            color: "#2F3136"
            height: 65
        }
        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 15
            radius: 8
            color: "#2F3136"
            height: 65
        }
        NButton {
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 20
            text: "Понятно"
            onClicked: root.clicked()
        }
    }
}
