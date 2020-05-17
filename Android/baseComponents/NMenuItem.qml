import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12


MenuItem {
    id: menuItem
    font.pointSize: 12
    contentItem: Item {
        anchors.fill: parent
        Text {
            id: menuItemText
            anchors.left: parent.left
            anchors.right: menuItemIcon.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.rightMargin: 5
            elide: Text.ElideRight
            text: menuItem.text
            leftPadding: 15
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            font: menuItem.font
            color: "#B9BBBE"
        }
        Text {
            id: menuItemIcon
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            rightPadding: 20
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: menuItem.font.pointSize
            font.family: "FontAwesome"
            text: menuItem.icon.name
            color: "#B9BBBE"
        }
    }

    background: Rectangle {
        anchors.centerIn: parent
        width: menuItem.width
        implicitHeight: 40
        color: menuItem.highlighted ? "#212326" : "transparent"
        radius: 4
    }
}
