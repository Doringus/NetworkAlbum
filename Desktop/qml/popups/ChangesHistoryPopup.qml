import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

import "../baseComponents"

Popup {
    id: root

    property var historyModel

    anchors.centerIn: parent
    width: 800
    height: 700
    clip: true
    modal: true

    Overlay.modal: Rectangle {
            color: "#51000000"
    }
    background: Rectangle {
        radius: 8
        color: "#36393F"
    }

    contentItem: Rectangle {
        anchors.fill: parent
        color: "#36393F"
        border.color: "#202225"
        radius: 8
        Rectangle {
            id: header
            height: 60
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            color: "#2F3136"
            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 20
                anchors.rightMargin: 20
                Label {
                    font.pointSize: 18
                    color: "white"
                    text: "История изменений"
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
        ListView {
            anchors.top: header.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.topMargin: 20
            boundsBehavior: Flickable.StopAtBounds
            model: historyModel
            ScrollBar.vertical: ScrollBar{}
            delegate: Rectangle {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 20
                height: 40
                color: "transparent"
                RowLayout {
                    anchors.fill: parent
                    spacing: 10
                    Label {
                        color: "#43B581"
                        font.family: "FontAwesome"
                        text: "\uf07b"
                        font.pointSize: 18
                    }
                    Label {
                        color: "white"
                        font.pointSize: 18
                        text: "Файл"
                    }
                    Label {
                        Layout.maximumWidth: 200
                        color: "white"
                        font.pointSize: 18
                        text: model.from
                        font.underline: true
                        elide: Text.ElideRight
                        ToolTip.text: text
                        ToolTip.visible: fromArea.containsMouse
                        MouseArea {
                            id: fromArea
                            hoverEnabled: true
                            anchors.fill: parent
                        }
                    }
                    Label {
                        color: "white"
                        font.pointSize: 18
                        text: "был изменен"
                    }
                    Label {
                        color: "#43B581"
                        font.pointSize: 18
                        text: "\uf061"
                        font.family: "FontAwesome"
                    }
                    Label {
                        Layout.maximumWidth: 200
                        color: "white"
                        font.pointSize: 18
                        text: model.to
                        font.underline: true
                        elide: Text.ElideRight
                        ToolTip.text: text
                        ToolTip.visible: toArea.containsMouse
                        MouseArea {
                            id: toArea
                            hoverEnabled: true
                            anchors.fill: parent
                        }
                    }
                }
            }
        }
    }

}
