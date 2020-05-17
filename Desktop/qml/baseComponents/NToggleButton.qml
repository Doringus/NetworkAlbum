import QtQuick 2.13
import QtQuick.Controls 2.12

Switch {
    id: control
    text: qsTr("Switch")

    indicator: Rectangle {
        implicitWidth: 48
        implicitHeight: 26
        x: control.leftPadding
        y: parent.height / 2 - height / 2
        radius: 13
        color: control.checked ? "#2095D0" : "#72767D"

        Rectangle {
            x: control.checked ? parent.width - width - 2 : 2
            y: parent.height / 2 - height / 2
            width: 22
            height: 22
            radius: 11
            color: "#ffffff"
            Behavior on x {
                NumberAnimation {
                    duration: 100
                }
            }
        }
    }

    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: control.down ? "#17a81a" : "#21be2b"
        verticalAlignment: Text.AlignVCenter
        leftPadding: control.indicator.width + control.spacing
    }
}
