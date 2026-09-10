#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStringList>
#include <QString>
#include <filesystem>

using namespace std;

int main(int argc, char *argv[])
{
    filesystem::path currentPath = R"(C:\)";
    QStringList folders;
    QStringList files;

    if (filesystem::exists(currentPath) && filesystem::is_directory(currentPath)) {
        for (const auto& entry : filesystem::directory_iterator(currentPath)) {
            if (entry.is_directory())
                folders.append(QString::fromStdString(entry.path().filename().string()));
            else if (entry.is_regular_file()) {
                files.append(QString::fromStdString(entry.path().filename().string()));
            }
        }
    }

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    QString currentDir = QString::fromStdString(currentPath.string());
    engine.setInitialProperties({
        {"folders", folders},
        {"files", files},
        {"currentDir", currentDir},
    });

    engine.loadFromModule("File_explorer", "Main");

    return QGuiApplication::exec();
}
