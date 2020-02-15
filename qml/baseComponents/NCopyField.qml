import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root

    property string text: "SAMPLE TEXT"
    property bool isDark: false

    property color borderColor: isDark ? "#222428" : "#C8C9CC"
    property color borderActiveColor: "#40A7E3"
    property color fieldColor: isDark ? "#2B2E33": "white"
    property color textColor: isDark ? "white" : "black"

    width: 200
    height: 40

    TextField {
        id: textField
        height: root.height
        width: root.width
        font.pointSize: 16
        text: root.text
        selectByMouse: true
        readOnly: true
        color: textColor

        background: Rectangle {
            id: rect
            color: fieldColor
            border.color: borderColor //parent.activeFocus ? borderActiveColor: borderColor
            radius: 3
            ColorAnimation  {
                id: activeAnimation
                target: rect
                property: "border.color"
                to: "#3CA374"
                duration: 600
                onFinished: {
                    copyBtn.text = "Копировать"
                    backAnimation.start()
                }
            }
            ColorAnimation {
                id: backAnimation
                target: rect
                property: "border.color"
                to: borderColor
                duration: 300
            }
        }


        NButton {
            id: copyBtn
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.margins: 5
            text: "Копировать"
            onClicked: {
                activeAnimation.start()
                textField.selectAll()
                textField.copy()
                textField.select(0, 0)
                copyBtn.text = "Скопировано"
            }
        }
    }
}


