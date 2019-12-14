//pragma Singleton
import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12

import AuthenticationSystem 1.0

import "../"
import "../StartTextInput"            //Import StartTextInput.qml

Item {
    id: _root
    signal clicked()                //Go to the other area signal
    signal succesfulLogin()      //When the login is successful

    Column
    {
        id: _textFields_clmn

        anchors.centerIn: _root
        spacing: Math.ceil(Screen.desktopAvailableHeight / 20) //! ~50

        StartTextInputEmail            //Email text field
        {
            id: _email_txtInp

            _text: "delete@text"        //TO DELETE
        }

        StartTextInputPassword            //Password text field
        {
            id: _password_txtInp
            _confirmPassword: false

            _text: "deleteText"        //TO DELETE
        }

        StartButtonLoginRegister                //Login button
        {
            id: _login_btn
            text: qsTr("LOG IN")
            onClicked: _root.login()

            Text        //Login text errors
            {
                id: _loginError_txt
                color: "#d41313"
                visible: false
                anchors
                {
                    bottom: _login_btn.top
                    horizontalCenter: _login_btn.horizontalCenter
                }
            }
        }

        StartButtonNoBackground
        {
            loginArea: true

            TapHandler                          //Detect mouse / touch click on the Rectangle
            {
                longPressThreshold: 255         //Max time to emit tap event between start tap end release
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
    }

    function login()                 //Try to login and find errors
    {
        _errorHandler._error = false        //Delete errorManager text content
        _loginError_txt.visible = false     //Hide login error text

        //Save texts in variables
        var email = _email_txtInp._text
        var password = _password_txtInp._text

        //Try to find errors in the text fields
        var emailErrorCode = _errorHandler.validateEmail(email)
        var passwordErrorCode = _errorHandler.validatePassword(password)

        //Show errors if there are
        _email_txtInp.showError(emailErrorCode)
        _password_txtInp.showError(passwordErrorCode)

        //Reset input texts' content if there are been some errors
        if (_errorHandler._error)
        {
            resetTextInput()    //Reset the field of the input texts
        }
        else   //Either, communicate with c++ to try to login, if the email/password are wronged (or other things), show errors
        {
            //Pass this istance to c++ to then call the loginResult function of this object
            AuthenticationSystem.loginEmail(email, password, this)
        }
    }

    function loginResult(result)
    {
        //If the login is successful
        if(result === true)
        {
            succesfulLogin()
        }
        else
        {
            resetTextInput()    //Reset the field of the input texts

            _loginError_txt.text = qsTr("The inserted password and email aren't correct!")
            _loginError_txt.visible = true
        }
    }
}


























































































/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
