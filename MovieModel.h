#ifndef MOVIEMODEL
#define MOVIEMODEL

#include "Movie.h"

#include <QAbstractListModel>
#include <QDebug>

class MovieModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum MovieRoles {
        TitleRole = Qt::UserRole + 1,
        DirectorRole,
        CastRole,
        PlotRole,
        PremiereRole,
        YearRole,
        CompleteRole,
        TorrentRole
    };

    MovieModel(QObject *parent = 0) : QAbstractListModel(parent)
    {
        qDebug() << this << "object created";
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const
    {
        //    qDebug() << this << "rowCount()";
        Q_UNUSED(parent);
        return _movies.count();
    }
    void add(const Movie &movie)
    {
        //    qDebug() << this << "add()";
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        _movies.append( movie );
        endInsertRows();
    }
    QVariant data(const QModelIndex &index, int role) const
    {
        //    qDebug() << this << "data()";
        if ( index.row() >= 0 || index.row() < _movies.count() ) {

            const Movie movie = _movies[index.row()];

            if ( role == TitleRole )
                return movie.title();
            else if ( role == DirectorRole )
                return movie.director();
            else if ( role == CastRole )
                return movie.cast();
            else if ( role == PlotRole )
                return movie.plot();
            else if ( role == PremiereRole )
                return movie.premiere().toString("dd/MM/yyyy");
            else if ( role == YearRole )
                return movie.year();
            else if ( role == CompleteRole )
                return movie.isComplete();
            else if ( role == TorrentRole )
                return movie.torrentInfo().isEmpty();
        }
        return QVariant();
    }

    void clear()
    {
        for( int i=_movies.count()-1; i>=0; --i ) {
            beginRemoveRows(QModelIndex(), rowCount(), rowCount());
            _movies.remove(i);
            endRemoveRows();
        }
    }
    Movie& movieByTitle(const QString &title)
    {
        //    qDebug() << this << "movieByTitle()" << title;
        for (int i=0; i<_movies.size(); ++i)
            if ( _movies.at(i).title() == title )
                return _movies[i];
    }
    int movieIndex(const QString &title) const
    {
        //    qDebug() << this << "movieIndex()" << title;
        int index = 0;
        for (int i=0; i<_movies.size(); ++i)
            if ( _movies.at(i).title() == title )
                index = i;
        return index;
    }

signals:
    void detailsDownloaded();

protected:
    QHash<int, QByteArray> roleNames() const
    {
        //    qDebug() << this << "roleNames()";
        QHash<int, QByteArray> roles;
        roles[TitleRole] = "title";
        roles[DirectorRole] = "director";
        roles[CastRole] = "cast";
        roles[PlotRole] = "plot";
        roles[PremiereRole] = "premiere";
        roles[YearRole] = "year";
        roles[CompleteRole] = "complete";
        roles[TorrentRole] = "torrentsEmpty";
        return roles;
    }

private:
    QVector<Movie> _movies;
};

#endif // MOVIEMODEL

