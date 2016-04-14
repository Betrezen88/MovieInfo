import QtQuick 2.5
import QtQuick.Controls 1.4

Rectangle {
    id: main; visible: false;
    color: "#000"; opacity: 0.7

    property string viewBtnText

    signal viewBtnClicked()

    MouseArea { anchors.fill: parent; onClicked: main.visible = false; }

    Column {
        spacing: 5
        width: 120; anchors { right: main.right; bottom: main.bottom; rightMargin: 10; bottomMargin: 10; }
        Button { id: viewBtn; height: 50; width: 120; text: main.viewBtnText; onClicked: main.viewBtnClicked(); }
        Button { id: quitBtn; height: 50; width: 120; text: "Quit"; onClicked: Qt.quit() }
    }
}
