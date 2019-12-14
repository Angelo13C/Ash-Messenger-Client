import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import QtGraphicalEffects 1.0

import ChatSystem 1.0

import "../"

Item {
    id: _root

    property bool _chatIsSelected

    //Background color
    Rectangle { anchors.fill: _root; color: "#303030" }

    property int _numberOfChats: 0

    Component.onCompleted: { ChatSystem.setQmlChatListInstance(this) }

    function addChat(name, chatImagePath)
    {
        _chats_view.model.append({ID: _numberOfChats,
                                 NAME: name,
                                 CHAT_IMAGE_PATH: chatImagePath,
                                 LAST_MESSAGE_BLUE: "",
                                 LAST_MESSAGE: "",
                                 TIME_STAMP: ""})

        setChatMessage(_numberOfChats, "ok", "okk", "15:32")
        _numberOfChats++
        return _numberOfChats - 1
    }

    function setChatMessage(chatID, lastMessageBlue, lastMessage, timeStamp)
    {
        _chats_view.model.set(chatID, {"LAST_MESSAGE_BLUE": lastMessageBlue,
                                  "LAST_MESSAGE": lastMessage,
                                  "TIME_STAMP": timeStamp})
    }

    //Select a chat
    signal chatSelected(int chatID, string chatName, string picPath)
    function selectChat(chatID)
    {
        _chats_view.currentIndex = chatID
        var chat = _chats_view.model.get(chatID)
        chatSelected(chatID, chat.NAME, chat.CHAT_IMAGE_PATH)
    }

    Component {
            id: _highlight
            Rectangle {
                //If there is any chat selected, show the highlight
                visible: _chatIsSelected

                width: _chats_view.width; height: 64

                color:  "#336EAEF3";

                y: _chats_view.currentItem.y
            }
    }

    ListElements        //Chat list
    {
        id: _chats_view

        //anchors.fill: _root
        anchors{
            horizontalCenter: _root.horizontalCenter
        }

        height: _root.height - y
        width: _root.width

        highlight: _highlight

        delegate: ChatButton        //Chat button to enter into it
        {
            Component.onCompleted:
            {
                enterChat.connect(_root.selectChat)
            }

            clip: false
            width: parent.width

            _id: ID
            _chatName: NAME
            _chatPicturePath: CHAT_IMAGE_PATH
            _lastMessageBlue: LAST_MESSAGE_BLUE
            _lastMessage: LAST_MESSAGE
            _timeStamp: TIME_STAMP
        }
    }
}



/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
