import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2
import QtMultimedia 5.14

import "../baseComponents"

Popup {
    id: root

    onOpened: video.play()
    onClosed: video.stop()
    anchors.centerIn: parent
    width: 800
    height: 600
    clip: true
    modal: true

    contentItem: Video {
        id: video
        width: 800
        height: 600
        source: "qrc:///res/easterEgg.avi"
    }
}
