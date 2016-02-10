#ifndef TASK
#define TASK

#include <QObject>
#include <QVector>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "Movie.h"

class Task : public QObject
{
    Q_OBJECT

signals:
    void finished();
    void sendMovieList(QVector<Movie> movies);
    void sendMovieDetails(Movie movie);

public slots:
    virtual void requestData() {}
    virtual void reply(QNetworkReply *reply) { Q_UNUSED(reply) }

protected:
    QNetworkAccessManager *_networkManager;

};

#endif // TASK
