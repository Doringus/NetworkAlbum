import QtQuick 2.13
import QtQuick.Controls 2.12

Rectangle {
    id:rect
    property string checkedColor: "#2095D0"
    property string uncheckedColor: "#72767D"
    property bool isChecked: false
    signal checkedChanged(bool check)

    width: 42
    height: 25
    radius: 16
    color: isChecked ? checkedColor:uncheckedColor

    Rectangle {
        id: checkBall
        width: 18
        height: 18
        radius: 9
        color: "#FFFFFF"
        anchors.verticalCenter: parent.verticalCenter
        x: isChecked ? 21:3
        NumberAnimation on x {
            running: false
            id:anim
            from: 3
            to: 21
        }
        NumberAnimation on x {
            running: false
            id:backAnim
            from: 21
            to: 3
        }
    }
    MouseArea {
        id:mouseArea
        anchors.fill: parent
        onClicked: {
            if(rect.isChecked){
                rect.isChecked = false
                rect.color = uncheckedColor
                backAnim.start()
                checkedChanged(false)
            } else {
                rect.isChecked = true
                rect.color = checkedColor
                anim.start()
                checkedChanged(true)
            }
        }
    }

}

