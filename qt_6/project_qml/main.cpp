#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // 获取应用程序的目录路径
    QString appPath = QCoreApplication::applicationDirPath();
    // 拼接文件路径
    QString qmlPath = appPath + "/main.qml";
    qDebug() << qmlPath;
    // 检查文件是否存在
    if (!QFile(qmlPath).exists()) {
        qDebug() << "无法找到文件：" << qmlPath;
        return -1;
    }
    QQmlApplicationEngine engine;
    engine.load(QUrl::fromLocalFile(qmlPath));

    return app.exec();
}
