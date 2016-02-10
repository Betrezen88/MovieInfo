#include "TaskImageDownloader.h"

#include <QNetworkRequest>
#include <QPixmap>
#include <QDebug>

TaskImageDownloader::TaskImageDownloader(Movie &movie) : _movie(movie)
{
    qDebug() << this << "object created";
}

TaskImageDownloader::~TaskImageDownloader()
{
    qDebug() << this << "object destroyed";
    delete _networkManager;
}

void TaskImageDownloader::requestData()
{
//    qDebug() << this << "requestData()";
    _networkManager = new QNetworkAccessManager;
    connect(_networkManager,    &QNetworkAccessManager::finished,   this,   &TaskImageDownloader::reply);
    _networkManager->get( QNetworkRequest(_movie.posterLink()) );
}

void TaskImageDownloader::reply(QNetworkReply *reply)
{
//    qDebug() << this << "reply()";
    QPixmap image;
    image.loadFromData( reply->readAll() );
    _movie.setPoster( image );
    reply->deleteLater();
    emit finished();
}
