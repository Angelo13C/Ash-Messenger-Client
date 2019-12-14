import QtQuick 2.13
import QtGraphicalEffects 1.0

MouseArea
{
    id: _root

    width: 40; height: 40

    property int _sourceSize: 20
    property string _source

    signal triggered()

    state: "notHovered"     //Default state

    cursorShape: Qt.PointingHandCursor  //How the cursor looks if is hover this area

    hoverEnabled: true
    preventStealing: true       //It allows the onReleased to work properly

    onEntered: this.state = "hovered"
    onExited: if(!pressed)
            this.state = "notHovered"

    onPressed: this.state = "pressed"

    onReleased: {
        if(containsMouse)
        {
            this.state = "hovered"
            triggered()
        }
        else       //If the user selects the chat
            this.state = "notHovered"
    }

    Image
    {
        id: _image
        anchors.centerIn: parent

        fillMode: Image.PreserveAspectFit

        source: _source

        width: _sourceSize
        height: _sourceSize
        sourceSize.width: _sourceSize
        sourceSize.height: _sourceSize
    }

    ColorOverlay
    {
        id: _colorOverlay
        anchors.fill: _image
        source: _image

        cached: true        //For efficiency
    }

    states:
    [
        State
        {
            name: "notHovered"
            PropertyChanges { target: _colorOverlay; color: "#777777" }
        },
        State
        {
            name: "hovered"
            PropertyChanges { target: _colorOverlay; color: "#DDDDDD" }
        },
        State
        {
            name: "pressed"
            extend: "hovered"
            PropertyChanges {  }
        }
    ]

    transitions:
    [
        Transition {
            from: "*"
            to: "*"
            PropertyAnimation { target: _colorOverlay; properties: "color"; duration: 200 }
        }
    ]
}


