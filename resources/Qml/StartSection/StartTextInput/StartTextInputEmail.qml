import QtQuick 2.0
import QtQuick.Layouts 1.12

StartTextInput {            //Email text field
    id: _root
    _password: false
    _imageType: "User"
    _placeholder: qsTr("Email")
    _validator: RegExpValidator { regExp: /[A-Za-z0-9@_!#$%&'*+-/=?^_`{|}~]{3,50}/ }
    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
}
