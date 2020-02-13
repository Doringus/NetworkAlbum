import QtQuick 2.13
import QtQuick.Controls 2.12

TextField {
    id: root
    height: 40
    font.pointSize: 16
    background: Rectangle {
        border.color: root.activeFocus ? "#40A7E3" : "#C8C9CC"
        radius: 3
    }
}
