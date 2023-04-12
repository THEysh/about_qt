//
// Created by top on 2023-04-10.
//

#ifndef QT_EXAM_BEAUTIFICATION_H
#define QT_EXAM_BEAUTIFICATION_H
#include <QApplication>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include "iostream"
#include "ui/myfirst_ui.h"
#include "ui/Qstring_Interface_switching_ui.h"
#include "ui/QSlider_color_ui.h"
#include "ui/label_list_ui.h"
#include "function.h"
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
#include <QSvgWidget>
#include <QVector>

class Net_Image : public QObject{
public:
    QString *ABProjectDir = new QString(PROJECT_ROOT_DIR);
    Net_Image() = default;

    pair<QLabel*,QMovie*> down_gif_show(){
        //下载一张gif 保存到temp_dir目录并加载到label里
        QUrl url("https://img.zcool.cn/community/01ef345bcd8977a8012099c82483d3.gif");
        QNetworkRequest request(url);
        QNetworkAccessManager manager;

        QNetworkReply *reply = manager.get(request);

        // 同步等待网络请求完成
        QEventLoop loop;
        QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec();

        // 保存文件
        QFile file( *ABProjectDir + "/src/temp_dir/animated.gif");

        if (file.open(QIODevice::WriteOnly)) {
            file.write(reply->readAll());
            file.close();
        } else {
            qWarning() << "Failed to open file for writing.";
        }

        reply->deleteLater();

        auto *movie = new QMovie(*ABProjectDir + "/src/temp_dir/animated.gif");

        movie->setSpeed(300); //速度3倍
        // 创建 QLabel 对象并设置 QMovie 对象作为其动画
        QLabel *label = new QLabel();

        label->setMovie(movie);
        // 播放 GIF 动画
        movie->start();

        pair<QLabel*,QMovie*> re = make_pair(label, movie);

        return re;
    }

    QLabel* show_label(){
        // 使用label显示一张网络图片,返回返回这个label的地址, 使用 this.label1_1()->show(); //使用显示图片
        auto *label = new QLabel;
        QNetworkAccessManager manager;

        // Create a network request for the image
        QUrl url("https://w.wallhaven.cc/full/5g/wallhaven-5g57w1.jpg");
        QNetworkRequest request(url);

        // Send the request and wait for the response
        QNetworkReply *reply = manager.get(request);
        QEventLoop loop;
        QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec();

        // Check if the request was successful
        if (reply->error() != QNetworkReply::NoError) {
            qWarning() << "Failed to download image:" << reply->errorString();
        }

        // Create a QPixmap from the downloaded image data
        QPixmap pixmap;
        pixmap.loadFromData(reply->readAll());

        // Set the pixmap as the content of the label
        label->setPixmap(pixmap);

        return label;
    }

};

class Net_Label_Class : public QObject{
public:
    Ui_Show_Label ui_f{};
    QString *ABProjectDir = new QString(PROJECT_ROOT_DIR); //在堆创建一块内存空间，味着在程序运行时动态地分配一块内存空间给这个对象。
    // 在堆上分配内存需要通过调用操作系统的API来完成，因为操作系统会维护一张内存使用情况表，记录哪些内存块已经被使用，哪些还没有被使用。
    QString *temp_image_path = new QString(*ABProjectDir + "/src/temp_dir"); //temp_dir 目录路径
    struct down_struct_inf {
        QDateTime time;
        QString name;
        QString type;
        QString path;
    };
    QVector<down_struct_inf> down_struct_list;

    Net_Label_Class(Ui_Show_Label& ui_f){
        this->ui_f = ui_f;
        load_and_show_label(ui_f.label_1, "https://simpleicons.org/icons/1001tracklists.svg");
        load_and_show_label(ui_f.label_2,"https://simpleicons.org/icons/adafruit.svg");
        load_and_show_label(ui_f.label_3,"https://simpleicons.org/icons/aerlingus.svg");
        load_and_show_label(ui_f.label_4,"https://simpleicons.org/icons/android.svg");

    }

    ~Net_Label_Class() override{
        delete ABProjectDir; //析构函数释放内存，必须要手动释放
        delete temp_image_path;
    }
    void down(const QString& link_url){
        QUrl url(link_url);

        QNetworkAccessManager manager;
        QEventLoop loop;
        QNetworkReply *reply = manager.get(QNetworkRequest(url));

        QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec(); //检测下载是否完成的一个循环

        down_struct_inf struct_temp;
        struct_temp.time = QDateTime::currentDateTime();
        struct_temp.name = struct_temp.time.toString("yyyyMMdd_hhmmss_zzz");

        QRegularExpression pattern("\\.([A-Za-z0-9]+)$"); //qt的正则表达式获取 链接"."后面的类型
        QRegularExpressionMatch match = pattern.match(link_url);
        if (match.hasMatch()) {
            QString fileExtension = match.captured(1);
            qDebug() << fileExtension;
            struct_temp.type = "."+ fileExtension;
        }
        struct_temp.path = *temp_image_path +"/"+ struct_temp.name + struct_temp.type;
        down_struct_list.append(struct_temp);

        //QString desktopPath = *ABProjectDir + "/src/temp_dir";
        // Check if the request was successful
        if (reply->error() != QNetworkReply::NoError) {
            qWarning() << "Failed to download image: " << reply->errorString();
        } else {
            QFile file(struct_temp.path);

            if (file.open(QIODevice::WriteOnly)) {
                file.write(reply->readAll());
                file.close();
                qDebug() << "Image downloaded saved to: " + struct_temp.path;
            } else {
                qWarning() << "save failed and save path is:" + struct_temp.path;
            }
        }

        reply->deleteLater();
    }

    void load_and_show_label(QLabel *mylabel, const QString& link_url){
        auto *label = mylabel;
        down(link_url);
        //this->down(link_url);

//        QSvgWidget* svgWidget = new QSvgWidget(desktopPath + "/abc.svg");
//        layout.addWidget(svg_widget)
//        svgWidget->show();
        // Create a QPixmap from the downloaded image data

    }
};

#endif //QT_EXAM_BEAUTIFICATION_H
