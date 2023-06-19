#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QResource>
#include <QProcess>
#include <QFileSystemWatcher>
#include <QQuickItem>
#include <QQuickWindow>
#include "src/QML_Reloader.h"

void Resource_Registration(){
    QString currentPath = QDir::currentPath();
    // 输出路径
    qDebug() << "Current path: " << currentPath;
    QString path_rcc = QString(currentPath + "/the_qrc.rcc"); //获取项目的.rcc路径
    qDebug() << "path_rcc: " << path_rcc;

    if (QResource::registerResource(path_rcc)) { //获取项目的资源文件
        qDebug() << "Resource file registered successfully!";
    } else {
        qWarning() << "Failed to register resource file，try find currentPath ";
    }

}

void pross_qrc_command(){
    // rcc -binary F:\code\c_code\about_qt\qt_6\qml_fitst_projiect\image\the_qrc.qrc -o myresources.rcc
    // 创建 QProcess 对象
    QProcess process;
    // 设置要执行的命令和参数
    QString command = "rcc";
    QStringList arguments;
    arguments << "-binary" << "F:/code/c_code/about_qt/qt_6/qml_fitst_projiect/image/the_qrc.qrc" << "-o" << "the_qrc.rcc";
    // 启动新进程并执行命令
    process.start(command, arguments);
    // 等待进程结束
    process.waitForFinished();
    // 输出命令执行结果
    QString output = process.readAllStandardOutput();
    qDebug()<<" pross_qrc_command_out"<<output;
}


int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    Resource_Registration();
    QString qmlpath_1 = "F:/code/c_code/about_qt/qt_6/qml_fitst_projiect/image/qml/testqml_1.qml";
    QQmlApplicationEngine engine;
    new QMLReloader(engine, qmlpath_1);
    return app.exec();
}
