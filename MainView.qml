import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    id: main
    objectName: "main"
    anchors.fill: parent

    signal search(string title)
    signal getDetails(string title)
    signal downloadTorrent(string downloadLink)

    ListView {
        id: movieListView
        objectName: "lista"
        anchors { top: upperBar.bottom; bottom: main.bottom; left: main.left; right: main.right; }
        spacing: 2
        model: movies
        delegate: MovieDelegate {
            onDetails: getDetails(title)
            onDownloadTorrent: main.downloadTorrent(downloadLink);
        }
    }

    Item {
        id: upperBar; height: 50;
        anchors { top: main.top; left: main.left; right: main.right }
        Rectangle { color: "white"; anchors.fill: upperBar; }

        Button {
            id: menuBtn; width: 50; text: "M";
            anchors { top: upperBar.top; bottom: upperBar.bottom; left: upperBar.left }
            onClicked: {
                menu.visible = true;
//                var component = Qt.createComponent("Menu.qml");
//                if ( component.status === Component.Ready ) {
//                    console.log("Menu button")
//                    var object = component.createObject(menuBtn.parent.parent);
//                    object.z = 5;
//                    //object.downloadTorrent.connect(main.downloadTorrent);
//                }
//                else
//                    console.log("Error loading component:", component.errorString() );
            }
        }

        TextField {
            id: movieTitleInput; placeholderText: "Enter movie title";
            anchors { top: upperBar.top; bottom: upperBar.bottom; left: menuBtn.right; right: searchBtn.left; }
        }

        Button {
            id: searchBtn; width: 50; text: "S";
            anchors { top: upperBar.top; bottom: upperBar.bottom; right: upperBar.right }
            onClicked: (movieTitleInput.text !== "") ? search(movieTitleInput.text) : console.log("Movie title is empty");
        }

    }
    MainMenu { id: menu; anchors.fill: main; }



    Component.onCompleted: movieTitleInput.forceActiveFocus();
}
