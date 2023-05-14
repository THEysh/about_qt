//
// Created by top on 2023-04-23.
//

#ifndef PICTURE_VIEWER_MY_PHOTO_GRAPHICS_H
#define PICTURE_VIEWER_MY_PHOTO_GRAPHICS_H
#include <QScrollBar>
#include "QTimer"
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <iostream>
#include <QWheelEvent>
#include <QGraphicsBlurEffect>
#include <QMessageBox>
#include <QTreeWidgetItem>
#include "QMenu"

using namespace  std;
class My_Photo_Graphics : public QGraphicsView {
Q_OBJECT
signals:
public:

    QTreeWidgetItem **photo_actived_rootNode = nullptr; //这个指针永远指向active_item
    QPixmap activated_photo_pixmap = QPixmap(); // 根据尺寸变化的缩放图
    QPixmap or_activated_photo_pixmap = QPixmap(); //原始图片

    explicit My_Photo_Graphics(QWidget *parent = nullptr) : QGraphicsView(parent) {
        this->setScene(scene);
        // 禁用滚轮
        this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        // 设置为拖拽
        this->setDragMode(static_cast<DragMode>(QGraphicsView::ScrollHandDrag | QGraphicsView::RubberBandDrag));
    }

private:
    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(activated_photo_pixmap); // 用于显示图片的场景
    QPixmap *or_background = new QPixmap(":ui/images/pic_b/wallhaven-nkqrgd.png"); // 设置背景的副本
    QPixmap *background = new QPixmap(":ui/images/pic_b/wallhaven-nkqrgd.png"); // 设置背景
    int p_width = or_activated_photo_pixmap.width();
    int p_height = or_activated_photo_pixmap.height();
    int pot_x = 0; int pot_y = 0;
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

        pixmapItem = new QGraphicsPixmapItem(activated_photo_pixmap);
        scene->addItem(pixmapItem);
        // 计算中心坐标并居中显示
        const QRectF &boundingRect = pixmapItem->boundingRect();
        QPointF center = this->viewport()->rect().center() - boundingRect.center();
        pixmapItem->setPos(center);
        // 设置为拖拽
        pixmapItem->setFlags(QGraphicsItem::ItemIsMovable);

        this->setBackgroundBrush(QBrush(*background));
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
        *background = or_background->scaled(QSize(w, h), Qt::IgnoreAspectRatio);
        if (w>p_width && h>p_height){
            activated_photo_pixmap = or_activated_photo_pixmap;
        } else{
            activated_photo_pixmap = or_activated_photo_pixmap.scaled(w,h,Qt::KeepAspectRatio);
        }

        Q_pixmap_show();
    }

    // 处理鼠标滚轮事件
    void wheelEvent(QWheelEvent *event) override {
        const QPointF scenePos = mapToScene(event->pos()); // 获取滚轮事件发生的场景坐标
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        double scaleFactor = 1.15;
        if (event->delta() > 0) {  // 缩放
            // 只对pixmapItem场景进行缩放
            pixmapItem->setScale(pixmapItem->scale() * scaleFactor);

        } else {  // 放大
            pixmapItem->setScale(pixmapItem->scale() / scaleFactor);

        }
        // 将场景坐标映射回视图坐标，以确保变换锚点正确(更新)
        const QPointF viewPoint = mapFromScene(scenePos);
        setTransformationAnchor(QGraphicsView::AnchorViewCenter);
        centerOn(viewPoint);
    }

    // 右键菜单
    void contextMenuEvent(QContextMenuEvent *event) override
    {
        QMenu menu(this);
        QAction *right_rotate = menu.addAction("右旋转90°");
        QAction *left_rotate = menu.addAction("左旋转90°");
        connect(right_rotate, &QAction::triggered, [this]() {// 旋转图片，例如90度
            or_activated_photo_pixmap = or_activated_photo_pixmap.transformed(QTransform().rotate(90));  // 旋转90度
            if (*photo_actived_rootNode!= nullptr){
                QString save_path = (*photo_actived_rootNode)->data(0,Qt::UserRole).toString();
                or_activated_photo_pixmap.save(save_path);
            }
            click_show_photo();
        });
        connect(left_rotate, &QAction::triggered, [this]() {// 旋转图片，例如90度
            or_activated_photo_pixmap = or_activated_photo_pixmap.transformed(QTransform().rotate(-90));  // 旋转90度
            if (*photo_actived_rootNode!= nullptr){
                QString save_path = (*photo_actived_rootNode)->data(0,Qt::UserRole).toString();
                or_activated_photo_pixmap.save(save_path);
            }
            click_show_photo();
        });


        menu.exec(event->globalPos());
    }
};


#endif
