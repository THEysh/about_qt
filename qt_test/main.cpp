#include <QCoreApplication>
#include <QFileSystemWatcher>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString path = "C:\\Users\\Administrator\\Desktop\\新建文件夹\\images"; // 要监听的路径

    QFileSystemWatcher watcher;
    watcher.addPath(path); // 添加要监听的路径

    qDebug() << "Watching directory: " << path;

    QObject::connect(&watcher, &QFileSystemWatcher::directoryChanged, [&](const QString &changedPath){
        qDebug() << "Directory changed:" << changedPath;
    });

    return a.exec();
}
