#ifndef TORRENTINFO
#define TORRENTINFO

#include <QString>
#include <QUrl>
#include <QDomNode>

#include <QDebug>

class TorrentInfo
{
public:
    class Builder;
    TorrentInfo() {}
    ~TorrentInfo() {}

    inline void setQuality(const QString quality) { _quality = quality; }
    inline void setSize(const QString size) { _size = size; }
    inline void setPeer(const int peer) { _peer = peer; }
    inline void setSeed(const int seed) { _seed = seed; }
    inline void setDownloadLink(const QString downloadLink) { _downloadLink = QUrl("https://www.yify-torrent.org"+downloadLink); }

    inline QString quality() const { return _quality; }
    inline QString size() const { return _size; }
    inline QUrl downloadLink() const { return _downloadLink; }
    inline int peer() const { return _peer; }
    inline int seed() const { return _seed; }

private:
    QString _quality;
    QString _size;
    QUrl _downloadLink;
    int _peer;
    int _seed;
};

class TorrentInfo::Builder
{
public:
    Builder() {}

    TorrentInfo build(const QDomNode &node)
    {
        TorrentInfo torrent;
        torrent.setQuality( getQuality(node) );
        torrent.setSize( getSize(node) );
        torrent.setPeer( getPeers(node) );
        torrent.setSeed( getSeeds(node) );
        torrent.setDownloadLink( getDownloadLink(node) );
        return torrent;
    }

private:
    QString getQuality(const QDomNode &node)
    {
//        qDebug() << this << "getQuality()";
        QString tmpQuality = "";
        QDomNodeList div = node.toElement().elementsByTagName("div");
        for ( int i=0; i<div.size(); ++i )
            if ( div.at(i).hasAttributes() && div.at(i).attributes().contains("class") && div.at(i).attributes().namedItem("class").nodeValue() == "mdif" )
                tmpQuality = div.at(i).toElement().elementsByTagName("li").at(1).childNodes().at(1).nodeValue();
        return tmpQuality;
    }

    QString getSize(const QDomNode &node)
    {
//        qDebug() << this << "getSize()";
        QString tmpSize = "";
        QDomNodeList div = node.toElement().elementsByTagName("div");
        for ( int i=0; i<div.size(); ++i )
            if ( div.at(i).hasAttributes() && div.at(i).attributes().contains("class") && div.at(i).attributes().namedItem("class").nodeValue() == "mdif" )
                tmpSize = div.at(i).toElement().elementsByTagName("li").at(3).childNodes().at(1).nodeValue();
        return tmpSize;
    }

    int getPeers(const QDomNode &node)
    {
//        qDebug() << this << "getPeers()";
        int tmpPeer = 0;
        QDomNodeList div = node.toElement().elementsByTagName("div");
        for ( int i=0; i<div.size(); ++i )
            if ( div.at(i).hasAttributes() && div.at(i).attributes().contains("class") && div.at(i).attributes().namedItem("class").nodeValue() == "mdif" )
                tmpPeer = div.at(i).toElement().elementsByTagName("li").at(5).childNodes().at(1).nodeValue().toInt();
        return tmpPeer;
    }

    int getSeeds(const QDomNode &node)
    {
//        qDebug() << this << "getSeeds()";
        int tmpSeed = 0;
        QDomNodeList div = node.toElement().elementsByTagName("div");
        for ( int i=0; i<div.size(); ++i )
            if ( div.at(i).hasAttributes() && div.at(i).attributes().contains("class") && div.at(i).attributes().namedItem("class").nodeValue() == "mdif" )
                tmpSeed = div.at(i).toElement().elementsByTagName("li").at(6).childNodes().at(1).nodeValue().toInt();
        return tmpSeed;
    }

    QString getDownloadLink(const QDomNode &node)
    {
        QString tmpDownloadLink;
        QDomNodeList a = node.toElement().elementsByTagName("a");
        for ( int i=0; i<a.size(); ++i )
            if ( a.at(i).hasAttributes() && a.at(i).attributes().contains("class") && a.at(i).attributes().namedItem("class").nodeValue().contains("small button orange") )
                tmpDownloadLink = a.at(i).attributes().namedItem("href").nodeValue();
        return tmpDownloadLink;
    }
};

Q_DECLARE_METATYPE(TorrentInfo)

#endif // TORRENTINFO
