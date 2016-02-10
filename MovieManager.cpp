#include "MovieManager.h"

#include <QDesktopServices>
#include <QDebug>

MovieManager::MovieManager(MovieModel &movies, TorrentInfoModel &torrents) : _movies(movies), _torrents(torrents)
{
    qDebug() << this << "MovieManager object created.";
}

MovieManager::~MovieManager()
{
    qDebug() << this << "MovieManager object destroyed.";
}

void MovieManager::requestMovieList(QString title)
{
//    qDebug() << this << "MovieManager object requestMovieList(" << title << ")";
    _movies.clear();
    _thread = new QThread;
    _task = new TaskList(title);
    _task->moveToThread(_thread);

    connect(_thread,    &QThread::started,      _task,      &Task::requestData);
    connect(_task,      &Task::finished,        _thread,    &QThread::quit);
    connect(_thread,    &QThread::finished,     _task,      &Task::deleteLater);
    connect(_thread,    &QThread::finished,     _thread,    &QThread::deleteLater);
    connect(_task,      &Task::sendMovieList,   this,       &MovieManager::updateMovieModel, Qt::QueuedConnection);

    _thread->start();
}

void MovieManager::requestMovieDetails(QString title)
{
    qDebug() << this << "requestMovieDetails()" << title;

    _thread = new QThread;
    _task = new TaskDetails( _movies.movieByTitle(title));
    _task->moveToThread(_thread);

    connect(_thread,    &QThread::started,      _task,      &Task::requestData);
    connect(_task,      &Task::finished,        _thread,    &QThread::quit);
    connect(_thread,    &QThread::finished,     _task,      &Task::deleteLater);
    connect(_thread,    &QThread::finished,     _thread,    &QThread::deleteLater);
    connect(_task,      &Task::sendMovieDetails,    this,   &MovieManager::updateMovieDetails);

    _thread->start();
}

void MovieManager::updateMovieModel(QVector<Movie> movies)
{
//    qDebug() << this << "updateMovieModel()";
    for (int i=0; i<movies.size(); ++i)
        _movies.add( movies.at(i) );
}

void MovieManager::updateMovieDetails(Movie movie)
{
    qDebug() << this << "updateMovieDetails()" << movie.title();
    updateTorrentList(movie.torrentInfo());
    emit _movies.detailsDownloaded();
}

void MovieManager::updateTorrentList(QVector<TorrentInfo> torrents)
{
    qDebug() << this << "updateTorrentList()";
    _torrents.clear();
    for ( int i=0; i<torrents.size(); ++i )
        _torrents.add( torrents.at(i) );
}

void MovieManager::downloadTorrent(QString link)
{
    qDebug() << this << "downloadTorrent()" << link;
    QDesktopServices::openUrl( QUrl(link) );
}

void MovieManager::addMovieToWishList(Movie movie)
{
    qDebug() << this << "addMovieToWishList()" << movie.title();
}

void MovieManager::removeMovieFromWishList(Movie movie)
{
    qDebug() << this << "removeMovieFromWishList()" << movie.title();
}
