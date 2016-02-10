#ifndef TASKTORRENTDETAILS_H
#define TASKTORRENTDETAILS_H

#include "Task.h"

class TaskTorrentDetails : public Task
{
    Q_OBJECT
public:
    TaskTorrentDetails(Movie &movie);
    ~TaskTorrentDetails();

public slots:
    void requestData();
    void reply(QNetworkReply *reply);

private:
    void prepareTorrentInfo(QDomDocument page);

private:
    Movie &_movie;
};

#endif // TASKTORRENTDETAILS_H
