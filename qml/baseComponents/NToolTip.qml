import QtQuick 2.13
import QtQuick.Controls 2.12

ToolTip {
    id: control
    contentItem: Text {
        text: control.text
        font.bold: true
        font.pointSize: 10
        color: "white"
    }
    background: Rectangle {
        color: "black"
        radius: 4
    }
}
