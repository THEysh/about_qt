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
    QPixmap activated_photo_pixmap = QPixmap(); // 根据尺寸变化的缩放图
    QPixmap or_activated_photo_pixmap = QPixmap(); //原始图片

    My_Photo_Label(QWidget *parent = nullptr) : QLabel(parent) {}

protected:
    void paintEvent(QPaintEvent *event) override
    {
        QLabel::paintEvent(event); //先执行父类
        QPainter painter(this); // 在这个label上创建一个painter,在paintEvent函数中创建QPainter对象，并且在完成绘图工作后要及时销毁该对象。
        this->setPixmap(QPixmap()); //设置一个空对象，随后移动位置为居中
        if (or_activated_photo_pixmap.size().width() < activated_photo_pixmap.size().width() ||
            or_activated_photo_pixmap.size().height() < activated_photo_pixmap.size().height())
        {
            _paint_changesize(or_activated_photo_pixmap,&painter);
        }
        else{
            _paint_changesize(activated_photo_pixmap,&painter);
        }
    }
    void _paint_changesize(const QPixmap& p,QPainter *painter){
        //判断是否选择略缩图，就是说:要展示大于原始的图片尺寸，就选择直接显示原本的图片尺寸。否则就自适应尺寸的大小
        int p1 = this->geometry().width()/2;
        int p2 = p.size().width()/2;
        int p3 = this->geometry().height()/2;
        int p4 = p.size().height()/2;
        QPoint pos(p1-p2, p3-p4); // 移动后的新位置
        painter->drawPixmap(pos,p);
        //
    }
};


#endif //QT_EXAM_MY_PHOTO_LABEL_H
