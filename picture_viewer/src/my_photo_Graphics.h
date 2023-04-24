//
// Created by top on 2023-04-23.
//

#ifndef PICTURE_VIEWER_MY_PHOTO_GRAPHICS_H
#define PICTURE_VIEWER_MY_PHOTO_GRAPHICS_H

#include "Qtimer"
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

class My_Photo_Graphics : public QGraphicsView {
Q_OBJECT
signals:

public:
    QGraphicsScene* scene = new QGraphicsScene();
    QPixmap activated_photo_pixmap = QPixmap(); // 根据尺寸变化的缩放图
    QPixmap or_activated_photo_pixmap = QPixmap(); //原始图片
    int pot_x = 0;
    int pot_y = 0;
    explicit My_Photo_Graphics(QWidget *parent = nullptr) : QGraphicsView(parent) {
        this->setScene(scene);
    }

private:
    int mouse_x = 0;
    int mouse_y = 0;
    QTimer* timer_mousepress = new QTimer();

public:
    void click_show_photo(){
        scene->clear();

        int w = this->geometry().width();
        int h = this->geometry().height();
        activated_photo_pixmap = or_activated_photo_pixmap.scaled(w,h,Qt::KeepAspectRatio);

        this->fitInView(QRectF(0,0, w,h));
        this->show();
    }

protected:

    void resizeEvent(QResizeEvent *event) override
    {
        scene->clear();
        int w = this->geometry().width();
        int h = this->geometry().height();
        activated_photo_pixmap = or_activated_photo_pixmap.scaled(w,h,Qt::KeepAspectRatio);
        scene->addPixmap(activated_photo_pixmap);
        //calculate_center_pos(activated_photo_pixmap);
        this->show();
    }

    std::pair<int,int> calculate_center_pos(QPixmap &p){
        //给一个QPixmap对象p， 计算p与this label居中的位置
        int p1 = this->geometry().width()/2;
        int p2 = p.size().width()/2;
        int p3 = this->geometry().height()/2;
        int p4 = p.size().height()/2;
        pot_x = p1-p2; pot_y = p3-p4;

        return std::make_pair(p1-p2,p3-p4);
    }
};


#endif //PICTURE_VIEWER_MY_PHOTO_GRAPHICS_H
