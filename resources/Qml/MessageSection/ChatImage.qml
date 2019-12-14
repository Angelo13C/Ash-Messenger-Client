import QtQuick 2.0
import QtGraphicalEffects 1.13


Item
{
    id: _root

    property int _size

    function setPath(path, letter)
    {
        _chatImage.source = path
        _noImageLetter.text = letter
    }

    width: _size
    height: width

    Item
    {
        id: _image

        anchors.fill: parent

        visible: _chatImage.source != ""

        Rectangle        //Mask shape
        {
            id: _chatImageMaskShape

            anchors.fill: _chatImage

            radius: width / 2
        }

        OpacityMask     //Opacity mask (effect) to the chat image
        {
            anchors.fill: _chatImageMaskShape
            source: if(_chatImage.source != "") _chatImage
            maskSource: _chatImageMaskShape
        }

        Image       //Chat image
        {
            id: _chatImage
            //Not visible because the opacity mask is going to be the circle image
            visible: false

            sourceSize.width: _size
            sourceSize.height: width

            anchors.centerIn: parent
        }
    }


    Rectangle        //If there isn't an image
    {
        id: _noImage

        anchors.fill: parent

        //Make a circle
        radius: width / 2

        //Random circle color
        Component.onCompleted:
        {
            var randomColors = [
                "#B87502",
                "#119134",
                "#114691",
                "#00B1BA",
                "#BA003B",
                "#9000B8",
                "#B2B800"
            ]

            color = randomColors[Math.floor((Math.random() * randomColors.length))]
        }

        Text {
            id: _noImageLetter

            //Show if there's no image
            visible: _chatImage.source == ""

            color: "#FFFFFF"    //White

            anchors.centerIn: parent

            font.pixelSize: 20
        }
    }
}
