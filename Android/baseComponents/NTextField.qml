import QtQuick 2.13
import QtQuick.Controls 2.12

TextField {
    id: root

    property bool hasError: false
    property color backgroundColor: "white"

    height: 40
    font.pointSize: 16
    background: Rectangle {
        border.color: {
            if(root.activeFocus) {
                root.hasError ? "#F04747" : "#40A7E3"
            } else {
                root.hasError ? "#F04747" : "#C8C9CC"
            }
        }
        radius: 3
    }
}
