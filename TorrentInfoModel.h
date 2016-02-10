#ifndef TORRENTINFOMODEL
#define TORRENTINFOMODEL

#include "TorrentInfo.h"

#include <QAbstractListModel>

class TorrentInfoModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum TorrentInfoRoles {
        QualityRole = Qt::UserRole + 1,
        SizeRole,
        PeerRole,
        SeedRole,
        DownloadLinkRole
    };

    TorrentInfoModel(QObject *parent = 0) : QAbstractListModel(parent)
    {

    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const
    {
        Q_UNUSED(parent);
        return _torrentInfo.count();
    }

    void add(const TorrentInfo &torrentInfo)
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        _torrentInfo.append( torrentInfo );
        endInsertRows();
    }

    QVariant data(const QModelIndex &index, int role) const
    {
        if ( index.row() >= 0 || index.row() < _torrentInfo.count() ) {
            const TorrentInfo torrentInfo = _torrentInfo[index.row()];

            if ( role == QualityRole )
                return torrentInfo.quality();
            else if ( role == SizeRole )
                return torrentInfo.size();
            else if ( role == PeerRole )
                return torrentInfo.peer();
            else if ( role == SeedRole )
                return torrentInfo.seed();
            else if ( role == DownloadLinkRole )
                return torrentInfo.downloadLink().toString();
        }
        return QVariant();
    }

    void clear()
    {
        for ( int i=_torrentInfo.size()-1; i>=0; --i ) {
            beginRemoveRows(QModelIndex(), rowCount(), rowCount());
            _torrentInfo.remove(i);
            endRemoveRows();
        }
    }

protected:
    QHash<int, QByteArray> roleNames() const
    {
        QHash<int, QByteArray> roles;
        roles[QualityRole] = "quality";
        roles[SizeRole] = "size";
        roles[PeerRole] = "peer";
        roles[SeedRole] = "seed";
        roles[DownloadLinkRole] = "downloadLink";
        return roles;
    }

private:
    QVector<TorrentInfo> _torrentInfo;
};

#endif // TORRENTINFOMODEL

