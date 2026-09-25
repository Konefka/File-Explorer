#include "filesystemmodel.h"

FileSystemModel::FileSystemModel(FileSystemManager* manager, QObject* parent)
    : QAbstractListModel(parent), manager(manager){}


QHash<int, QByteArray> FileSystemModel::roleNames() const
{
    return {
        { NameRole, "name" },
        { IsDirectoryRole, "isDirectory" },
        { PathRole, "path" }
    };
}

void FileSystemModel::changePath(const QString& path)
{
    manager->ChangePath(
        std::filesystem::path(path.toStdString())
        );

    Refresh();

    emit currentPathChanged();
}

QString FileSystemModel::currentPath() const
{
    return QString::fromStdString(
        manager->GetCurrentPath().string()
        );
}

int FileSystemModel::rowCount(const QModelIndex& parent) const
{
    if(parent.isValid())
        return 0;

    return static_cast<int>(manager->GetItems().size());
}

QVariant FileSystemModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= static_cast<int>(manager->GetItems().size()))
    {
        return {};
    }

    const FileSystemItem& item = manager->GetItems()[index.row()];

    switch (role)
    {
    case NameRole:
        return QString::fromStdString(item.GetPath().filename().string());

    case IsDirectoryRole:
        return item.IsDirectory();

    case PathRole:
        return QString::fromStdString(item.GetPath().string());

    default:
        return {};
    }
}

void FileSystemModel::Refresh()
{
    beginResetModel();

    manager->LoadDirectory();

    endResetModel();
}

void FileSystemModel::openItem(const QString& path)
{
    QDesktopServices::openUrl(
        QUrl::fromLocalFile(path)
    );
}