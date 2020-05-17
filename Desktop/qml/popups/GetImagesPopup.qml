import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

import "../baseComponents"

Popup {
    id: root

    property alias albumName: nameField.text
    property alias albumSize: sizeField.text

    signal clicked()

    anchors.centerIn: parent
    width: 550
    height: 460
    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    clip: true

    Overlay.modal: Rectangle {
            color: "#51000000"
    }
    background: Rectangle {
        radius: 6
    }

    onClosed: {
        link = ""
        scaled = false
    }

    contentItem: Rectangle {
        anchors.fill: parent
        color: "transparent"
        Column {
            anchors.fill: parent
            anchors.bottomMargin: 20
            anchors.topMargin: 15
            spacing: 50
            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Открыть альбом"
                font.pointSize: 20
                color: "#40A7E3"
            }

            Label {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 40
                text: "Название альбома"
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
                font.pointSize: 12
                color: "#87909C"
            }
            NTextField {
                id: nameField
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 40
                readOnly: true
            }
            Label {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 40
                text: "Размер альбома"
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
                font.pointSize: 12
                color: "#87909C"
            }
            NTextField {
                id: sizeField
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 40
                readOnly: true
            }
        }

        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            height: 75
            radius: 6
            color: "#F6F6F7"
            NButton {
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.rightMargin: 40
                anchors.bottomMargin: 20
                text: "Подключиться"
                onClicked: root.clicked()
            }
        }
    }
}
