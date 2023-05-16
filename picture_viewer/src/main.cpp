


#include <QString>
#include <QFile>
#include <iostream>
#include <QResource>
#include <QApplication>
#include <QMainWindow>
#include "qdebug.h"
#include "ui/ui_file/Qtree_ui.h"
#include "function.h"

QString* Resource_Registration(){
    auto *ProjectDir = new QString(PROJECT_ROOT_DIR);

    QString path_rcc = QString(*ProjectDir + "/src/my_qrc.rcc"); //获取项目的.rcc路径
    QFile file(path_rcc);
    std::cout << "Project directory of .rcc: " <<  path_rcc.toStdString() << std::endl; //
    if (QResource::registerResource(path_rcc)) { //获取项目的资源文件
        qDebug() << "Resource file registered successfully!";
    } else {
        qWarning() << "Failed to register resource file";
    }
    return ProjectDir;
}


int main(int argc, char *argv[])
{
    system("chcp 65001"); //用于解决中文乱码
    QString *ABProjectDir = Resource_Registration(); // 注册资源文件（包括图片的rcc文件，这是由qrc转换出来的）,返回路径
    std::cout << "Project directory: " << ABProjectDir->toStdString() << std::endl; //获取项目的绝对路径
    QApplication app(argc, argv);


    auto *QWidget = new QMainWindow();

    Ui_Qtree_Class_UI my_ui{};
    Inherit_UI my_class(my_ui,QWidget);
    QWidget->show();

    delete ABProjectDir; //清空内存指针
    return QApplication::exec();
}