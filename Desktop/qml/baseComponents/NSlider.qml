import QtQuick 2.13
import QtQuick.Controls 2.12

Slider {
    id: control

    background: Rectangle {
            x: control.leftPadding
            y: control.topPadding + control.availableHeight / 2 - height / 2
            implicitWidth: 200
            implicitHeight: 5
            width: control.availableWidth
            height: implicitHeight
            radius: 2
            color: "#DCDDDE"

            Rectangle {
                width: control.visualPosition * parent.width
                height: parent.height
                color: "#40A7E3"
                radius: 2
            }
        }

        handle: Rectangle {
            x: control.leftPadding + control.visualPosition * (control.availableWidth - width)
            y: control.topPadding + control.availableHeight / 2 - height / 2
            implicitWidth: 13
            implicitHeight: 26
            radius: 3
            color: "white"
            border.color: "#DCDDDE"
        }

    NToolTip {
        parent: control.handle
        visible: control.pressed
        text: control.value.toFixed(1) + "%"
    }
}

