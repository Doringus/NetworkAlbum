import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.folderlistmodel 2.14
import QtQml.Models 2.14

import "../baseComponents"
import NetworkAlbum 1.0


Page {
    id: root

    signal opened()
    signal canceled()

    property alias albumName: albumNameLabel.text
    property alias albumSize: albumSizeLabel.text
    property alias errorString: errorLabel.text

    header: Rectangle {
        height: 80
        color: "#36393F"
        NToolButton {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.margins: 15
            icon: "\uf060"
            pointSize: 16
            onClicked: canceled()
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "#36393F"
        Column {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: 15
            spacing: 10
            Label {
                anchors.left: parent.left
                anchors.right: parent.right
                text: "Присоедениться к альбому"
                font.weight: Font.DemiBold
                font.pointSize: 14
                horizontalAlignment: Text.AlignHCenter
                color: "white"
            }
            Label {
                Layout.fillWidth: true
                wrapMode: Text.WordWrap
                text: "Имя альбома"
                font.weight: Font.DemiBold
                font.pointSize: 10
                horizontalAlignment: Text.AlignHCenter
                color: "#87909C"
            }
            Label {
                id: albumNameLabel
                Layout.fillWidth: true
                wrapMode: Text.WordWrap
                font.weight: Font.DemiBold
                font.pointSize: 10
                horizontalAlignment: Text.AlignHCenter
                color: "white"
            }
            Label {
                Layout.fillWidth: true
                wrapMode: Text.WordWrap
                text: "Размер альбома(мб)"
                font.weight: Font.DemiBold
                font.pointSize: 10
                horizontalAlignment: Text.AlignHCenter
                color: "#87909C"
            }
            Label {
                id: albumSizeLabel
                Layout.fillWidth: true
                wrapMode: Text.WordWrap
                font.weight: Font.DemiBold
                font.pointSize: 10
                horizontalAlignment: Text.AlignHCenter
                color: "white"
            }
            Label {
                id: errorLabel
                anchors.left: parent.left
                anchors.margins: 40
                font.pointSize: 10
                color: "#F04747"
                visible: text !== ""
            }
        }

        Column {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 15
            spacing: 10
            NButton {
                text: "Подключиться"
                anchors.left: parent.left
                anchors.right: parent.right
                onClicked: {
                    ActionProvider.getImages()
                    opened()
                }
            }
            NButton {
                text: "Отмена"
                anchors.left: parent.left
                anchors.right: parent.right
                onClicked: canceled()
            }
        }


    }


}
