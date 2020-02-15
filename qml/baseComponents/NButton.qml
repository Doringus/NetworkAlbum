import QtQuick 2.13
import QtQuick.Controls 2.12

Item {
    id: root
    property string text: ""
    property color color: "#40A7E3"
    property color hoverColor: "#39A5DB"
    property color pressColor: "#2095D0"
    property int fontSize: 14

    signal clicked()

    height: 35
    width: 120

    Rectangle {
        id: rect
        anchors.fill: parent
        radius: 3
        color: root.color
        Text {
            id: innerText
            text: root.text
            anchors.centerIn: parent
            color: "white"
            font.pixelSize: fontSize
            font.capitalization: Font.AllUppercase
        }
    }
    states: [
        State {
            name: "Hovering"
            PropertyChanges {
                target: rect
                color: hoverColor
            }
        },
        State {
            name: "Pressed"
            PropertyChanges {
                target: rect
                color: pressColor
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
            from: "Hovering"
            to: "Pressed"
            reversible: true
            ColorAnimation {
                duration: 200
            }
        },
        Transition {
            from: "Pressed"
            to: ""
            reversible: true
            ColorAnimation {
                duration: 200
            }
        }
    ]
    MouseArea {
          hoverEnabled: true
          cursorShape: Qt.PointingHandCursor
          anchors.fill: root
          onEntered: { root.state='Hovering'}
          onExited: { root.state=''}
          onClicked: {root.clicked()}
          onPressed: { root.state="Pressed" }
          onReleased: {
              if (containsMouse)
                root.state="Hovering";
              else
                root.state="";
          }
        }
}
