import QtQuick 2.13
import QtQuick.Controls 2.13

import AdvertisePanel 1.0

Item {
    clip: true
    width: 1200; height: 800

    property var _imageSources: //Images to show on the panel (in the correct order)
    [
        "qrc:/Assets/Assets/Images/StartSection/GitHub.png",
        "qrc:/Assets/Assets/Images/StartSection/Reddit.png",
        "qrc:/Assets/Assets/Images/StartSection/Twitter.png"
    ]
    property var _imageWebURLs: //Web broser URLs of the images
    [
        "GitHub.com/Angelo13C",
        "Reddit.com/user/Angelo13C",
        "Twitter.com/Angelo13C_"
    ]

    function setImage(index)
    {
        //If there aren't images left, switch to the first image
        if(index >= _swipeView.count)
            index = 0
        else if(index < 0)
            index = _swipeView.count - 1

        _swipeView.setCurrentIndex(index)
    }

    SwipeView {
        id: _swipeView
        anchors.fill: parent

        currentIndex: _pageIndicator.currentIndex

        interactive: false
        Repeater {
            model: _imageSources.length
            Loader {
                active: true//SwipeView.isCurrentItem || SwipeView.isNextItem || SwipeView.isPreviousItem
                sourceComponent: Image {
                    source: _imageSources[index]

                    anchors.fill: parent

                    sourceSize.height: 1460
                    sourceSize.width: 730

                    MouseArea
                    {
                        anchors.fill: parent

                        cursorShape: Qt.PointingHandCursor

                        onPressed: AdvertisePanel.openBrowserURL(_imageWebURLs[_swipeView.currentIndex])
                    }
                }
            }
        }
    }

    PageIndicator {
        id: _pageIndicator
        interactive: true
        count: _swipeView.count
        currentIndex: _swipeView.currentIndex

        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        //Restart the timer when the page is changed
        onCurrentIndexChanged: _timer.restart()

        delegate: Rectangle
        {
            implicitWidth: 15
            implicitHeight: 15

            radius: width / 2
            color: "#FFFFFF"

            opacity: index === _pageIndicator.currentIndex ? 1 : pressed ? 0.75 : 0.4

            Behavior on opacity
            {
                OpacityAnimator { duration: 400 }
            }
        }
    }

    Timer
    {
        id: _timer
        running: true
        repeat: true
        interval: 3000
        onTriggered: {
            setImage(_swipeView.currentIndex + 1)
        }
    }

    MouseArea
    {
        width: 50; height: 50

        anchors
        {
            right: parent.right; rightMargin: 20
            verticalCenter: parent.verticalCenter
        }
        opacity: 0.4

        cursorShape: Qt.PointingHandCursor

        onPressed: setImage(_swipeView.currentIndex + 1)
        hoverEnabled: true
        onEntered: opacity = 0.9
        onExited: opacity = 0.4

        Image {
            source: "qrc:/Assets/Assets/Images/StartSection/Right_Image_Advertise_Panel.svg"

            anchors.fill: parent
        }
    }
    MouseArea
    {
        width: 50; height: 50

        anchors
        {
            left: parent.left; leftMargin: 20
            verticalCenter: parent.verticalCenter
        }

        cursorShape: Qt.PointingHandCursor

        opacity: 0.4
        onPressed: setImage(_swipeView.currentIndex - 1)
        hoverEnabled: true
        onEntered: opacity = 0.9
        onExited: opacity = 0.4

        Image {
            source: "qrc:/Assets/Assets/Images/StartSection/Right Image Advertise Panel.svg"

            mirror: true
            anchors.fill: parent
        }
    }
}


