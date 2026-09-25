#ifndef FILESYSTEMITEM_H
#define FILESYSTEMITEM_H

#include <filesystem>

class FileSystemItem
{
private:
    std::filesystem::path path;
    bool isDirectory;

public:
    FileSystemItem(std::filesystem::path itemPath, bool itemIsDirectory);

    std::filesystem::path GetPath() const;
    bool IsDirectory() const;
};

#endif // FILESYSTEMITEM_H
