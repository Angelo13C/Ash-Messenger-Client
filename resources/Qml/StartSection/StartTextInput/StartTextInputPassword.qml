import QtQuick 2.0
import QtQuick.Layouts 1.12

StartTextInput {            //Password text field
    id: _root
    property bool _confirmPassword              //Is it a confirm password or password textInput?

    _password: true
    _placeholder: _confirmPassword ? qsTr("Confirm password") : qsTr("Password")
    _imageType: "Password"
    _validator: RegExpValidator { regExp: /[A-Za-z0-9_@.]{6,50}/ }
    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
}
