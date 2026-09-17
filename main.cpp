#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStringList>
#include <QString>
#include <filesystem>
#include <iostream>

#include "filesystemmanager.h"

using namespace std;

int main(int argc, char *argv[])
{
    FileSystemManager fileSystemManager;
    QString currentDir = QString::fromStdString(fileSystemManager.GetCurrentPath().string());

    fileSystemManager.LoadDirectory();
    const auto& items = fileSystemManager.GetItems();

    for (const auto& item : items)
    {
        cout << item.GetPath() << endl;
    }

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.setInitialProperties({
        // {"folders", folders},
        // {"files", files},
        {"currentDir", currentDir},
    });

    engine.loadFromModule("File_explorer", "Main");

    return QGuiApplication::exec();
}
