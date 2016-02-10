#ifndef TASKLIST_H
#define TASKLIST_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDomDocument>

#include "Task.h"
#include "TaskImageDownloader.h"
#include "Movie.h"

#include <QDebug>

class TaskList : public Task
{
    Q_OBJECT
public:
    TaskList(QString &title);
    ~TaskList();

public slots:
    void requestData();
    void reply(QNetworkReply *reply);
    void imagesDownloaded();

private:
    void createMovieList(const QDomDocument &page);
    void startPosterDownload();

    void displayMoviesInfo();

    QString _title;
    QVector<Movie> _movies;
    int _imageTaskCounter;
};

#endif // TASKLIST_H
