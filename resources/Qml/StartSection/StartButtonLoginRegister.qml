import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Window 2.12


RoundButton                 //Login/Register button
{
    id: _root

    Material.background: "#ababab"
    width: Math.ceil(Screen.desktopAvailableWidth / 5) //! ~300
    height: Math.ceil(Screen.desktopAvailableHeight / 20) //! ~50
    radius: Math.ceil(Screen.desktopAvailableHeight / 70) //! ~15

    font
    {
        pointSize: Math.ceil(Screen.desktopAvailableHeight / 70) //! ~15 (same as radius)
    }
}





/*##^## Designer {
    D{i:0;height:0;width:0}
}
 ##^##*/
