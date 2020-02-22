import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    width: 600
    height: 50
    Rectangle {
        id: componentTitle
        anchors.left: parent.left
        anchors.top: parent.top
        width: 240
        height: 50
        color: "#36393F"
        Label {
            anchors.fill: parent
            anchors.leftMargin: 40
            color: "white"
            text: "Новый альбом"
            elide: "ElideRight"
            font.weight: Font.DemiBold
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 16
        }
    }

    Rectangle {
        id: toolBar
        anchors.left: componentTitle.right
        anchors.top: parent.top
        anchors.right: parent.right
        height: 50
        color: "#36393F"
        RowLayout {
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.rightMargin: 20
            ToolSeparator { }
            NToolButton {
                icon: "\uf013"
                pointSize: 16
                toolTip: "Настройки"
            }
            NToolButton {
                icon: "\uf128"
                pointSize: 16
                toolTip: "Помощь"
            }
        }
    }

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: toolBar.bottom
        height: 2
        color: "#2B2E33"
    }
}
