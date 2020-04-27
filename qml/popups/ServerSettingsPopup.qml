import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

import "../baseComponents"

Popup {
    id: root

    property alias showNotifications: notificationToggle.checked
    property alias closableWindow: windowToggle.checked
    property bool showAlbumSettings: false
    property string albumReserveFolder
    property bool notificationCache
    property bool closableCache

    signal saveSettings()

    onClosed: {
        notificationToggle.checked = notificationCache
        windowToggle.checked = closableCache
    }

    height: showAlbumSettings ? 560 : 410
    width: 500
    modal: true
    Overlay.modal: Rectangle {
            color: "#51000000"
    }
    background: Rectangle {
        color: "#36393F"
        radius: 6
    }
    contentItem: Rectangle {
        anchors.fill: parent
        color: "#36393F"
        radius: 6
        Rectangle {
            id: header
            height: 40
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: 20
            color: "transparent"
            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 20
                anchors.rightMargin: 20
                Label {
                    font.pointSize: 18
                    color: "white"
                    text: "Настройки"
                }
                NToolButton {
                    Layout.alignment: Qt.AlignRight
                    icon: "\uf00d"
                    toolTip: "Закрыть"
                    pointSize: 16
                    onClicked: root.close()
                }
            }
        }

        Column {
            id: column
            anchors.top: header.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 20
            spacing: 30
            Rectangle {
                visible: root.showAlbumSettings
                anchors.left: parent.left
                anchors.right: parent.right
                color: "#292B2F"
                radius: 8
                height: 150
                Column {
                    anchors.fill: parent
                    anchors.margins: 20
                    spacing: 40
                    Label {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        color: "white"
                        text: "Резервная папка"
                        font.weight: Font.Medium
                        font.pointSize: 16
                    }
                    NTextField {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        readOnly: true
                        text: albumReserveFolder
                        selectByMouse: true
                    }

                }
            }
            Rectangle {
                anchors.left: parent.left
                anchors.right: parent.right
                color: "#292B2F"
                radius: 8
                height: 200
                Column {
                    anchors.fill: parent
                    anchors.margins: 20
                    spacing: 20
                    Label {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        color: "white"
                        text: "Прочие настройки"
                        font.weight: Font.Medium
                        font.pointSize: 16
                    }
                    RowLayout {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        spacing: 20
                        NToggleButton {
                            id: notificationToggle
                            text: ""
                        }
                        Label {
                            color: "white"
                            font.pointSize: 14
                            text: "Windows уведомления"
                        }
                    }
                    RowLayout {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        spacing: 20
                        NToggleButton {
                            id: windowToggle
                            text: ""
                        }
                        Label {
                            color: "white"
                            font.pointSize: 14
                            text: "Выключать при закрытии"
                        }
                    }

                }
            }
            RowLayout {
                anchors.left: parent.left
                anchors.right: parent.right
                NButton {
                    Layout.alignment: Qt.AlignRight
                    text: "Сохранить"
                    onClicked: {
                        notificationCache = notificationToggle.checked
                        closableCache = windowToggle.checked
                        saveSettings()
                    }
                }
            }


        }
    }
}
