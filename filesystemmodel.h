#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <QByteArray>
#include <QVariant>

#include "filesystemmanager.h"

class FileSystemModel : public QAbstractListModel
{
    Q_OBJECT

private:
    FileSystemManager* manager;

public:
    explicit FileSystemModel(FileSystemManager* manager, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;
    enum Roles
    {
        NameRole = Qt::UserRole + 1,
        IsDirectoryRole,
        PathRole
    };

    Q_INVOKABLE void ChangePath(const QString& path);
    void Refresh();
};

#endif // FILESYSTEMMODEL_H
