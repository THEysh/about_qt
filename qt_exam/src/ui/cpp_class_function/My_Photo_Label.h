//
// Created by top on 2023-04-14.
//

#ifndef QT_EXAM_MY_PHOTO_LABEL_H
#define QT_EXAM_MY_PHOTO_LABEL_H


#include <QLabel>
#include <QPixmap>
#include <QDateTime>
#include <QPainter>
#include <iostream>

using namespace std;
class My_Photo_Label : public QLabel
{
public:
    QPixmap activated_photo_pixmap = QPixmap();
    My_Photo_Label(QWidget *parent = nullptr) : QLabel(parent) { }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        QLabel::paintEvent(event); //先执行父类
        QPainter painter(this);
        cout<<activated_photo_pixmap.isNull()<<endl;
        //this->setPixmap(activated_photo_pixmap);
        painter.drawPixmap(200,200,activated_photo_pixmap);

    }
};


#endif //QT_EXAM_MY_PHOTO_LABEL_H
