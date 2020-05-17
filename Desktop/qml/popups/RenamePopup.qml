import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

import "../baseComponents"

Popup {
    id: root

    property alias errorString: errorLabel.text
    property alias fileName: nameField.text

    signal clicked()

    anchors.centerIn: parent
    width: 550
    height: 300
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
        //folderName = ""
    }

    contentItem: Rectangle {
        anchors.fill: parent
        color: "transparent"
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 20
            spacing: 50
            Label {
                text: "Переименовать"
                font.pointSize: 20
                color: "#40A7E3"
            }
            Column {
                Layout.minimumWidth: 510
                spacing: 10
                NTextField {
                    id: nameField
                    anchors.left: parent.left
                    anchors.right: parent.right
                    validator: RegExpValidator { regExp: /[0-9A-Za-zА-Яа-яё\s]+/ }
                    selectByMouse: true
                }
                Label {
                    id: errorLabel
                    anchors.left: parent.left
                    anchors.right: parent.right
                    font.pointSize: 10
                    color: "#F04747"
                    visible: text !== ""
                }
            }
            NButton {
                Layout.alignment: Qt.AlignRight
                text: "Сохранить"
                onClicked: {
                    root.clicked()
                }
            }
        }
    }
}
