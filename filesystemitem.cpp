#include "filesystemitem.h"

FileSystemItem::FileSystemItem(std::filesystem::path itemPath, bool isItemDirectory)
{
    path = itemPath;
    isDirectory = isItemDirectory;
}

std::filesystem::path FileSystemItem::GetPath() const
{
    return path;
}

bool FileSystemItem::IsDirectory() const {
    return isDirectory;
}