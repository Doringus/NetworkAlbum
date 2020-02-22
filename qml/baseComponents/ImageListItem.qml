import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root
    property url imagePath: "pics/logo.png"
    property string imageName: "IMAGENAME"

    signal clicked()

    width: 200
    height: 200


    states: [
        State {
            name: "Hovering"
            PropertyChanges {
                target: titleRect
                color: "#18191C"
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
        color: "#202225"
        Text {
            anchors.fill: parent
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
            anchors.fill: parent
            sourceSize.width: width
            sourceSize.height: height
            source: imagePath
        }
    }


    MouseArea {
        id: area
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onEntered: { root.state='Hovering'}
        onExited: { root.state=''}
        onClicked: {
            root.clicked()
        }
    }

}
