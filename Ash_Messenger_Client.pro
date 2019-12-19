QT += quick
QT += svg
QT += sql
QT += network
QT += quickcontrols2
CONFIG += c++11
CONFIG += precompile_header

# Use Precompiled headers (PCH)
PRECOMPILED_HEADER = src/pch.h

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

release: DESTDIR = build/release
debug:   DESTDIR = build/debug
profile:   DESTDIR = build/profile

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/Database/database.cpp \
        src/Messaging/StartSection/advertisepanel.cpp \
        src/Messaging/authenticationsystem.cpp \
        src/Messaging/chatsystem.cpp \
        src/Messaging/messagesystem.cpp \
        src/Messaging/searchchatuser.cpp \
        src/Messaging/userinfo.cpp \
        src/Network/DataTransferProtocolAsh/dtpa.cpp \
        src/Network/DataTransferProtocolAsh/dtpaform.cpp \
        src/Network/DataTransferProtocolAsh/dtpareceiver.cpp \
        src/Network/DataTransferProtocolAsh/dtpareceivermanager.cpp \
        src/Network/DataTransferProtocolAsh/dtparequest.cpp \
        src/Network/DataTransferProtocolAsh/dtpasender.cpp \
        src/Network/sslconnection.cpp \
        src/Other/config.cpp \
        src/Other/singleappinstance.cpp \
        src/Other/translatormanager.cpp \
        src/Other/usersettings.cpp \
        src/main.cpp \
        src/performancebenchmark.cpp

RESOURCES = resources/qml.qrc

TRANSLATIONS = Resources/Languages/lang_it.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    resources/Assets/Images/Chat/Attachments.svg \
    resources/Assets/Images/Chat/Menu Dots.svg \
    resources/Assets/Images/Chat/Menu.svg \
    resources/Assets/Images/Chat/Search.svg \
    resources/Assets/Images/Chat/Send Message.svg \
    resources/Assets/Images/Chat/Unselect_Chat.svg \
    resources/Assets/Images/Eye_ShowPassword.svg \
    resources/Assets/Images/Flags/Flag_it.svg \
    resources/Assets/Images/Flags/Flag_uk.svg \
    resources/Assets/Images/Padlock.svg \
    resources/Assets/Images/StartSection/GitHub.png \
    resources/Assets/Images/StartSection/Reddit.png \
    resources/Assets/Images/StartSection/Right Image Advertise Panel.svg \
    resources/Assets/Images/StartSection/Twitter.png \
    resources/Assets/Images/User.svg \
    resources/Assets/Images/test.jpg \
    resources/Config/config.json \
    resources/Database/defaultTables.txt \
    resources/Languages/lang_it.qm \
    resources/Languages/lang_it.ts \
    resources/Qml/IconButton.qml \
    resources/Qml/MessageSection/AreaChat/AreaChat.qml \
    resources/Qml/MessageSection/AreaChat/ChatInfoBar.qml \
    resources/Qml/MessageSection/AreaChat/MessageBar.qml \
    resources/Qml/MessageSection/ChatImage.qml \
    resources/Qml/MessageSection/ChatListSection/AreaChatList/AreaChatList.qml \
    resources/Qml/MessageSection/ChatListSection/AreaChatList/ChatButton.qml \
    resources/Qml/MessageSection/ChatListSection/AreaSearch/AreaSearch.qml \
    resources/Qml/MessageSection/ChatListSection/ChatListSection.qml \
    resources/Qml/MessageSection/ChatListSection/ListElements.qml \
    resources/Qml/MessageSection/ChatListSection/SearchBar.qml \
    resources/Qml/MessageSection/MessageSection.qml \
    resources/Qml/StartSection/AdvertisePanel/AdvertisePanel.qml \
    resources/Qml/StartSection/AreaLogin/AreaLogin.qml \
    resources/Qml/StartSection/AreaRegister/AreaRegister.qml \
    resources/Qml/StartSection/ErrorHandler.qml \
    resources/Qml/StartSection/StartButtonLoginRegister.qml \
    resources/Qml/StartSection/StartButtonNoBackground.qml \
    resources/Qml/StartSection/StartSection.qml \
    resources/Qml/StartSection/StartTextInput/StartTextInput.qml \
    resources/Qml/StartSection/StartTextInput/StartTextInputEmail.qml \
    resources/Qml/StartSection/StartTextInput/StartTextInputPassword.qml \
    resources/Qml/main.qml

HEADERS += \
    src/pch.h \
    src/Database/database.h \
    src/Messaging/StartSection/advertisepanel.h \
    src/Messaging/authenticationsystem.h \
    src/Messaging/chatsystem.h \
    src/Messaging/messagesystem.h \
    src/Messaging/searchchatuser.h \
    src/Messaging/userinfo.h \
    src/Network/DataTransferProtocolAsh/dtpa.h \
    src/Network/DataTransferProtocolAsh/dtpaform.h \
    src/Network/DataTransferProtocolAsh/dtpareceiver.h \
    src/Network/DataTransferProtocolAsh/dtpareceivermanager.h \
    src/Network/DataTransferProtocolAsh/dtparequest.h \
    src/Network/DataTransferProtocolAsh/dtpasender.h \
    src/Network/sslconnection.h \
    src/Other/config.h \
    src/Other/singleappinstance.h \
    src/Other/translatormanager.h \
    src/Other/usersettings.h \
    src/performancebenchmark.h
