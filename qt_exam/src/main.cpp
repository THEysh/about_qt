#include <QApplication>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include "iostream"
#include "ui/myfirst_ui.h"
#include "ui/Qstring_Interface_switching_ui.h"
#include "ui/QSlider_color_ui.h"
#include "function.h"
#include <QResource>
#include <QDir>
#include <QApplication>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>
#include <QFontDatabase>

void Resource_Registration(){
    QString ProjectDir = PROJECT_ROOT_DIR;
    std::cout << "Project directory: " << ProjectDir.toStdString() << std::endl; //获取项目的绝对路径
    QString path_rcc = QString(ProjectDir + "/src/ui/my_qrc.rcc"); //获取项目的.rcc路径
    QFile file(path_rcc);
    std::cout << "Project directory of .rcc: " <<  path_rcc.toStdString() << std::endl; //
    if (QResource::registerResource(path_rcc)) { //获取项目的资源文件
    qDebug() << "Resource file registered successfully!";
    } else {
    qWarning() << "Failed to register resource file";
    }
}

void net(QApplication &a){
    // 使用网络编程，下载一个图片放在桌面
    QString imageUrl = "https://w.wallhaven.cc/full/yx/wallhaven-yxemzd.jpg";
    QUrl url(imageUrl);

    QNetworkAccessManager manager;
    QEventLoop loop;
    QNetworkReply *reply = manager.get(QNetworkRequest(url));

    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if(reply->error() != QNetworkReply::NoError)
    {
        qWarning() << "Failed to download image: " << reply->errorString();
    }
    else
    {
        QString desktopPath = QDir::homePath() + "/Desktop";
        QFile file(desktopPath + "/wallpaper.jpg");
        if(file.open(QIODevice::WriteOnly))
        {
            file.write(reply->readAll());
            file.close();
            qDebug() << "Image downloaded and saved to desktop.";
        }
        else
        {
            qWarning() << "Failed to save image to desktop.";
        }
    }

    reply->deleteLater();
}

int main(int argc, char *argv[])
{

    Resource_Registration(); // 注册资源文件（包括图片的rcc文件，这是由qrc转换出来的）
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
//    Slider_Color my_class_ui_color(ui_color);
//    QWidget3->show();


    int fontId = QFontDatabase::addApplicationFont(":/fonts/Font Awesome 6 Brands-Regular-400.otf");
    if (fontId == -1) {
        qDebug() << "Failed to load font";
        return 1;
    }

    qDebug() << "Font ID:" << fontId;

    QFont fontAwesome("FontAwesome", 19);
    https://fontawesome.com/v5/icons/sticky-note?f=classic&s=solid
    // 创建Label，并设置样式和图标
    QLabel label;
    label.setStyleSheet("QLabel { color: #111; fonts-family: FontAwesome; }");
    label.setFont(fontAwesome);
    label.setText("\uf249"); // FontAwesome图标的Unicode码
    label.show();

    return QApplication::exec();

}
