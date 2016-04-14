import QtQuick 2.5

Item {
    id: main

    property string btnText
    property string placeholder
    property string provider
    property var model

    signal search(string title)
    signal changeView()
    signal downloadTorrent(string downloadLink)
    signal downloadDetails(string title)

    ListView {
        id: listView
        model: main.model
        anchors { top: searchPanel.bottom; bottom: main.bottom; left: main.left; right: main.right }
        delegate: MovieDelegate {
            provider: main.provider
            onDownloadTorrent: main.downloadTorrent(downloadLink);
            onDownloadDetails: main.downloadDetails(title);
        }
    }

    UpperPanel {
        id: searchPanel; placeholder: main.placeholder
        onMenuBtnClicked: menu.visible = true;
        onSearchBtnClicked: search(text);
    }

    MainMenu {
        id: menu; visible: false; anchors.fill: main; viewBtnText: main.btnText;
        onViewBtnClicked: main.changeView();
    }
}
