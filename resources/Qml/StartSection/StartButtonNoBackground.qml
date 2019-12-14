import QtQuick 2.13
import QtQuick.Window 2.12

Rectangle
{
    id: _root
    color: "#00000000"          //Invisible but the TapHandler works

    property bool loginArea             //Is the login area?

    width: loginArea ? Math.ceil(Screen.desktopAvailableWidth / 9) : Math.ceil(Screen.desktopAvailableWidth / 7)        //! 187 : 240
    height: Math.ceil(Screen.desktopAvailableHeight / 40)                                                               //! 27

    Text
    {
        id: _content_txt

        text: loginArea ? qsTr("No account? Register") : qsTr("Already got account? Login")

        anchors.fill: _root

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter        //Text alignment (the vertical alignment is useless)

        font
        {
            pointSize: Math.ceil(Screen.desktopAvailableHeight / 90) //! ~15
            underline: true
            bold: true
        }

        color: "#333333"
    }
}
