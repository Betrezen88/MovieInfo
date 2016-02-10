#ifndef MOVIE_H
#define MOVIE_H

#include "TorrentInfo.h"
#include "TorrentInfoModel.h"

#include <QString>
#include <QVector>
#include <QDate>
#include <QDomNode>
#include <QUrl>
#include <QPixmap>
#include <QObject>

#include <QDebug>

class Movie
{
public:
    class Builder;

    Movie() { _complete = false; }
    ~Movie() {}

    inline void setTitle(const QString title) { _title = title; }
    inline void setDirector(const QVector<QString> director) { _director = director; }
    inline void addDirector(const QString director) { _director.append(director); }
    inline void addCast(const QString cast) { _cast.append(cast); }
    inline void setCast(const QVector<QString> cast) { _cast = cast; }
    inline void setPlot(const QString plot) { _plot = plot; }
    inline void setPremiere(const int day, const int month, const int year) { _premiere.setDate(year, month, day); }
    inline void setPremiere(const QDate premiere) { _premiere = premiere; }
    inline void setPosterLink(const QUrl posterLink) { _posterLink = QUrl(posterLink); }
    inline void setPoster(const QPixmap poster) { _poster = poster; }
    inline void setDetailLink(const QUrl detailLink) { _detailLink = detailLink; }
    inline void setComplete(const bool complete) { _complete = complete; }
    inline void addTorrentInfo(const TorrentInfo torrent) { _torrentInfo.append(torrent); }

    inline QString title() const { return _title; }
    inline QString plot() const { return _plot; }
    inline QDate premiere() const { return _premiere; }
    inline QUrl posterLink() const { return _posterLink; }
    inline QPixmap poster() const { return _poster; }
    inline QUrl detailLink() const { return _detailLink; }
    inline int year() const { return _premiere.year(); }
    inline bool isComplete() const { return _complete; }
    inline QVector<TorrentInfo> torrentInfo() const { return _torrentInfo; }

    QString director() const
    {
        QString tmpDirector = "";
        for (int i=0; i<_director.size(); ++i) {
            tmpDirector += _director[i];
            if ( i < _director.size()-1 )
                tmpDirector += ", ";
        }
        return tmpDirector;
    }
    QString cast() const
    {
        QString tmpCast = "";
        for (int i=0; i<_cast.size(); ++i) {
            tmpCast += _cast[i];
            if ( i < _cast.size()-1 )
                tmpCast += ", ";
        }
        return tmpCast;
    }

private:
    QString _title;
    QVector<QString> _director;
    QVector<QString> _cast;
    QString _plot;
    QDate _premiere;
    QUrl _posterLink;
    QPixmap _poster;
    QUrl _detailLink;
    bool _complete;
    QVector<TorrentInfo> _torrentInfo;
};

class Movie::Builder
{
public:
    Builder() {}

    Movie build(const QDomNode &node)
    {
        Movie movie;
        movie.setTitle( getTitle( node ) );
        movie.setDirector( getDirector( node ) );
        movie.setCast( getCast( node ) );
        movie.setDetailLink( getDetailsLink( node ) );
        movie.setPosterLink( getPosterLink( node ) );
        movie.setPremiere( getYear(node) );
        return movie;
    }

    Movie buildDetails(const QDomDocument &node)
    {
        Movie movie;
        movie.setPlot( getPlot(node) );
        movie.setPremiere( getPremiere(node) );
        return movie;
    }

    void fillDetails(Movie &movie, const QDomDocument &node)
    {
        movie.setPlot( getPlot(node) );
        movie.setPremiere( getPremiere(node) );
        movie.setComplete(true);
    }

private:
    const QString getTitle(const QDomNode &node)
    {
        QString tmpTitle = "";
        QDomNodeList div = node.toElement().elementsByTagName("div");
        for ( int i=0; i<div.size(); ++i )
            if ( div.at(i).hasAttributes() && div.at(i).attributes().contains("class") && div.at(i).attributes().namedItem("class").nodeValue().contains("hitImage") ) {
                tmpTitle = div.at(i).namedItem("a").attributes().namedItem("title").nodeValue();
                break;
            }
        return tmpTitle;
    }

    const QVector<QString> getDirector(const QDomNode &node)
    {
        QVector<QString> tmpDirector;
        QDomNodeList a = node.toElement().elementsByTagName("dl").at(0).toElement().elementsByTagName("dd").at(0).toElement().elementsByTagName("a");
        for ( int i=0; i<a.size(); ++i )
            tmpDirector.append( a.at(i).firstChild().nodeValue() );
        return tmpDirector;
    }

    const QVector<QString> getCast(const QDomNode &node)
    {
        QVector<QString> tmpCast;
        QDomNodeList a = node.toElement().elementsByTagName("dl").at(0).toElement().elementsByTagName("dd").at(1).toElement().elementsByTagName("a");
        for ( int i=0; i<a.size(); ++i )
            tmpCast.append( a.at(i).firstChild().nodeValue() );
        return tmpCast;
    }

    QDate getYear(const QDomNode &node)
    {
        QDate year(1000, 1, 1);
        QDomNodeList span = node.toElement().elementsByTagName("span");
        if ( span.at(0).hasAttributes() && span.at(0).attributes().namedItem("class").nodeValue().contains("hdr hdr-medium hitTitle") )
            year.setDate(span.at(0).firstChild().nodeValue().remove(5, 1).remove(0, 1).toInt(), 1, 1);
        return year;
    }

    const QUrl getPosterLink(const QDomNode &node)
    {
        QUrl tmpPosterLink;
        QDomNodeList div = node.toElement().elementsByTagName("div");
        for ( int i=0; i<div.size(); ++i )
            if ( div.at(i).hasAttributes() && div.at(i).attributes().contains("class") && div.at(i).attributes().namedItem("class").nodeValue().contains("hitImage") ) {
                tmpPosterLink = QUrl( div.at(i).toElement().elementsByTagName("img").at(0).attributes().namedItem("src").nodeValue() );
                break;
            }
        return tmpPosterLink;
    }

    const QUrl getDetailsLink(const QDomNode &node)
    {
        QUrl tmpDetailLink;
        QDomNodeList a = node.toElement().elementsByTagName("a");
        for ( int i=0; i<a.size(); ++i )
            if (a.at(i).hasAttributes() && a.at(i).attributes().contains("class") && a.at(i).attributes().namedItem("class").nodeValue().contains("hdr hdr-medium hitTitle") ) {
                tmpDetailLink = QUrl( "http://www.filmweb.pl"+a.at(i).attributes().namedItem("href").nodeValue() );
                break;
            }
        return tmpDetailLink;
    }

    const QString getPlot(const QDomDocument &document)
    {
        QString tmpPlot = "";
        QDomNodeList div = document.elementsByTagName("div");
        for ( int i=0; i<div.size(); ++i )
            if ( div.at(i).hasAttributes() && div.at(i).attributes().contains("class") && div.at(i).attributes().namedItem("class").nodeValue().contains("filmPlot") )
                tmpPlot = div.at(i).firstChild().firstChild().nodeValue();
        return tmpPlot;
    }

    const QDate getPremiere(const QDomDocument &document)
    {
//        qDebug() << this << "getPremiere()";
        QDate tmpPremiere = QDate(1000, 1, 1);
        QDomNodeList span = document.elementsByTagName("span");
        for (int i=0; i<span.size(); ++i)
            if ( span.at(i).hasChildNodes() && span.at(i).attributes().contains("id") && span.at(i).attributes().namedItem("id").nodeValue().contains("filmPremiereWorld") ) {
                tmpPremiere = QDate::fromString(span.at(i).firstChild().nodeValue(), "yyyy-MM-dd");
                break;
            }
        return tmpPremiere;
    }
};

Q_DECLARE_METATYPE(Movie)

#endif // MOVIE_H
