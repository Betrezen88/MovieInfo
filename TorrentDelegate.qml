import QtQuick 2.0

Item {
    id: main; height: 40; anchors { left: parent.left; right: parent.right; margins: 5; }

    signal downloadTorrent(string downloadLink);

    Rectangle {
        id: item; anchors.fill: parent; color: "#491bcd";
        Text {
            id: label; anchors { left: item.left; right: icon.left; top: item.top; bottom: item.bottom; }
            verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignHCenter;
            text: "Quality: "+model.quality+" | Size:"+model.size+"\nSeeds: "+model.seed+" | Peers: "+model.peer;
        }
        Image {
            id: icon; source: "icon/icons/download.png"; width: 32;
            anchors { top: item.top; bottom: item.bottom; right: item.right; margins: 5} verticalAlignment: Image.AlignVCenter
        }
    }
    MouseArea { anchors.fill: main; onClicked: main.downloadTorrent(model.downloadLink) }
}
