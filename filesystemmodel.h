#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <QByteArray>
#include <QVariant>

#include <QDesktopServices>
#include <QUrl>

#include "filesystemmanager.h"

class FileSystemModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString currentPath READ currentPath NOTIFY currentPathChanged)

private:
    FileSystemManager* manager;

    enum Roles
    {
        NameRole = Qt::UserRole + 1,
        IsDirectoryRole,
        PathRole
    };

public:
    explicit FileSystemModel(FileSystemManager* manager, QObject* parent = nullptr);

    Q_INVOKABLE void changePath(const QString& path);
    QString currentPath() const;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void Refresh();

    Q_INVOKABLE void openItem(const QString& path);

signals:
    void currentPathChanged();
};

#endif // FILESYSTEMMODEL_H
