import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import QtGraphicalEffects 1.0

import SearchChatUser 1.0

import "../.."

Rectangle       //Top menu
{
    id: _root

    height: 50

    color: "#2b2b2b"

    signal searchingText(bool searching)

    RowLayout
    {
        anchors.fill: parent
        spacing: 10

        IconButton
        {
            id: _menu_btn

            Layout.fillHeight: true
            Layout.preferredWidth: height

            Layout.leftMargin: 5

            _source: "qrc:/Assets/Assets/Images/Chat/Menu.svg"
        }

        Rectangle
        {
            Layout.fillWidth: true
            Layout.preferredHeight: 30

            Layout.rightMargin: 20

            color: "#444444"

            radius: 4

            TextField
            {
                clip: true      //Hide text outside the input field

                verticalAlignment: TextInput.AlignVCenter
                anchors.centerIn: parent

                color: "#ffffff"

                height: parent.height
                width: parent.width - 20

                placeholderText: qsTr("Search")
                placeholderTextColor: "#818A80"

                selectByMouse: true

                topPadding: 0
                bottomPadding: 0

                background: Item{}      //Remove the background

                onTextChanged:
                {
                    if(text != "")
                    {
                        searchingText(true)
                        //If there are at least two chars and the first is a @
                        if(text.length > 1 && text.charAt(0) === "@")
                            SearchChatUser.searchUsername(text)
                    }
                    else
                        searchingText(false)
                }
            }
        }
    }
}
