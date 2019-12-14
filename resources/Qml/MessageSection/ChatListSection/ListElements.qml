import QtQuick 2.13

import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

ListView        //Chat list
{
    id: _root

    clip: true

    highlightFollowsCurrentItem: false

    keyNavigationWraps: false   //IDK

    maximumFlickVelocity: 15000     //Scrollbar's scroll velocity

    pixelAligned: true      //IDK

    model: ListModel {}

    spacing: 0

    flickableDirection: Flickable.VerticalFlick
    boundsBehavior: Flickable.StopAtBounds

    ScrollBar.vertical: ScrollBar {     //Scrollbar
        //Show the scrollbar only when needed
        visible: size != 1

        width: 6
        anchors.left: _root.rigth

        opacity: _scrollbar_mouseArea.containsMouse ? 1 : 0.5

        contentItem: Rectangle      //Scrollbar foreground
        {
            radius: 4
            color: "#777777"
        }

        background : Rectangle      //Scrollbar background
        {
            radius: 4
            color: "#55555555"
        }

        policy: ScrollBar.AsNeeded

        MouseArea{
            id: _scrollbar_mouseArea
            anchors.fill: parent

            hoverEnabled: true      //Also if there isn't any mouse button clicked

            //Propagates mouse events behind the mouse area
            onClicked: mouse.accepted = false;
            onPressed: mouse.accepted = false;
            onReleased: mouse.accepted = false;
            onDoubleClicked: mouse.accepted = false;
            onPositionChanged: mouse.accepted = false;
            onPressAndHold: mouse.accepted = false;

            propagateComposedEvents: true
        }
    }
}
