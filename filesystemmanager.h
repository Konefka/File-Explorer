#ifndef FILESYSTEMMANAGER_H
#define FILESYSTEMMANAGER_H

#include <filesystem>
#include <vector>

#include "filesystemitem.h"

class FileSystemManager
{
private:
    std::filesystem::path currentPath;
    std::vector<FileSystemItem> items;

public:
    FileSystemManager();

    void ChangePath(const std::filesystem::path& newPath);
    std::filesystem::path GetCurrentPath() const;

    void LoadDirectory();
    const std::vector<FileSystemItem>& GetItems() const;
};

#endif // FILESYSTEMMANAGER_H
