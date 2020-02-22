import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root

    width: 320
    height: 600

    property color otherMessageColor: "#182533"
    property color mineMessageColor: "#2B5278"

    Rectangle {
        anchors.fill: parent
        color: "transparent"
    }

    ListView {
        id: chatList
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: messageFieldRect.top
        anchors.topMargin: 20
        anchors.bottomMargin: 10
        verticalLayoutDirection: ListView.BottomToTop
        boundsBehavior: Flickable.StopAtBounds
        spacing: 12
        model: 10

        delegate: Rectangle {
            anchors.right: parent.right
            anchors.rightMargin: 10
            width: Math.min(message.implicitWidth + 20, chatList.width / 4 * 3)
            height: message.implicitHeight + 20
            color: mineMessageColor
            radius: 8
            Label {
                id: message
                anchors.fill: parent
                anchors.margins: 12
                color: "white"
                font.pointSize: 11
                wrapMode: Label.Wrap
                text: "TESTTESTTEESTTESTESTESTESTEST"
            }
        }

        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AsNeeded
            contentItem: Rectangle {
                implicitWidth: 6
                implicitHeight: 100
                radius: width / 2
                color: "#9A9A9C"
            }
        }
    }

    Rectangle {
        id: messageFieldRect
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: "#36393F"
        height: 70
        z:2
        Rectangle {
            anchors.fill: parent
            anchors.leftMargin: 15
            anchors.rightMargin: 15
            anchors.bottomMargin: 20
            radius: 8
            color: "#40444B"
            TextArea {
                anchors.fill: parent
                font.pointSize: 10
                verticalAlignment: Text.AlignVCenter
                placeholderText: "Написать пользователю"
                placeholderTextColor: "#87909C"
                color: "white"
                wrapMode: TextArea.Wrap
                selectByMouse: true
                Keys.onReturnPressed: {}
            }
        }
    }

}
