#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include <QQmlContext>

#include "MovieManager.h"
#include "MovieModel.h"
#include "ResourceImageProvider.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MovieModel movies;
    MovieModel wishlist;
    TorrentInfoModel torrents;
    MovieManager manager(movies, torrents);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("movies", &movies);
    engine.rootContext()->setContextProperty("wishlist", &wishlist);
    engine.rootContext()->setContextProperty("torrents", &torrents);
    engine.addImageProvider( QLatin1String("img"), new ResourceImageProvider(QQuickImageProvider::Pixmap, movies) );
    engine.addImageProvider( QLatin1String("wsl"), new ResourceImageProvider(QQuickImageProvider::Pixmap, movies) );
    engine.load( QUrl(QStringLiteral("qrc:/main.qml")) );

    if ( engine.rootObjects().size() > 0 ) {
        QObject *item = engine.rootObjects().at(0)->findChild<QQuickItem*>("loader");
        QObject::connect(item,  SIGNAL(searchMovie(QString)),       &manager,   SLOT(requestMovieList(QString)));
        QObject::connect(item,  SIGNAL(downloadDetails(QString)),   &manager,   SLOT(requestMovieDetails(QString)));
        QObject::connect(item,  SIGNAL(downloadTorrent(QString)),   &manager,   SLOT(downloadTorrent(QString)));
    }

    return app.exec();
}
