pragma Singleton
import QtQuick 2.0

Item {
    objectName: "utilities"
    property int _screenWidth
    property int _screenHeight

    function setScreen(screen)
    {
        _screenWidth = screen.width
        _screenHeight = screen.height
    }
}
