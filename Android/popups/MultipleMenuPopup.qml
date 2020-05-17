import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

import "../baseComponents"

Rectangle {
    id: root

    signal clearSelected()
    signal openMove()

    property alias files: filesLabel.text

    radius: 6

    Rectangle {
        anchors.fill: parent
        radius: 6
        Label {
            id: filesLabel
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.left: parent.left
            anchors.right: row.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            elide: "ElideRight"
            font.pointSize: 14
        }
        RowLayout {
            id: row
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            NToolButton {
                icon: "\uf0ec"
                onClicked: openMove()
                pointSize: 14
            }
            NToolButton {
                icon: "\uf00d"
                pointSize: 14
                onClicked: {
                    clearSelected()
                }
            }
        }
    }
}
