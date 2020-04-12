import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root
   // property url imagePath: "pics/logo.png"
    property alias imagePath: image.source
    property string imageName: "IMAGENAME"
    property bool selected: false

    signal clicked()
    signal doubleClicked()
    signal ctrlClicked()

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
        Drag.active: area.drag.active && selected
        Drag.hotSpot.x: 0
        Drag.hotSpot.y: 0
        Drag.mimeData: { "text/plain": "test"/*item.display */}
        Drag.dragType: Drag.Automatic
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
            cache: true
            asynchronous: true
        }
    }

    Rectangle{
        id: test
        width: 50
        height: 50
       // visible: false
    }

    MouseArea {
        id: area
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onEntered: { root.state='Hovering'}
        onExited: { root.state=''}
        drag.target: backgroundRect
        onPressed: {
            test.grabToImage(function(result) {
                            backgroundRect.Drag.imageSource = result.url
            })
        }

        onClicked: {
            if ((mouse.button == Qt.LeftButton) && (mouse.modifiers & Qt.ControlModifier)) {
                root.ctrlClicked()
            } else {
                root.clicked()
            }
        }
        onDoubleClicked: {
            root.doubleClicked()
        }
    }

}
