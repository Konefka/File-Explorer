#ifndef FILESYSTEMITEM_H
#define FILESYSTEMITEM_H

#include <filesystem>

class FileSystemItem
{
private:
    std::filesystem::path path;
    bool isDirectory; // a variable that says if it's a directory

public:
    FileSystemItem(std::filesystem::path itemPath, bool isItemDirectory);

    std::filesystem::path GetPath() const;
    bool IsDirectory() const; // a method that returns isDirectory
};

#endif // FILESYSTEMITEM_H
