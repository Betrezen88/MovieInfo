import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    id: main; visible: false;

    Rectangle {
        anchors.fill: main; color: "#000"; opacity: 0.7
        MouseArea { anchors.fill: parent; onClicked: main.visible = false; }
    }

    Column {
        id: buttons
        spacing: 5
        anchors.fill: main

        Button { id: quitBtn; height: 40; width: 90; text: "Quit"; anchors { bottom: buttons.bottom; right: buttons.right }  onClicked: Qt.quit() }
    }
}
