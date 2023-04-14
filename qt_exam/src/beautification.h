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
#include "ui/ui_file/myfirst_ui.h"
#include "ui/ui_file/Qstring_Interface_switching_ui.h"
#include "ui/ui_file/QSlider_color_ui.h"
#include "ui/ui_file/label_list_ui.h"
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
#include "QMutex"
#include "QUuid"
#include <QtCore>

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


class Net_Class : public QObject{
Q_OBJECT
signals:
    void signals1(QString str);
public slots:
    void onsignals1(QString str){
    mutex.lock();
    cout<<str.toStdString()<<endl;
    for (auto i : down_struct_list){
        cout<<"path:"<<i.path.toStdString()<<endl;
        cout<<"uuid:"<<i.uuid.toStdString()<<endl;
        }
    mutex.unlock();
    }
public:
    QMutex mutex;

    Ui_Show_Label ui_f{};
    QString *ABProjectDir = new QString(PROJECT_ROOT_DIR); //在堆创建一块内存空间，味着在程序运行时动态地分配一块内存空间给这个对象。
    // 在堆上分配内存需要通过调用操作系统的API来完成，因为操作系统会维护一张内存使用情况表，记录哪些内存块已经被使用，哪些还没有被使用。
    QString *temp_image_path = new QString(*ABProjectDir + "/src/temp_dir"); //temp_dir 目录路径
    struct down_struct_inf {
        QDateTime time;
        QString type;
        QString name;
        QString path;
        QString uuid;
    };
    QVector<down_struct_inf> down_struct_list;
    QVector<QString> url_list;

    Net_Class(Ui_Show_Label& ui_f){
        this->ui_f = ui_f;

        QObject::connect(this, &Net_Class::signals1,this, &Net_Class::onsignals1);
        url_list.append("https://w.wallhaven.cc/full/yx/wallhaven-yxexok.jpg");
        url_list.append("https://simpleicons.org/icons/adafruit.svg");
        url_list.append("https://w.wallhaven.cc/full/jx/wallhaven-jx1x7p.jpg");
        down();

    }

    ~Net_Class() override{
        delete ABProjectDir; //析构函数释放内存，必须要手动释放
        delete temp_image_path;
    }

    QString generateUniqueId(QString String)
    {
        //用于生成唯一的标识符
        QUuid uuid = QUuid::createUuidV5(QUuid(), String);
        return uuid.toString();
    }

    void __down(const QString& link_url){
        QUrl url(link_url);

        QNetworkAccessManager manager; //网络管理
        QEventLoop loop;
        QNetworkReply *reply = manager.get(QNetworkRequest(url));

        QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec(); //检测下载是否完成的一个循环

        down_struct_inf struct_temp;
        struct_temp.time = QDateTime::currentDateTime();

        QRegularExpression pattern("\\.([A-Za-z0-9]+)$"); //qt的正则表达式获取 链接"."后面的类型
        QRegularExpressionMatch match = pattern.match(link_url);
        if (match.hasMatch()) {
            QString fileExtension = match.captured(1);
            struct_temp.type = "."+ fileExtension;
        }
        struct_temp.uuid = generateUniqueId(link_url);
        struct_temp.name = generateUniqueId(link_url) + struct_temp.type; //用于生成唯一的标识符
        struct_temp.path = *temp_image_path +"/"+ struct_temp.name;

        down_struct_list.append(struct_temp);

        if (down_struct_list.size()>=url_list.size()){
            // 下载结束发出信号
            emit signals1("work_done");
        }


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

    void __start_Thread_down(const QString& link_url){
        auto *t = new QThread;
        QObject::connect(t, &QThread::started,[this,link_url]() {
            //完成任务发出信号
            //这是在qthread开启多线程，需要一个信号机制，在多线程的内，又写一个lambda函数
            this->__down(link_url);
        });
        t->start();
    }

    void down(){
        for(auto u: url_list){
            __start_Thread_down(u);
        }

    }

    void for_test_cdn(){

    }
};

#endif //QT_EXAM_BEAUTIFICATION_H
