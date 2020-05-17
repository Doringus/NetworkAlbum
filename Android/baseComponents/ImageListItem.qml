import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root
    property alias imagePath: image.source
    property string imageName: "IMAGENAME"
    property bool selected: false

    signal clicked()
    signal doubleClicked()
    signal ctrlClicked()
    signal menuClicked()
    signal pressAndHold()

    width: 200
    height: 200

    states: [
        State {
            name: "Hovering"
            PropertyChanges {
                target: titleRect
                color: root.selected ? "#40A7E3" : "#18191C"
            }
        }
    ]

    transitions: Transition {
        from: ""
        to: "Hovering"
        reversible: true

        ColorAnimation {
            duration: 100
        }
    }

    Rectangle {
        id: backgroundRect
        anchors.fill: parent
        color: "transparent"
        border.color: "#202225"
        radius: 8
    }

    Rectangle {
        id: titleRect
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 65
        radius: 8
        color: root.selected ? "#2095D0" : "#202225"
        Text {
            anchors.fill: parent
            anchors.rightMargin: 30
            font.pointSize: 14
            color: "white"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            elide: Text.ElideRight
            text: imageName
        }
    }
    Rectangle {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: titleRect.top
        radius: 8
        color: "transparent"
        Image {
            id: image
            anchors.fill: parent
            sourceSize.width: width
            sourceSize.height: height
            cache: false
            asynchronous: true
        }

    }

    MouseArea {
        id: area
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onEntered: { root.state='Hovering'}
        onExited: { root.state=''}
        NToolButton {
            id: iconMore
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 18
            anchors.right: parent.right
            anchors.rightMargin: 20
            icon: "\uf142"
            onClicked: {
                menuClicked()
            }
        }
        onClicked: {
            root.clicked()

        }
        onPressAndHold: {
            root.pressAndHold()
        }
    }

}
