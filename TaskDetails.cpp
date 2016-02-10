#include "TaskDetails.h"
#include "TaskTorrentDetails.h"
#include "Parser.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>

TaskDetails::TaskDetails(Movie &movie) : _movie(movie)
{
    qDebug() << this << "object created";
}

TaskDetails::~TaskDetails()
{
    qDebug() << this << "object destroyed";
    delete _networkManager;
    delete _task;
}

void TaskDetails::requestData()
{
    qDebug() << this << "requestData()";
    _networkManager = new QNetworkAccessManager;
    connect(_networkManager,    &QNetworkAccessManager::finished,   this,   &TaskDetails::reply);
    _networkManager->get( QNetworkRequest(_movie.detailLink()) );
}

void TaskDetails::reply(QNetworkReply *reply)
{
    qDebug() << this << "reply()";

    Parser parser;
    parser.parse( QString::fromLocal8Bit( reply->readAll() ).replace("&oacute;", QString::fromLocal8Bit("ó")).simplified() );

    Movie::Builder().fillDetails(_movie, parser.page());

    downloadTorrentInfo(_movie);
}

void TaskDetails::sendDetails()
{
    qDebug() << this << "sendDetails()" << _movie.title();
    emit sendMovieDetails(_movie);
    emit finished();
}

void TaskDetails::downloadTorrentInfo(Movie &movie)
{
    qDebug() << this << "donwloadTorrentInfo()";
    _task = new TaskTorrentDetails(movie);
    connect(_task,  &Task::finished,  this,   &TaskDetails::sendDetails);
    _task->requestData();
}
