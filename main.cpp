#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStringList>
#include <QString>
#include <QQmlContext>
#include <QWindow>

#include "filesystemmanager.h"
#include "filesystemmodel.h"

#ifdef Q_OS_WINDOWS
#include "platform/windows/WindowsWindow.h"
#endif

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

    #ifdef Q_OS_WINDOWS
        QObject* rootObject = engine.rootObjects().first();

        QWindow* window = qobject_cast<QWindow*>(rootObject);

        WindowsWindow windowsWindow(window);

        app.installNativeEventFilter(&windowsWindow);
    #endif

    return QGuiApplication::exec();
}
