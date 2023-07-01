#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QDir>
#include <QFileSystemWatcher>
#include <QQuickItem>
#include <QResource>
#include <QProcess>
#include "src/code/QML_Reloader.h"


void pross_qrc_command(QString &qrc_path){
    // 创建 QProcess 对象
    QProcess process;
    // 设置要执行的命令和参数
    QString command = "rcc";
    QStringList arguments;
    arguments << "-binary" << qrc_path << "-o" << "the_qrc.rcc";
    // 启动新进程并执行命令
    process.start(command, arguments);
    // 等待进程结束
    process.waitForFinished();
    // 输出命令执行结果
    QString output = process.readAllStandardOutput();
    qDebug()<<" pross_qrc_command_out"<<output;
    QString currentPath = QDir::currentPath();
    // 输出路径
    qDebug() << "Current path: " << currentPath;
    // 注册资源文件
    QString path_rcc = QString(currentPath + "/the_qrc.rcc"); //获取项目的.rcc路径
    if (QResource::registerResource(path_rcc)) { //获取项目的资源文件
        qDebug() << "Resource file registered successfully!";
    } else {
        qWarning() << "Failed to register resource file，try find currentPath ";
    }
}




int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QString qrc_path = R"(F:\code\c_code\about_qt\qt_6\hello_world\src\the_qrc.qrc)";
    pross_qrc_command(qrc_path);
    // QString qmlpath_1 = R"(F:\code\c_code\about_qt\qt_6\hello_world\src\qml\testqml_1.qml)";
    QString qmlpath_2 = R"(F:\code\c_code\about_qt\qt_6\hello_world\src\qml\testqml_2.qml)";
    QQmlApplicationEngine engine;
    QFileSystemWatcher watcher;
    new QMLReloader(engine, qmlpath_2);
    return app.exec();
}
