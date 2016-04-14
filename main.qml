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
        signal downloadDetails(string title);
        signal downloadTorrent(string link);

        anchors.fill: parent
        sourceComponent: movieView
    }

    Component {
        id: movieView
        View {
            placeholder: "Enter movie title"
            provider: "img"
            model: movies
            btnText: "Wishlist"
        }
    }

    Component {
        id: wishlistView
        View {
            placeholder: "Search movie in wishlist"
            provider: "wsl"
            model: wishlist
            btnText: "Main View"
        }
    }

    Connections {
        target: viewLoader.item
        onSearch: viewLoader.searchMovie(title);
        onChangeView: viewLoader.sourceComponent = (viewLoader.sourceComponent === movieView ? wishlistView : movieView)
        onDownloadDetails: viewLoader.downloadDetails(title);
        onDownloadTorrent: viewLoader.downloadTorrent(downloadLink);
    }
}
