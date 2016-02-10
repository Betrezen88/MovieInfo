#ifndef MOVIEMANAGER_H
#define MOVIEMANAGER_H

#include "Database.h"
#include "Movie.h"
#include "MovieModel.h"
#include "Task.h"
#include "TaskList.h"
#include "TaskDetails.h"
#include "TorrentInfoModel.h"

#include <QObject>
#include <QThread>
#include <QVector>

class MovieManager : public QObject
{
    Q_OBJECT
public:
    MovieManager(MovieModel &movies, TorrentInfoModel &torrents);
    ~MovieManager();

signals:
    void detailsDownloaded();

public slots:
    void requestMovieList(QString title);
    void requestMovieDetails(QString title);
    void updateMovieModel(QVector<Movie> movies);
    void updateMovieDetails(Movie movie);
    void updateTorrentList(QVector<TorrentInfo> torrents);
    void downloadTorrent(QString link);
    void addMovieToWishList(Movie movie);
    void removeMovieFromWishList(Movie movie);

private:
    QThread *_thread;
    Task *_task;
    MovieModel &_movies;
    TorrentInfoModel &_torrents;
    Database db;
};

#endif // MOVIEMANAGER_H
