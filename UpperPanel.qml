import QtQuick 2.0
import QtQuick.Controls 1.4

Rectangle {
    id: main
    height: 50
    color: "#fff"
    anchors { top: parent.top; left: parent.left; right: parent.right; }

    property string placeholder

    signal menuBtnClicked();
    signal searchBtnClicked(string text);

    Button {
        id: menuBtn; width: 50; text: "M"; anchors { top: main.top; bottom: main.bottom; left: main.left; }
        onClicked: main.menuBtnClicked();
    }

    TextField {
        id: searchFrase; placeholderText: main.placeholder;
        anchors { top: main.top; bottom: main.bottom; left: menuBtn.right; right: searchBtn.left; }
        onTextChanged: searchBtn.enabled = (searchFrase.text.length > 0 ? true : false)
    }

    Button {
        id: searchBtn; width: 50; text: "S"; anchors { top: main.top; bottom: main.bottom; right: main.right; }
        enabled: false; onClicked: main.searchBtnClicked(searchFrase.text);
    }

    Component.onCompleted: searchFrase.forceActiveFocus();
}
