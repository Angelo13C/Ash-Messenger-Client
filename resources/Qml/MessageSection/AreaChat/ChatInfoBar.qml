import QtQuick 2.13
import QtQuick.Layouts 1.11

import "../"
import "../../"

Rectangle       //Top bar of the chat
{
    id: _root

    property string _chatPicSource
    on_ChatPicSourceChanged: chatPic.setPath(_chatPicSource, _chatName.text.charAt(0))
    property alias _chatName: _chatName.text
    property alias _chatInfo: _chatInfo.text

    signal unselectedChat()

    width: 400
    height: 50

    color: "#303030"

    RowLayout
    {
        anchors.fill: parent
        spacing: 5

        IconButton   //Back arrow image
        {
            Layout.fillHeight: true; Layout.preferredWidth: height

            _source: "qrc:/Assets/Assets/Images/Chat/Unselect_Chat.svg"

            onTriggered: unselectedChat()
        }

        ChatImage       //Chat image
        {
            id: _chatPic

            _size: 40
        }

        Column
        {
            Layout.fillWidth: true
            Layout.preferredHeight: _chatPic.height

            topPadding: 5
            spacing: 5

            Text {
                id: _chatName

                text: "Chat Name"

                color: "#DDDDDD"

            }

            Text {
                id: _chatInfo

                text: "Chat Info"

                color: "#4D5D6E"
            }
        }

        IconButton   //Menu Dots icon
        {
            Layout.fillHeight: true; Layout.preferredWidth: height

            _source: "qrc:/Assets/Assets/Images/Chat/Menu Dots.svg"
        }
    }

}

