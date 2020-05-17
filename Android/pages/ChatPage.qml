import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.folderlistmodel 2.14
import QtQml.Models 2.14

import "../baseComponents"
import "../popups"
import NetworkAlbum 1.0



Page {
    signal back()
    header: Rectangle {
        color: "#36393F"
        height: 50
        NToolButton {
            anchors.left: parent.left
            anchors.leftMargin: 10
            icon: "\uf060"
            iconColor: "#87909C"
            toolTip: "Назад"
            height: 50
            onClicked: {
                back()
            }
        }
    }
    Rectangle {
        anchors.fill: parent
        color: "#36393F"
    }

    NChat {
        anchors.fill: parent
        chatModel: ConversationStore.conversationModel
        onMessageWritten: {
            ActionProvider.sendMessage(message)
        }
    }

}

