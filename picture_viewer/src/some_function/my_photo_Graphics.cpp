//
// Created by top on 2023-04-23.
//
#include "qdebug.h"
#include <QLabel>
#include <QGuiApplication>
#include "QCheckBox"
#include <QtGui/QClipboard>
#include "My_Photo_Graphics.h"
#include "Item_Interface.h"

My_Photo_Graphics::My_Photo_Graphics(QWidget *parent):
        QGraphicsView(parent),
        scene(new QGraphicsScene()),
        or_background(new QPixmap(":ui/images/pic_b/wallhaven-nkqrgd.png")),
        background(new QPixmap(":ui/images/pic_b/wallhaven-nkqrgd.png")),
        interface_photo_graphics(new Item_Interface(this)) //初始化接口
{
    this->setScene(scene);

    setRenderHint(QPainter::Antialiasing, true);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    setInteractive(true);
    // 禁用滚轮
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // 设置为拖拽
    this->setDragMode(static_cast<DragMode>(QGraphicsView::ScrollHandDrag | QGraphicsView::RubberBandDrag));
}

std::pair<int, int> My_Photo_Graphics::get_width_height(){
    int width = this->width();
    int height = this->height();
    return std::make_pair(width, height);
}


void My_Photo_Graphics::click_element() {

}

void My_Photo_Graphics::show_photo() {
    resetTransform(); // 重设位置
}

void My_Photo_Graphics::wheelEvent(QWheelEvent *event) {
    QGraphicsView::wheelEvent(event);
}

void My_Photo_Graphics::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
}

void My_Photo_Graphics::graphics_load_image(const QString &path, const QStringList &type_img) {
    if (interface_photo_graphics!= nullptr){
        interface_photo_graphics->interface_load_image(path,type_img);
    }


}




//
//
//void My_Photo_Graphics::resizeEvent(QResizeEvent *event)
//{
//    scene->clear();
//    int w = this->geometry().width();
//    int h = this->geometry().height();
//    // 设置场景的大小
//    QRect new_rect(QPoint(0, 0), QSize(w, h));
//    scene->setSceneRect(new_rect);
//    *background = or_background->scaled(QSize(w, h), Qt::IgnoreAspectRatio);
//    if (w>p_width && h>p_height){
//        activated_photo_pixmap = or_activated_photo_pixmap;
//    } else{
//        activated_photo_pixmap = or_activated_photo_pixmap.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation);
//    }
//
//    Q_pixmap_show();
//}
//
//void My_Photo_Graphics::wheelEvent(QWheelEvent *event)  {
//
//    const QPointF scenePos = mapToScene(event->pos()); // 获取滚轮事件发生的场景坐标
//    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
//    double scaleFactor = 1.15;
//    if (event->delta() > 0) {  // 缩放
//        // 只对pixmapItem场景进行缩放
//        pixmapItem->setScale(pixmapItem->scale() * scaleFactor);
//    } else {  // 放大
//        pixmapItem->setScale(pixmapItem->scale() / scaleFactor);
//    }
//    // 将场景坐标映射回视图坐标，以确保变换锚点正确(更新)
//    const QPointF viewPoint = mapFromScene(scenePos);
//    setTransformationAnchor(QGraphicsView::AnchorViewCenter);
//    centerOn(viewPoint);
//}
//

//void My_Photo_Graphics::contextMenuEvent(QContextMenuEvent *event)
//{
//    QMenu menu(this);
//    QAction *right_rotate = menu.addAction("右旋转90°");
//    QAction *left_rotate = menu.addAction("左旋转90°");
//    QAction *copy_dirpath = menu.addAction("复制图片路径");
//    connect(right_rotate, &QAction::triggered, [this]() {// 旋转图片，例如90度
//        or_activated_photo_pixmap = or_activated_photo_pixmap.transformed(QTransform().rotate(90));  // 旋转90度
//        if (*photo_actived_rootNode!= nullptr){
//            QString save_path = (*photo_actived_rootNode)->data(0,Qt::UserRole).toString();
//            or_activated_photo_pixmap.save(save_path);
//        }
//        click_show_photo();
//    });
//    connect(left_rotate, &QAction::triggered, [this]() {// 旋转图片，例如90度
//        or_activated_photo_pixmap = or_activated_photo_pixmap.transformed(QTransform().rotate(-90));  // 旋转90度
//        if (*photo_actived_rootNode!= nullptr){
//            QString save_path = (*photo_actived_rootNode)->data(0,Qt::UserRole).toString();
//            or_activated_photo_pixmap.save(save_path);
//        }
//        click_show_photo();
//    });
//
//    connect(copy_dirpath,&QAction::triggered,[this](){
//        if (*photo_actived_rootNode!= nullptr){
//            QClipboard *clipboard = QGuiApplication::clipboard();
//            clipboard->setText((*photo_actived_rootNode)->data(0, Qt::UserRole).toString());
//        }
//    });
//    menu.exec(event->globalPos());
//}
//
//

//void My_Photo_Graphics::connect_checkbox() {
//    if (that_checkBox!= nullptr){
//        that_checkBox->setTristate(false);
//        connect(that_checkBox, &QCheckBox::toggled, [this](bool checked){
//            if (checked) {
//                scaling = true;
//                Q_pixmap_show();
//                // 如果复选框被选中执行的操作
//            } else {
//                scaling = false;
//                Q_pixmap_show();
//                // 如果复选框未被选中执行的操作
//            }
//        });
//    }
//}