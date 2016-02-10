#ifndef TASKDETAILS_H
#define TASKDETAILS_H

#include "Task.h"
#include "TaskTorrentDetails.h"

class TaskDetails : public Task
{
    Q_OBJECT
public:
    TaskDetails(Movie &movie);
    ~TaskDetails();

public slots:
    void requestData();
    void reply(QNetworkReply *reply);
    void sendDetails();

private:
    void downloadTorrentInfo(Movie &movie);

private:
    Task *_task;
    Movie &_movie;
};

#endif // TASKDETAILS_H
