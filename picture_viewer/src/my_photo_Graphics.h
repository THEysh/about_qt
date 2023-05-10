//
// Created by top on 2023-04-23.
//

#ifndef PICTURE_VIEWER_MY_PHOTO_GRAPHICS_H
#define PICTURE_VIEWER_MY_PHOTO_GRAPHICS_H

#include "Qtimer"
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <iostream>
#include <QWheelEvent>
using namespace  std;
class My_Photo_Graphics : public QGraphicsView {
Q_OBJECT
signals:
public:
    QGraphicsScene* scene = new QGraphicsScene();
    QPixmap activated_photo_pixmap = QPixmap(); // 根据尺寸变化的缩放图
    QPixmap or_activated_photo_pixmap = QPixmap(); //原始图片

    int p_width = or_activated_photo_pixmap.width();
    int p_height = or_activated_photo_pixmap.height();

    int pot_x = 0; int pot_y = 0;
    explicit My_Photo_Graphics(QWidget *parent = nullptr) : QGraphicsView(parent) {
        this->setScene(scene);
        // 禁用滚轮
        this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        // 设置为拖拽
        this->setDragMode(static_cast<DragMode>(QGraphicsView::ScrollHandDrag | QGraphicsView::RubberBandDrag));

    }
private:
    int mouse_x = 0;
    int mouse_y = 0;
    QTimer* timer_mousepress = new QTimer();
public:
    void click_show_photo(){
        scene->clear();
        // 将场景缩放恢复为默认值 1.0
        resetTransform();

        int w = this->geometry().width();
        int h = this->geometry().height();
        // 得到原始图片的宽和高
        p_width = or_activated_photo_pixmap.width();
        p_height = or_activated_photo_pixmap.height();

        activated_photo_pixmap = or_activated_photo_pixmap.scaled(w,h,Qt::KeepAspectRatio);

        if (w>p_width && h>p_height){
            activated_photo_pixmap = or_activated_photo_pixmap;
        } else{
            activated_photo_pixmap = or_activated_photo_pixmap.scaled(w,h,Qt::KeepAspectRatio);
        }
        Q_pixmap_show();
    }

protected:
    void Q_pixmap_show(){

        auto* pixmapItem = new QGraphicsPixmapItem(activated_photo_pixmap);
        scene->addItem(pixmapItem);
            // 计算中心坐标并居中显示
        const QRectF &boundingRect = pixmapItem->boundingRect();
        QPointF center = this->viewport()->rect().center() - boundingRect.center();
        pixmapItem->setPos(center);
        // 设置为拖拽
        pixmapItem->setFlags(QGraphicsItem::ItemIsMovable);

        this->show();
    }
    void resizeEvent(QResizeEvent *event) override
    {
        scene->clear();
        int w = this->geometry().width();
        int h = this->geometry().height();
        // 设置场景的大小
        QRect new_rect(QPoint(0, 0), QSize(w, h));
        scene->setSceneRect(new_rect);

        if (w>p_width && h>p_height){
            activated_photo_pixmap = or_activated_photo_pixmap;
        } else{
            activated_photo_pixmap = or_activated_photo_pixmap.scaled(w,h,Qt::KeepAspectRatio);
        }
        Q_pixmap_show();
    }
    // 处理鼠标滚轮事件
    void wheelEvent(QWheelEvent *event) override {
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse); // 设置变换锚点
        double scaleFactor = 1.15;
        if (event->delta() > 0) {  // 缩放
            scale(scaleFactor, scaleFactor);
        } else {  // 放大
            scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        }
    }
};


#endif //PICTURE_VIEWER_MY_PHOTO_GRAPHICS_H
