import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

/*Symbol Legend
! = For my computer*/

Rectangle
{
    id: _root

    //Text input focus size
    width: Math.ceil(Screen.desktopAvailableWidth / 5)      //! 350
    height: Math.ceil(Screen.desktopAvailableHeight / 20)    //! 40

    clip: false

    color: "#00000000"; border.color: "#00000000"

    readonly property string assetPath: "qrc:/Assets/Assets/"

    property bool _password: false      //If the component is for password holding
    property bool _showPassword: _password ? false : true      //If the password is shown (changed by the button passwordShower

    Rectangle                   //Show/Hide password manager
    {
        id: _passwordShower
        visible: _password
        color: "#00000000"
        width: Math.ceil(Screen.desktopAvailableWidth * Screen.desktopAvailableHeight / 45000)     //! 40
        height: Math.ceil(Screen.desktopAvailableWidth * Screen.desktopAvailableHeight / 65000)   //! 28

        anchors
        {
            verticalCenter: _input_txtfld.verticalCenter
            left: _input_txtfld.right
            leftMargin: Math.ceil(Screen.desktopAvailableWidth / 80)    //! ~21
        }

        TapHandler                          //Detect mouse / touch click on the Rectangle
        {
            longPressThreshold: 255         //Max time to emit tap event between start tap end release
            onTapped: _showPassword = !_showPassword
        }

        Image                               //Show showPassword image
        {
            id: _passwordShower_img
            anchors.centerIn: _passwordShower

            source: assetPath + "Images/Eye_ShowPassword.svg"

            sourceSize {             //Image size
                width: Math.ceil(Screen.desktopAvailableWidth * Screen.desktopAvailableHeight / 60000)  //! ~30
                height: width//Math.ceil(Screen.desktopAvailableWidth * Screen.desktopAvailableHeight / 60000) //! ~30 (same as width)
            }
        }
    }

    property string _imageType: "User"

    Image {                            //The image before the textField
        id: _type_img

        source:                     //Image source
            switch (_imageType)
            {
                case "User": assetPath + "Images/User.svg"; break;
                case "Password": assetPath + "Images/Padlock.svg"; break;
            }

        sourceSize {             //Image size
            width: Math.ceil(Screen.desktopAvailableWidth * Screen.desktopAvailableHeight / 40000)  //! 45
            height: Math.ceil(Screen.desktopAvailableWidth * Screen.desktopAvailableHeight / 40000) //! 45 (same as width)
        }

        anchors
        {
            bottom: _lineUnderText_rect.top; bottomMargin: Math.ceil(Screen.desktopAvailableHeight / 500) //! 3
            left: _root.left; leftMargin: Math.ceil(Screen.desktopAvailableWidth / 300) //! 6
        }
    }

    property alias _placeholder: _input_txtfld.placeholderText       //Text placeholder
    property alias _validator: _input_txtfld.validator               //Text validator (only letters..)
    property alias _text: _input_txtfld.text                         //Get access to current text outsides

    property bool _error: false

    function showError(errorCode)
    {
        _errorMessage_txt.text = errorCode
        _error = errorCode !== false
    }

    TextField {                     //TextField
        id: _input_txtfld

        color: "#000000"

        bottomPadding: 0; topPadding: 0        //Center the text in vertical

        horizontalAlignment: TextField.AlignLeft
        verticalAlignment: TextField.AlignBottom       //Text alignment (the vertical alignment is useless because there is the anchor.bottom)

        anchors
        {
            fill: _root
            left: _type_img.left; leftMargin: Math.ceil(Screen.desktopAvailableWidth / 30)    //! 56
            bottomMargin: Math.ceil(Screen.desktopAvailableHeight / 48)    //! 22
        }

        font
        {
            pointSize: Math.ceil(Screen.desktopAvailableHeight / 60)    //! ~18
            capitalization: Font.MixedCase
        }

        renderType: Text.QtRendering
        selectByMouse: true                 //The user can select the text with the mouse

        echoMode: _showPassword ? TextInput.Normal : TextInput.Password

        background: Rectangle { visible: false }      //Hides background Rectangle

        placeholderTextColor: _error ? "#d41313" : "#adadad"
    }

    Rectangle           //Line under the text
    {
        id: _lineUnderText_rect
        width: _root.width; height: Math.ceil(Screen.desktopAvailableHeight / 2000)  //! 1

        anchors {  top: _input_txtfld.bottom; bottomMargin: Math.ceil(Screen.desktopAvailableHeight / 400) } //! 3

        color: _error ? "#d41313" : "#555555"
    }

    Text {                      //Error message text
        id: _errorMessage_txt

        visible: _error

        anchors
        {
            top: _lineUnderText_rect.top; topMargin: Math.ceil(Screen.desktopAvailableHeight / 400) //! -3
        }

        font.pointSize: 12

        color: "#d41313"
    }
}


