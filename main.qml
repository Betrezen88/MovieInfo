import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.0

Window {
    visible: true
    width: 300
    height: 500

    Loader {
        id: viewLoader
        objectName: "loader"

        signal searchMovie(string title);
        signal searchDetails(string title);
        signal downloadTorrent(string link);

        anchors.fill: parent
        source: "MainView.qml"
    }

    Connections {
        target: viewLoader.item
        onSearch: viewLoader.searchMovie(title);
        onGetDetails: viewLoader.searchDetails(title);
        onDownloadTorrent: viewLoader.downloadTorrent(downloadLink);
    }
}
