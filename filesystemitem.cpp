#include "filesystemitem.h"

FileSystemItem::FileSystemItem(std::filesystem::path itemPath, bool itemIsDirectory)
{
    path = itemPath;
    isDirectory = itemIsDirectory;
}

std::filesystem::path FileSystemItem::GetPath() const
{
    return path;
}