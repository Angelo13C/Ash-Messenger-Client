import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13

import "../"

Item {
    id: _root

    //Background color
    Rectangle { anchors.fill: _root; color: "#222222" }

    //Unselect the chat
    signal unselectedChat()

    function showChat(chatName, picSource, chatInfo)
    {
        _chatInfoBar._chatName = chatName
        _chatInfoBar._chatPicSource = picSource
        _chatInfoBar._chatInfo = chatInfo
    }

    ColumnLayout
    {
        anchors.fill: parent

        ChatInfoBar
        {
            id: _chatInfoBar

            Layout.fillWidth: true
            height: 50

            Component.onCompleted: unselectedChat.connect(_root.unselectedChat)
        }

        Item        //Area where all messages are displayed
        {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        MessageBar
        {
            Layout.fillWidth: true
        }

    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
