import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.12

import TranslatorManager 1.0

import "./AreaLogin"
import "./AreaRegister"
import "./AdvertisePanel"

import "../"

Item {
    id: _root

    signal messageSection()

    RowLayout
    {
        anchors.fill: parent

        spacing: 50

        StackLayout                 //Areas manager
        {
            id: _stackLayout
            Layout.fillHeight: true
            Layout.preferredWidth: 500
            Layout.maximumWidth: 500

            Layout.alignment: Qt.AlignLeft

            currentIndex: 0             //Default = areaLogin
            opacity: 1

            OpacityAnimator
            {
                id: _dulling
                target: _stackLayout
                from: 1
                to: 0
                duration: 100
                onFinished:                 //When the animation end, change the area and start the other animation
                {
                    _stackLayout.currentIndex = !_stackLayout.currentIndex
                    _undulling.start()
                }
            }
            OpacityAnimator
            {
                id: _undulling
                target: _stackLayout
                from: 0
                to: 1
                duration: 100
            }

            AreaLogin                  //Area Login
            {
                id: _startAreaLogin

                onClicked: _dulling.start()      //Switch to the other area starting the animation

                onSuccesfulLogin: messageSection()
            }

            AreaRegister               //Area Register
            {
                id: _startAreaRegister

                onClicked: _dulling.start()      //Switch to the other area starting the animation

                onSuccesfulRegister: messageSection()
            }
        }

        AdvertisePanel
        {
            visible: Utilities._screenWidth > 200

            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }

    /*
    Rectangle                           //Rectangle that is at the bottom of the window (utility)
    {
        id: _utility_rect
        height: 50
        width: _root.width
        x: 0; y: _root.height - height      //Anchor to the bottom - center (it's the only way)

        color: "#ababab"

        Row
        {
            anchors.fill: _utility_rect
            layoutDirection: Qt.RightToLeft
            spacing: 10
            rightPadding: 20

            Button
            {
                id: _language_btn
                width: height
                height: _utility_rect.height

                icon
                {
                    color: "#00000000"
                    source: "qrc:/Assets/Assets/Images/Flags/Flag_it.svg"
                    width: 50
                    height: width
                }

                onClicked: TranslatorManager.setLanguage(TranslatorManager.ITALY)
            }

            Button
            {
                id: _languageUK_btn
                width: height
                height: _utility_rect.height

                icon
                {
                    color: "#00000000"
                    source: "qrc:/Assets/Assets/Images/Flags/Flag_uk.svg"
                    width: 50
                    height: width
                }

                onClicked: TranslatorManager.setLanguage(TranslatorManager.UNITED_KINGDOM)
            }
        }
    }*/
}






















































/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
