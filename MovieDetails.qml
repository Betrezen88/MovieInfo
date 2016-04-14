import QtQuick 2.0
import QtQuick.Controls 1.4

Rectangle {
    id: main
    anchors.fill: parent
    color: "white";
    z: 1

    property string provider

    signal downloadTorrent(string downloadLink)

    MouseArea { anchors.fill: parent }

    Item {
        id: upperBar; height: 50; anchors { top: main.top; left: main.left; right: main.right; }

        Button { id: menuBtn; width: 50; text: "M"; anchors { top: upperBar.top; bottom: upperBar.bottom; left: upperBar.left; } }
        Label {
            id: title; text: model.title; anchors { left: menuBtn.right; right: closeBtn.left; top: upperBar.top; bottom: upperBar.bottom }
            verticalAlignment: Text.AlignVCenter; horizontalAlignment: Text.AlignHCenter;
        }
        Button {
            id: closeBtn; width: 50; text: "C"; anchors { top: upperBar.top; bottom: upperBar.bottom; right: upperBar.right }
            onClicked: main.destroy();
        }
    }
    Item {
        id: infoBox; height: 200; anchors { top: upperBar.bottom; left: main.left; right: main.right }

        Image { id: poster; source: "image://"+main.provider+"/"+model.title; height: 200; width: 140; anchors.left: infoBox.left }
        Column {
            id: infoColumn; anchors { top: infoBox.top; bottom: infoBox.bottom; left: poster.right; right: infoBox.right } spacing: 5;
            Label {
                id: director; text: "Director: "+model.director; wrapMode: Text.WordWrap;
                anchors { left: infoColumn.left; right: infoColumn.right; leftMargin: 5; rightMargin: 5 }
            }
            Label {
                id: cast; text: "Cast: "+model.cast; wrapMode: Text.WordWrap;
                anchors { left: infoColumn.left; right: infoColumn.right; leftMargin: 5; rightMargin: 5 }
            }
            Label {
                id: premiere; text: "Premiere: "+model.premiere; wrapMode: Text.WordWrap;
                anchors { left: infoColumn.left; right: infoColumn.right; leftMargin: 5; rightMargin: 5 }
            }
        }
    }
    Item {
        id: plotBox; height: 100; anchors { top: infoBox.bottom; left: main.left; right: main.right; margins: 5; }
        Text { id: plot; text: "Plot: "+model.plot; anchors.fill: plotBox; wrapMode: Text.WordWrap; }
    }
    Item {
        id: torrentBox; anchors { top: plotBox.bottom; left: main.left; right: main.right; bottom: main.bottom }
        ListView {
            id: torrentList
            anchors { top: label.bottom; bottom: torrentBox.bottom; left: torrentBox.left; right: torrentBox.right; }
            model: torrents
            delegate: TorrentDelegate { onDownloadTorrent: main.downloadTorrent(downloadLink) }
            spacing: 5
        }
        Rectangle {
            id: label; height: 15; anchors { left: torrentBox.left; right: torrentBox.right; top: torrentBox.top; }
            Text { text: "Availeble Torrents"; anchors.centerIn: parent; }
        }
    }

    Connections {
        target: movies
        onDetailsDownloaded: refresh()
    }

    Connections {
        target: wishlist
        onDetailsDownloaded: refresh()
    }

    function refresh() {
        console.log( "refresh()" );
        premiere.text = "Premiere: "+model.premiere;
        plot.text = "Plot: "+model.plot;
    }
}
