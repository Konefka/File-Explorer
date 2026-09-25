#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStringList>
#include <QString>
#include <QQmlContext>

#include "filesystemmanager.h"
#include "filesystemmodel.h"

using namespace std;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    FileSystemManager fileSystemManager;
    fileSystemManager.LoadDirectory();

    FileSystemModel fileSystemModel(&fileSystemManager);

    engine.rootContext()->setContextProperty("fileSystemModel", &fileSystemModel);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection
        );

    engine.loadFromModule("File_explorer", "Main");

    return QGuiApplication::exec();
}
