import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import ChatSystem 1.0

import "./StartSection"
import "./MessageSection"

ApplicationWindow {
    id: _root
    objectName: "main"

    visible: true

    width: 1400; height: 650
    minimumWidth: 400; minimumHeight: 450

    title: qsTr("Ash (Messenger)")
    color: "#DDDDDD"

    Item                 //Sections manager
    {
        id: _sections

        state: "StartSection"   //Default section is the StartSection
        states: [
            State { name: "StartSection" },
            State { name: "MessageSection" }
        ]

        anchors.fill: parent

        Loader  //Dynamically load the StartSection
        {
            active: parent.state == "StartSection"

            sourceComponent:
                StartSection    //Start section
                {
                    onMessageSection:
                    {
                        _sections.state = "MessageSection"
                        ChatSystem.loadQmlChats(false)
                    }
                }

            anchors.fill: parent
        }

        Loader  //Dynamically load the MessageSection
        {
            active: parent.state == "MessageSection"

            sourceComponent:
                MessageSection    //Message section
                {

                }

            anchors.fill: parent
        }

    }
    property QtObject utilObj: Utilities
}
