import QtQuick 2.13


/*VALIDATE RETURNS:
  TRUE = there is an error :(
  FALSE = no error :D
*/

Item {
    id: _root

    property bool _error: false //Set invisible by default

    property var _errorCodes:                       //DEFAULT ERROR CODES WITH RESPECTIVE CONTENTS
    {
        "EMAIL_SHORT": qsTr("The email is too short!"),                    //The email is too short
        "EMAIL_NO_SNAIL": qsTr("The email doesn't contain a snail (@) !"),
        "EMAIL_NO_LOCAL_PART": qsTr("The email can't start with the snail (@) !"),
        "EMAIL_NO_DOMAIN": qsTr("The email can't end with the snail (@) !"),
        "PASSWORD_SHORT": qsTr("The password is too short!"),             //The password is too short
        "CONFIRM_PASSWORD_NOT_EQUAL": qsTr("The confirm password is not equal to the password!")          //The confirm password is not equal to the password
    }

    function validateEmail(email)
    {
        if (email.length < 3)              //If the email has less than 3 characters (that is the minimum for a valid email)
        {
            _error = true
            return _errorCodes["EMAIL_SHORT"]
        }
        if(email.split("@").length-1 < 1)
        {
            _error = true;
            return _errorCodes["EMAIL_NO_SNAIL"]
        }
        if(email[0] === "@")
        {
            _error = true;
            return _errorCodes["EMAIL_NO_LOCAL_PART"]
        }
        if(email[email.length - 1] === "@")
        {
            _error = true;
            return _errorCodes["EMAIL_NO_DOMAIN"]
        }

        return false
    }

    function validatePassword(password)
    {
        if (password.length < 5)           //If the password has less than 5 characters (that is the minimum for a valid password)
        {
            _error = true
            return _errorCodes["PASSWORD_SHORT"]
        }
        return false
    }

    function validateConfirmPassword(password, confirmPassword)
    {
        if (confirmPassword !== password)  //If the confirm password is not equal to the password
        {
            _error = true
            return _errorCodes["CONFIRM_PASSWORD_NOT_EQUAL"]
        }
        return false
    }
}



























































































































/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
