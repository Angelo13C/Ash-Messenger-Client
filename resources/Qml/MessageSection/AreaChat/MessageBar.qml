import QtQuick 2.13
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.3

import MessageSystem 1.0

import "../"
import "../../"

Rectangle       //Top bar of the chat
{
    id: _root

    property int _bounderiesHeight: 20

    width: 400
    height: 40

    color: "#303030"

    function sendMessage()
    {
        var text = _messageArea.text
        MessageSystem.sendTextMessage("0", text)
        _messageArea.text = ""
    }

    RowLayout
    {
        clip: false
        anchors.fill: parent

        spacing: 0

        IconButton   //Attachments button
        {
            Layout.alignment: Qt.AlignBottom
            Layout.preferredWidth: 40; Layout.preferredHeight: width

            _source: "qrc:/Assets/Assets/Images/Chat/Attachments.svg"

            onTriggered: _attachmentDialog.open()

            FileDialog
            {
                id: _attachmentDialog

                title: qsTr("Please choose a file")
                folder: shortcuts.music
                onAccepted:
                {
                    //...
                    this.close()
                }
                Component.onCompleted: visible = false
            }
        }

        Flickable
        {
            Layout.fillHeight: true
            Layout.fillWidth: true

            clip: true

            maximumFlickVelocity: 2000     //Scrollbar's scroll velocity
            flickDeceleration: 5000

            boundsBehavior: Flickable.StopAtBounds
            boundsMovement: Flickable.StopAtBounds
            flickableDirection: Flickable.VerticalFlick

            TextArea.flickable: TextArea
            {
                id: _messageArea

                padding: 0
                leftPadding: 5; rightPadding: 5
                bottomPadding: 5; topPadding: 5        //Center the text in vertical

                color: "#FFFFFF"
                verticalAlignment: Text.AlignVCenter
                placeholderTextColor: "#888888"
                placeholderText: qsTr("Write a message...")

                selectByMouse: true

                wrapMode: Text.WrapAtWordBoundaryOrAnywhere

                Keys.onReturnPressed:
                {
                    if(!(event.modifiers & Qt.ShiftModifier) && !(event.modifiers & Qt.ControlModifier))
                        sendMessage()
                    else    //Otherwise put a \n char, don't steal the signal
                        event.accepted = false
                }

                onLineCountChanged:
                {
                    //Max 10 lines height
                    if(lineCount <= 10)
                        _root.implicitHeight = contentHeight + _bounderiesHeight
                }

                //Remove the background
                background: Item {}
            }
        }

        IconButton   //Send message button
        {
            Layout.alignment: Qt.AlignBottom
            Layout.preferredWidth: 40; Layout.preferredHeight: width

            _source: "qrc:/Assets/Assets/Images/Chat/Send Message.svg"

            onTriggered: sendMessage()
        }
    }
}

