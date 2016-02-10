#ifndef DATABASE
#define DATABASE

#include <QSqlDatabase>
#include <QSqlQuery>

#include "Movie.h"

class Database
{
public:
    Database()
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("movies");
        if ( db.open() )
            createTables();
    }
    ~Database() {}

    bool addMovie(Movie movie)
    {
        //TO DO dodawanie filmu do bazy
        bool result = false;
        if ( db.isOpen() ) {
            QSqlQuery query;
            query.prepare("INSERT INTO movie (title, director, cast, plot, premiere, posterLink, detailLink, complete)"
                          "VALUES (:title, :director, :cast, :plot, :premiere, :posterLink, :detailLink, :complete)");
            query.bindValue(":title",       movie.title());
            query.bindValue(":director",    movie.director());
            query.bindValue(":cast",        movie.cast());
            query.bindValue(":plot",        movie.plot());
            query.bindValue(":premiere",    movie.premiere());
            query.bindValue(":posterLink",  movie.posterLink());
            query.bindValue(":detailLink", movie.detailLink());
            query.bindValue(":complete",    movie.isComplete());
            result = query.exec();
        }
        return result;
    }

    bool removeMovie(QString title)
    {
        //TO DO usuwanie filmu z bazy
        bool result = false;
        if ( db.isOpen() ) {
            QSqlQuery query;
            query.exec( QString("SELECT id FROM movie WHERE title = %1").arg(title) );
            if ( query.next() ) {
                QSqlQuery remove(QString("DELETE FROM movie WHERE id = %1").arg( query.value(0).toString() ));
                result = remove.exec();
            }
        }
        return result;
    }

    QVector<Movie> movies()
    {
        //TO DO zwrócenie listy filmów
        QVector<Movie> movies;
        if ( db.isOpen() ) {
            QSqlQuery query;
            query.exec("SELECT title, director, cast, plot, premiere, posterLink, detailLink, complete FROM movie");
            while ( query.next() ) {
                Movie movie;
                movie.setTitle( query.value(0).toString() );
                movie.setDirector( query.value(1).toStringList().toVector() );
                movie.setCast( query.value(2).toStringList().toVector() );
                movie.setPlot( query.value(3).toString() );
                movie.setPremiere( query.value(4).toDate() );
                movie.setPosterLink( query.value(5).toUrl() );
                movie.setDetailLink( query.value(6).toUrl() );
                movie.setComplete( query.value(7).toBool() );
                movies.append( movie );
            }
        }
        return movies;
    }

private:
    void createTables()
    {
        //TO DO tworzenie struktury bazy danych
        if ( db.isOpen() ) {
            QSqlQuery query;
            query.exec("CREATE TABLE movie "
                       "(id INTERER PRIMARY KEY,"
                       "title VARCHAR(30),"
                       "director VARCHAR(50),"
                       "cast VARCHAR(100),"
                       "plot VARCHAR(500),"
                       "premiere DATE,"
                       "posterLink VARCHAR(100),"
                       "detailLink VARCHAR(100)"
                       "complete BOOLEAN)");
        }
    }

    QSqlDatabase db;
};

#endif // DATABASE

