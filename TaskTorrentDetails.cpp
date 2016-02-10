#include "TaskTorrentDetails.h"
#include "Parser.h"
#include "TorrentInfo.h"

#include <QDebug>

TaskTorrentDetails::TaskTorrentDetails(Movie &movie) : _movie(movie)
{
    qDebug() << this << "object created" << _movie.title();
}

TaskTorrentDetails::~TaskTorrentDetails()
{
    qDebug() << this << "object destroyed";
    delete _networkManager;
}

void TaskTorrentDetails::requestData()
{
    qDebug() << this << "requestData()";
    _networkManager = new QNetworkAccessManager;
    connect(_networkManager,    &QNetworkAccessManager::finished,   this,   &TaskTorrentDetails::reply);
    _networkManager->get( QNetworkRequest( QUrl("https://www.yify-torrent.org/search/"+_movie.title()+"/") ) );
}

void TaskTorrentDetails::reply(QNetworkReply *reply)
{
    qDebug() << this << "reply()";

    Parser parser;
    parser.parse( QString::fromLocal8Bit( reply->readAll() ).simplified() );

    prepareTorrentInfo( parser.page() );
}

void TaskTorrentDetails::prepareTorrentInfo( QDomDocument page )
{
    qDebug() << this << "prepareTorrentInfo()" << _movie.year();
    QDomNodeList div = page.elementsByTagName("div");
    for ( int i=0; i<div.size(); ++i )
        if ( div.at(i).hasAttributes() && div.at(i).attributes().contains("class") && div.at(i).attributes().namedItem("class").nodeValue() == "mv" )
            if ( div.at(i).toElement().elementsByTagName("a").at(0).firstChild().nodeValue().contains(_movie.title()+" (") )
                _movie.addTorrentInfo( TorrentInfo::Builder().build( div.at(i) ) );
    emit finished();
}
