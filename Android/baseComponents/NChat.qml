import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root

    property var chatModel
    property color otherMessageColor: "#182533"
    property color mineMessageColor: "#2B5278"

    signal messageWritten(string message)

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
        model: chatModel

        delegate: Rectangle {
            anchors.right: model.owner ? parent.right : undefined
            anchors.left:  model.owner ? undefined : parent.left
            anchors.rightMargin: 10
            anchors.leftMargin: 10
            width: Math.min(message.implicitWidth + 40, chatList.width / 4 * 3)
            height: message.implicitHeight + 20
            color: model.owner ? mineMessageColor : "#FFFFFF"
            radius: 8
            Label {
                id: message
                anchors.fill: parent
                anchors.margins: 12
                color: model.owner ? "white" : "black"
                font.pointSize: 11
                wrapMode: Label.Wrap
                text: model.message
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
                id: messageArea
                anchors.fill: parent
                font.pointSize: 10
                verticalAlignment: Text.AlignVCenter
                placeholderText: "Написать пользователю"
                placeholderTextColor: "#87909C"
                color: "white"
                wrapMode: TextArea.Wrap
                selectByMouse: true
                Keys.onReturnPressed: {
                 //   messageWritten(text)
                  //  text = ""
                }
                rightPadding: 120
                NButton {
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.margins: 10
                    width: 100
                    text: "Отправить"
                    onClicked: {
                        Qt.inputMethod.reset()
                        messageWritten(messageArea.text)
                        messageArea.text = ""

                    }
                }
            }
        }
    }

}
