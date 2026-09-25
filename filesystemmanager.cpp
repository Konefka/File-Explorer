#include "filesystemmanager.h"
#include <algorithm>

FileSystemManager::FileSystemManager()
{
    currentPath = R"(C:\)";
}

void FileSystemManager::ChangePath(const std::filesystem::path& newPath)
{
    if (std::filesystem::exists(newPath) && std::filesystem::is_directory(newPath))
    {
        currentPath = newPath;
    }
}

std::filesystem::path FileSystemManager::GetCurrentPath() const
{
    return currentPath;
}

void FileSystemManager::LoadDirectory()
{
    items.clear();

    if (!std::filesystem::exists(currentPath)) return;

    for (const auto& entry : std::filesystem::directory_iterator(currentPath))
    {
        FileSystemItem item(entry.path(), entry.is_directory());
        items.push_back(item);
    }

    std::sort(items.begin(), items.end(),
    [](const FileSystemItem& a, const FileSystemItem& b)
    {
        if (a.IsDirectory() != b.IsDirectory())
        {
            return a.IsDirectory() > b.IsDirectory();
        }

        return a.GetPath().filename().string() < b.GetPath().filename().string();
    });
}

const std::vector<FileSystemItem>& FileSystemManager::GetItems() const
{
    return items;
}