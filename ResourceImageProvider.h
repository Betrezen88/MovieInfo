#ifndef RESOURCEIMAGEPROVIDER
#define RESOURCEIMAGEPROVIDER

#include <QQuickImageProvider>
#include <QDebug>

#include "MovieModel.h"

class ResourceImageProvider : public QQuickImageProvider
{
public:
    ResourceImageProvider(QQuickImageProvider::ImageType type, MovieModel &model) : QQuickImageProvider(type), _model(model)
    {
        qDebug() << this << "object created";
    }

    ~ResourceImageProvider()
    {
        qDebug() << this << "object destroyed";
    }

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
    {
//        qDebug() << this << "requestPixmap()" << id;
        QPixmap image( _model.movieByTitle( id ).poster() );
        QPixmap result;

        if ( requestedSize.isValid() )
            result = image.scaled(requestedSize, Qt::KeepAspectRatio);
        else
            result = image;
        *size = result.size();
        return result;
    }

private:
    MovieModel &_model;
};

#endif // RESOURCEIMAGEPROVIDER

