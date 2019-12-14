import QtQuick 2.13
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.13

import "../.."

Item {
    id: root

    width: 350
    height: 64

    property string _chatPicturePath
    property alias _chatName: _chatName.text
    property alias _lastMessageBlue: _blueMessage.text
    property alias _lastMessage: _message.text
    property alias _timeStamp: _timeStamp.text

    signal update()
    onUpdate: _chatPicture.setPath(_chatPicturePath, _chatName.text.charAt(0))

    property int _id
    signal enterChat(int id)

    Rectangle   //Chat button background
    {
        id: _background

        anchors.fill: parent

        opacity: 0
    }

    RowLayout
    {
        Layout.leftMargin: 10

        spacing: 10

        anchors.fill: parent

        ChatImage       //Chat picture
        {
            id: _chatPicture

           _size: 50

           Layout.alignment: Qt.AlignHCenter
           Layout.leftMargin: 10
        }


        Item
        {
            Layout.fillWidth: true
            Layout.fillHeight: true

            ColumnLayout
            {
                anchors.fill: parent

                spacing: -10

                Item
                {
                    Layout.fillWidth: true
                    height: 20

                    RowLayout
                    {
                        anchors.fill: parent

                        spacing: 5

                        Text        //Chat name
                        {
                            id: _chatName

                            Layout.fillWidth: true
                            font.bold: true

                            color: "#ffffff"

                            maximumLineCount: 1
                            elide: Text.ElideRight

                            text: "Chat name"
                        }

                        Text        //Timestamp of last message
                        {
                            id: _timeStamp

                            Layout.alignment: Qt.AlignRight
                            Layout.rightMargin: 10

                            color: "#737373"

                            text: "15:40"
                            horizontalAlignment: Text.AlignRight

                        }
                    }
                }

                RowLayout
                {
                    //Layout.fillWidth: true

                    spacing: 5

                    Text        //Last message of the chat
                    {
                        id: _blueMessage

                        color: "#399fed"

                        //If the text is too long, elid it
                        //width: _chat_msarea.width - x - 10
                        Layout.fillWidth: _message.text === ""

                        elide: Text.ElideRight

                        text: "Last message:"
                    }

                    Text        //Last message of the chat
                    {
                        id: _message

                        color: "#8a8a8a"

                        //If the text is too long, elid it
                        //width: _chat_msarea.width - x - 10
                        Layout.fillWidth: true
                        Layout.rightMargin: 10

                        elide: Text.ElideRight

                        text: "Last message"
                    }
                }
            }
        }
    }

    MouseArea
    {
        anchors.fill: _background

        cursorShape: Qt.PointingHandCursor  //How the cursor looks if is hover this area

        hoverEnabled: true

        onEntered: _background.opacity = 0.1
        onExited: {
            if(!pressed)
                _background.opacity = 0 }

        preventStealing: true       //It blocks the menu from swiping and it allows the onReleased to work properly

        onReleased: {
            if(containsMouse)       //If the user selects the chat
            {
                _background.opacity = 0.1
                enterChat(_id)
            }
            else
                _background.opacity = 0
        }
    }
}


