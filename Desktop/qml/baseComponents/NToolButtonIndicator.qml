import QtQuick 2.13
import QtQuick.Controls 2.12


Item {
    id: root
    property color iconColor: "#B9BBBE"
    property color iconHoveredColor: "#DCDDDE"
    property color iconCheckedColor: "#39A5DB"
    property string icon: "\uf002"
    property string toolTip: "tip"
    property int pointSize: 12
    property bool isActivated: true

    signal activated()
    signal deactivated()

    height: 25
    width: 25

    state: isActivated ? 'Pressed' : ''

    Rectangle {
        anchors.fill: parent
        color: "transparent"
        Label {
            id: icon
            anchors.fill: parent
            color: root.iconColor
            font.family: "FontAwesome"
            font.pointSize: root.pointSize
            text: root.icon
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        NToolTip {
            id: toolTip
            text: root.toolTip
        }
    }

    states: [
        State {
            name: "Hovering"
            PropertyChanges {
                target: icon
                color: root.iconHoveredColor
            }
        },
        State {
            name: "Pressed"
            PropertyChanges {
                target: icon
                color: root.iconCheckedColor
            }
        }
    ]

    transitions: [
        Transition {
            from: ""
            to: "Hovering"
            reversible: true
            ColorAnimation {
                duration: 200
            }
        },
        Transition {
            from: "Pressed"
            to: ""
            ColorAnimation {
                duration: 200
            }
        },
        Transition {
            from: "Hovering"
            to: "Pressed"
            reversible: true

            ColorAnimation {
                duration: 200
            }
        }
    ]
    MouseArea {
        id: area
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: {
            toolTip.close()
            if(root.state == 'Pressed') {
                root.state = 'Hovering'
                root.deactivated()
            } else {
                root.state = 'Pressed'
                root.activated()
            }

        }
        onEntered: {
            toolTip.open()
            if(root.state != 'Pressed') root.state = 'Hovering'
        }
        onExited: {
            toolTip.close()
            if(root.state != 'Pressed') root.state = ''
        }
    }
}
