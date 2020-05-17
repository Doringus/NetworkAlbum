import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

import "../baseComponents"

Popup {
    id: popup

    property alias globalLink: globalLinkField.text
    property alias localLink: localLinkField.text

    anchors.centerIn: parent
    width: 600
    height: 540
    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    clip: true

    Overlay.modal: Rectangle {
            color: "#51000000"
    }
    background: Rectangle {
        radius: 6
    }

    Label {
        id: title
        anchors.top: parent.top
        anchors.topMargin: 15
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Доступ"
        font.pointSize: 20
        color: "#40A7E3"
    }
    Column {
        anchors.top: title.bottom
        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.topMargin: 40
        spacing: 20
        Label {
            id: pathToAlbumLabel

            text: "Ключ доступа"
            font.capitalization: Font.AllUppercase
            font.bold: true
            font.pointSize: 10
            color: "#87909C"
        }
        Label {
            text: "Поделитесь данным приглашением"
            font.pointSize: 10
            wrapMode: "WrapAtWordBoundaryOrAnywhere"
            color: "#87909C"
        }
        NCopyField {
            id: globalLinkField
            width: 530
        }
        Label {
            text: "Используйте данный код, если клиент находится не в вашей локальной сети.\n
Для корректной работы необходимо открыть порт 22222"
            wrapMode: Text.WordWrap
            font.pointSize: 10
            color: "#FAA61A"
        }
        NCopyField {
            id: localLinkField
            width: 530
        }
        Label {
            text: "Используйте данный код, если клиент находится в вашей локальной сети"
            font.pointSize: 10
            color: "#FAA61A"
        }
        Label {
            text: "Внимание! Приглашения работают только для одного пользователя"
            font.pointSize: 10
            color: "#FAA61A"
        }
    }
}
