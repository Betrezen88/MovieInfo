import QtQuick 2.5
import QtQuick.Controls 1.4

Item {
    id: main
    height: 100
    anchors { left: parent.left; right: parent.right; }

    property string provider

    signal downloadDetails(string title)
    signal downloadTorrent(string downloadLink)

    Image {
        id: poster; source: "image://"+provider+"/"+model.title;
        width: 80; height: 100; anchors { left: main.left }
    }

    Column {
        id: infoColumn
        spacing: 5
        anchors { left: poster.right; right: main.right; leftMargin: 5 }

        Label {
            id: title; text: "Title: "+model.title+" ("+model.year+")"; wrapMode: Text.WordWrap
            anchors { left: infoColumn.left; right: infoColumn.right }
        }
        Label {
            id: director; text: "Director: "+model.director;  wrapMode: Text.WordWrap
            anchors { left: infoColumn.left; right: infoColumn.right }
        }
        Label {
            id: cast; text: "Cast: "+model.cast; wrapMode: Text.WordWrap
            anchors { left: infoColumn.left; right: infoColumn.right }
        }
    }

    MouseArea {
        anchors.fill: main
        onClicked: {
            if ( !model.complete )
                downloadDetails(model.title);
            createDetailsComponent();
        }
        onPressAndHold: delegateMenu.popup();
    }

    Menu {
        id: delegateMenu

        MenuItem {
            text: "Add to wish list"
            onTriggered: console.log( "Adding "+model.title+" to wish list." )
        }

        MenuItem {
            text: "Remove from wish list"
            enabled: false
            onTriggered: console.log( "Remove "+model.title+" from wish list." )
        }
    }

    function createDetailsComponent() {
        var component = Qt.createComponent("MovieDetails.qml");
        if ( component.status === Component.Ready ) {
            var object = component.createObject(main.parent.parent.parent, { "provider": main.provider });
            object.downloadTorrent.connect(main.downloadTorrent);
        }
        else
            console.log("Error loading component:", component.errorString() );
    }
}
