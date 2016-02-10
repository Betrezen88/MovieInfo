#include "TaskList.h"
#include "Parser.h"

#include <QDomDocument>

TaskList::TaskList(QString &title) : _title(title)
{
    qDebug() << this << "object created. Movie title: \"" << _title << "\"";
    _imageTaskCounter = 0;
}

TaskList::~TaskList()
{
    qDebug() << this << "object destroyed.";
    delete _networkManager;
}

void TaskList::requestData()
{
//    qDebug() << this << " requestData()";
    _networkManager = new QNetworkAccessManager(this);
    connect(_networkManager,   &QNetworkAccessManager::finished,   this,  &TaskList::reply);
    _networkManager->get(QNetworkRequest(QUrl("http://www.filmweb.pl/search/film?q="+_title+"&startYear=&endYear=&startRate=&endRate=&startCount=&endCount=&sort=TEXT_SCORE&sortAscending=false")));
}

void TaskList::reply(QNetworkReply *reply)
{
//    qDebug() << this << "reply()";

    Parser parser;
    parser.parse( QString::fromLocal8Bit( reply->readAll() ).replace("&oacute;", QString::fromLocal8Bit("ó")).simplified() );

    createMovieList(parser.page());

    reply->deleteLater();
    reply = 0;
}

void TaskList::imagesDownloaded()
{
//    qDebug() << this << "imagesDownloaded()" << _imageTaskCounter;
    --_imageTaskCounter;
    if ( _imageTaskCounter == 0 ) {
        emit sendMovieList(_movies);
        emit finished();
    }
}

void TaskList::createMovieList(const QDomDocument &page)
{
//    qDebug() << this << "createMovieList()";
    QDomNodeList li = page.elementsByTagName("li");

    for (int i=0; i<li.size(); ++i)
        if ( li.at(i).hasAttributes() && li.at(i).attributes().namedItem("id").nodeValue().contains("film_") )
            _movies.append( Movie::Builder().build( li.at(i) ) );
    startPosterDownload();
}

void TaskList::startPosterDownload()
{
//    qDebug() << this << "preparePosterDownload()";
    for ( int i=0; i<_movies.size(); ++i) {
        TaskImageDownloader *task = new TaskImageDownloader(_movies[i]);
        connect(task,   &Task::destroyed,    this,   &TaskList::imagesDownloaded);
        connect(task,   &Task::finished,    task,   &Task::deleteLater);
        task->requestData();
        ++_imageTaskCounter;
    }
}

void TaskList::displayMoviesInfo()
{
    for ( int i=0; i<_movies.size(); ++i) {
        qDebug() << "Title:" << _movies.at(i).title() << QString::number(_movies.at(i).premiere().year());
        qDebug() << "Director:" <<_movies.at(i).director();
        qDebug() << "Cast:" <<_movies.at(i).cast();
        qDebug() << "Details:" <<_movies.at(i).detailLink();
        qDebug() << "Poster:" <<_movies.at(i).poster().size();
    }
}
