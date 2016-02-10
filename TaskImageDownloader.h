#ifndef TASKIMAGEDOWNLOADER_H
#define TASKIMAGEDOWNLOADER_H

#include "Task.h"
#include "Movie.h"

class TaskImageDownloader : public Task
{
    Q_OBJECT
public:
    TaskImageDownloader(Movie &movie);
    ~TaskImageDownloader();

public slots:
    void requestData();
    void reply(QNetworkReply *reply);

private:
    Movie &_movie;
};

#endif // TASKIMAGEDOWNLOADER_H
