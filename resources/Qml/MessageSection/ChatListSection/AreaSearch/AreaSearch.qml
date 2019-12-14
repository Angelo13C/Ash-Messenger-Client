import QtQuick 2.13

import SearchChatUser 1.0

import "../"
import "../AreaChatList"

Item {
    id: _root

    //Background color
    Rectangle { anchors.fill: _root; color: "#303030" }

    Component.onCompleted:
    {
        SearchChatUser.setAreaObect(this)

        for(var i = 0; i < 5; i++)
            _searchList.model.append({"ID" : -1,
                                      "NAME" : "",
                                      "USERNAME": "",
                                      "CHAT_IMAGE_PATH": " ",
                                      "VISIBLE": false});
    }

    property int _numberOfChats: 0

    //Show a search result
    function showSearchResult(name, username, picPath)
    {
        _searchList.model.set(_numberOfChats , {"ID": _numberOfChats,
                                  "NAME": name,
                                  "USERNAME": "@" + username,
                                  "CHAT_IMAGE_PATH": picPath});

        //Show the result after setting all the parameters
        _searchList.model.get(_numberOfChats).VISIBLE = true

        _numberOfChats++
        return _numberOfChats - 1
    }

    //Clear all the searched results
    function clearSearchList()
    {
        //Hide all the results
        for(var i = 0; i < 5; i++)
            _searchList.model.get(i).VISIBLE = false

        _numberOfChats = 0
    }

    signal chatEntered(int chatID, string chatName, string picPath)

    ListElements        //Chat list
    {
        id: _searchList

        anchors.horizontalCenter: _root.horizontalCenter

        height: _root.height - y
        width: _root.width

        delegate: ChatButton        //Chat button to enter into it
        {
            Component.onCompleted:
            {
                enterChat.connect(_root.chatEntered)
            }

            clip: false
            width: parent.width

            visible: VISIBLE
            _id: ID
            _chatName: NAME
            _lastMessageBlue: USERNAME
            _chatPicturePath: CHAT_IMAGE_PATH

            //Hide the time stamp and the last message
            _timeStamp: ""
            _lastMessage: ""
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
