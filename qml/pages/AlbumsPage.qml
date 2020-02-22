import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../baseComponents"

Page {
    header: NMainToolBar{}
    Item {
        id: root
        anchors.fill: parent
        Popup {
            id: codePopup
            width: 440
            height: 150
            modal: true
            anchors.centerIn: parent
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
            Overlay.modal: Rectangle {
                    color: "#51000000"
            }
            background: Item {
                Rectangle {
                    anchors.fill: parent
                    color: "#36393F"
                    radius: 8
                }
            }
            contentItem: Rectangle {
                color: "transparent"
                Column {
                    spacing: 10
                    Label {
                        text: "Отправьте другу код"
                        color: "white"
                        font.capitalization: Font.AllUppercase
                        font.weight: Font.DemiBold
                        font.pointSize: 12
                    }
                    NCopyField {
                        anchors.right: parent.right
                        isDark: true
                        width: 410
                    }
                    Label {
                        text: "Внимание! Приглашение работает только для одного пользователя"
                        font.pointSize: 10
                        color: "#FAA61A"
                    }
                }
            }
        }

        Rectangle {
            anchors.fill: parent
            color: "#2F3136"
        }
        GridView {
            id: grid
            anchors.fill: parent
            anchors.leftMargin: 50
            anchors.topMargin: 30
            boundsBehavior: Flickable.StopAtBounds
            flow: GridView.LeftToRight
            snapMode: GridView.SnapToRow
            cacheBuffer: 0
            model: 20
            cellHeight: 240
            cellWidth: 360
            ScrollBar.vertical: ScrollBar {
                policy: ScrollBar.AlwaysOn
                contentItem: Rectangle {
                    implicitWidth: 6
                    implicitHeight: 100
                    radius: width / 2
                    color: "#9A9A9C"
                }
            }
            header: Rectangle {
                width: 350
                height: 240
                color: "transparent"
                AlbumNewItem {
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
            delegate: AlbumListItem {
                onClicked: {
                    codePopup.open()
                }
            }
        }
    }
}
