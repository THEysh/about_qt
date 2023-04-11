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


class Net_Image {
public:
    QString *ABProjectDir = new QString(PROJECT_ROOT_DIR);
    Net_Image() = default;
    void down() {
        // 使用网络编程，下载一个图片放在桌面
        QString imageUrl = "https://w.wallhaven.cc/full/5g/wallhaven-5g57w1.jpg";
        QUrl url(imageUrl);

        QNetworkAccessManager manager;
        QEventLoop loop;
        QNetworkReply *reply = manager.get(QNetworkRequest(url));

        QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();

        if (reply->error() != QNetworkReply::NoError) {
            qWarning() << "Failed to download image: " << reply->errorString();
        } else {
            QString desktopPath = QDir::homePath() + "/Desktop";
            QFile file(desktopPath + "/wallpaper.jpg");
            if (file.open(QIODevice::WriteOnly)) {
                file.write(reply->readAll());
                file.close();
                qDebug() << "Image downloaded and saved to desktop.";
            } else {
                qWarning() << "Failed to save image to desktop.";
            }
        }

        reply->deleteLater();
    }

    QLabel* down_gif_show(){
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
        movie->setSpeed(400);
        // 创建 QLabel 对象并设置 QMovie 对象作为其动画
        QLabel *label = new QLabel();
        label->setMovie(movie);
        label->show();
        // 播放 GIF 动画
        movie->start();
        return label;
    }

    QLabel* show_label(){
        // 使用label显示一张网络图片,返回返回这个label的地址, 使用 this.label1_1()->show(); //使用显示图片
        QLabel *label = new QLabel;
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



#endif //QT_EXAM_BEAUTIFICATION_H
