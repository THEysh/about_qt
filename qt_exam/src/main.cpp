#include <QApplication>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include "iostream"
#include "ui/myfirst_ui.h"
#include "ui/Qstring_Interface_switching_ui.h"
#include "ui/QSlider_color_ui.h"
#include "function.h"
#include "ui/label_list_ui.h"
#include "beautification.h"
#include <QResource>
#include <QDir>
#include <QApplication>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>
#include <QFontDatabase>
#include "QMovie"
#include "QTimer"
QString* Resource_Registration(){
    auto *ProjectDir = new QString(PROJECT_ROOT_DIR);

    QString path_rcc = QString(*ProjectDir + "/src/ui/my_qrc.rcc"); //获取项目的.rcc路径
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
    QString *ABProjectDir = Resource_Registration(); // 注册资源文件（包括图片的rcc文件，这是由qrc转换出来的）,返回路径
    std::cout << "Project directory: " << ABProjectDir->toStdString() << std::endl; //获取项目的绝对路径
    QApplication app(argc, argv);
    cout<<"------------------------------------------------------------------------------------------"<<endl;

//    auto MainWindow = new QMainWindow();
//    Ui_MainWindow ui_f{};
//    ui_f.setupUi(MainWindow);
//    ThreadReceiver receiver_main(ui_f);
//    MainWindow->show();

//    auto MainWindow2 = new QMainWindow();
//    Ui_Interface_MainWindow ui_interface{};
//    ui_interface.setupUi(MainWindow2);
//    Interface_Class ui_interface_main(ui_interface);
//    MainWindow2->show();

//    auto QWidget3 = new QWidget();
//    Ui_QSlider_Color ui_color{};
//    ui_color.setupUi(QWidget3);
//    Slider_Color_Class my_class_ui_color(ui_color);
//    QWidget3->show();

//    Net_Image mynetimage;
//    pair<QLabel*,QMovie*> re = mynetimage.down_gif_show(); //加载一张网络的gif图片并显示在界面
//    re.first->show();

    auto QWidget4 = new QMainWindow();
    Ui_Show_Label ui_label{};
    ui_label.setupUi(QWidget4);
    Net_Label_Class my_ui_f(ui_label);
    QWidget4->show();


    delete ABProjectDir; //清空内存指针
    return QApplication::exec();

}


//    QApplication a(argc, argv);
//
//    // 创建一个QSvgWidget对象
//    QSvgWidget* svgWidget = new QSvgWidget("F:\\code\\PYQT\\pyqt5_silverfox\\Copying_1017\\img\\buttom\\向下收起_expand-down-one.svg");
//
//    // 如果QSvgWidget库成功导入，则该对象应该被正确创建
//    if (svgWidget)
//    {
//        // 显示QSvgWidget对象
//        svgWidget->show();
//
//        // 返回Qt应用程序的执行结果
//        return a.exec();
//    }
//    else
//    {
//        // 如果QSvgWidget库未能成功导入，则打印错误信息并退出应用程序
//        qDebug("Failed to create QSvgWidget.");
//        return -1;
