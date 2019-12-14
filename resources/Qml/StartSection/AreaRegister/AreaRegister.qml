import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12

import AuthenticationSystem 1.0

import "../"
import "../StartTextInput"            //Import StartTextInput.qml

Item {
    id: _root
    signal clicked()                //Go to the other area signal
    signal succesfulRegister()      //When the registration is successful

    Column
    {
        id: _textFields_clmn

        anchors.centerIn: _root

        spacing: Math.ceil(Screen.desktopAvailableHeight / 20) //! ~50

        StartTextInputEmail            //Email text field
        {
            id: _email_txtInp
        }

        StartTextInputPassword            //Password text field
        {
            id: _password_txtInp
            _confirmPassword: false
        }

        StartTextInputPassword            //Confirm password text field
        {
            id: _confirmPassword_txtInp
            _confirmPassword: true
        }

        StartButtonLoginRegister            //Register button
        {
            id: _register_btn
            text: qsTr("CREATE ACCOUNT")
            onClicked: _root.register()

            Text        //Login text errors
            {
                id: _registerError_txt
                color: "#d41313"
                visible: false
                anchors
                {
                    bottom: _register_btn.top
                    horizontalCenter: _register_btn.horizontalCenter
                }
            }
        }

        StartButtonNoBackground
        {
            id: _goToOtherArea_btn
            loginArea: false

            TapHandler                          //Detect mouse / touch click on the Rectangle
            {
                longPressThreshold: 255         //Max time to emit tap event between start tap and release
                onTapped: _root.clicked()        //Trigger the signal
            }
        }
    }

    ErrorHandler
    {
        id: _errorHandler
    }

    function resetTextInput()       //Reset the field of the input texts
    {
        _email_txtInp._text = ""
        _password_txtInp._text = ""
        _confirmPassword_txtInp._text = ""
    }

    function register()                 //Try to register and find errors
    {
        _errorHandler._error = false        //Delete errorManager text content
        _registerError_txt.visible = false     //Hide register error text

        //Save texts in variables
        var email = _email_txtInp._text
        var password = _password_txtInp._text
        var confirmPassword = _confirmPassword_txtInp._text

        //Try to find errors in the text fields
        var emailErrorCode = _errorHandler.validateEmail(email);
        var passwordErrorCode =_errorHandler.validatePassword(password);
        var confirmPasswordErrorCode =_errorHandler.validateConfirmPassword(password, confirmPassword);

        //Show errors if there are
        _email_txtInp.showError(emailErrorCode)
        _password_txtInp.showError(passwordErrorCode)
        _confirmPassword_txtInp.showError(confirmPasswordErrorCode)

        //Reset input texts' content
        if (_errorHandler._error)
        {
            resetTextInput()    //Reset the field of the input texts
        }
        else        //Either, communicate with c++ to try to register, if the email/password are wronged (or other things), show errors
        {
            //Pass this istance to c++ to then call the registerResult function of this object
            AuthenticationSystem.registerEmail(email, password, this)
        }
    }

    function registerResult(result)
    {
        //If the register is successful
        if(result === true)
        {
            succesfulRegister()
        }
        else
        {
            resetTextInput()    //Reset the field of the input texts

            _registerError_txt.text = qsTr("A user with that email is already registered!")
            _registerError_txt.visible = true
        }
    }
}














































































































/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
