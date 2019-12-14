import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import "./AreaChatList"
import "./AreaSearch"

import SearchChatUser 1.0

Item {
    id: _root

    signal chatSelected(int chatID)
    signal chatEntered(int chatID, string chatName, string picPath)
    property bool chatIsSelected

    SearchBar
    {
        id: _searchBar

        width: _root.width

        anchors
        {
            top: _root.top
            horizontalCenter: _root.horizontalCenter
        }

        //Clear the search list and show the correct area when searching a text
        onSearchingText:
        {
            _areaSearch.clearSearchList()

            _areas_stcklyt.currentIndex = searching
        }
    }

    StackLayout                 //Areas manager
    {
        id: _areas_stcklyt

        width: _root.width
        height: _root.height - _searchBar.height

        anchors
        {
            top: _searchBar.bottom
            horizontalCenter: _root.horizontalCenter
        }

        currentIndex: 0             //Default = AreaChatList

        AreaChatList
        {
            id: _areaChatList

            //When a chat in the list is selected, enter in it
            Component.onCompleted: chatSelected.connect(_root.chatEntered)

            _chatIsSelected: chatIsSelected
        }

        AreaSearch
        {
            id: _areaSearch

            Component.onCompleted: chatEntered.connect(_root.chatEntered)
        }
    }
}
