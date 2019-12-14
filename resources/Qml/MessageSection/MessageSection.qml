import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import "./ChatListSection"
import "./AreaChat"

import ChatSystem 1.0   //TO DELETE

Item {
    id: _root

    //Selected chat id (-1 means nothing selected)
    property int _selectedChat: -1

    ChatListSection
    {
        id: _chatListSection

        anchors.left: _root.left

        /*If there's a selected chat and the window's app is small,
            don't show the chat list, but only the chat */
        width: _root.width < 500 ? _root.width * (_selectedChat == -1) : (_root.width / 4) + 100
        height: _root.height

        onChatEntered:
        {
            _selectedChat = chatID
            _areaChat.showChat(chatName, picPath, "")
        }

        chatIsSelected: _selectedChat != -1
    }

    AreaChat
    {
        id: _areaChat

        width: _root.width - _chatListSection.width// * (_selectedChat != -1)
        height: _root.height

        anchors.left: _chatListSection.right

        onUnselectedChat: _selectedChat = -1

        //s_chatImageSource:
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
