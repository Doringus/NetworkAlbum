import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.folderlistmodel 2.14
import QtQml.Models 2.14

import "../baseComponents"
import NetworkAlbum 1.0

Page {
    id: root

    signal connected()

    Rectangle {
        anchors.fill: parent
        color: "#36393F"
        ColumnLayout {
            anchors.fill: parent
            spacing: 10
            Label {
                Layout.fillWidth: true
                text: "Присоедениться к альбому"
                font.weight: Font.DemiBold
                font.pointSize: 14
                horizontalAlignment: Text.AlignHCenter
                color: "white"
            }
            Label {
                Layout.fillWidth: true
                wrapMode: Text.WordWrap
                text: "Введите приглашение, чтобы присоедениться"
                font.weight: Font.DemiBold
                font.pointSize: 10
                horizontalAlignment: Text.AlignHCenter
                color: "#87909C"
            }
            NTextField {
                id: linkTextField
                backgroundColor: "#303339"
                Layout.fillWidth: true
                Layout.leftMargin: 20
                Layout.rightMargin: 20
                readOnly: false
            }
            RowLayout {
                Layout.fillWidth: true
                anchors.margins: 40
                Label {
                    text: "Скачивать сжатые картинки"
                    font.pointSize: 10
                    color: "#87909C"
                }
                NToggleButton {
                     id: toggleButton
                     text: ""
                }
            }
            NButton {
                Layout.fillWidth: true
                Layout.leftMargin: 20
                Layout.rightMargin: 20
                text: "Подключиться"
                onClicked: {
                    ActionProvider.connectToAlbum(linkTextField.text, toggleButton.checked)
                    connected()
                }
            }
        }
    }


}
