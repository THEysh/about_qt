//
// Created by top on 2023-05-17.
//

#include <QFileInfo>
#include "my_photo_Graphics.h"
#include "Item_Interface.h"
#include "qDebug.h"
#include "qdebug.h"

Item_Interface::Item_Interface(){

}
void Item_Interface::click_element() {

}

void Item_Interface::show_photo(QGraphicsView *view, QGraphicsScene *scene) {

}


//====================================================================================================

C_QPixmapItem::C_QPixmapItem(QGraphicsPixmapItem *loadpixmap):
        pixmapItem(loadpixmap)
{
    pixmapItem = loadpixmap;
    or_activated_photo_pixmap = pixmapItem->pixmap();
    activated_photo_pixmap = pixmapItem->pixmap();
}
void C_QPixmapItem::click_element() {
    Item_Interface::click_element();
}

void C_QPixmapItem::show_photo(QGraphicsView *view, QGraphicsScene *scene) {
    Item_Interface::show_photo(view,scene);

    position_calculation(view->width(),view->height());

    // 查看是否需要自适应缩放:
    if (scaling || (or_activated_photo_pixmap.size().height()< view->viewport()->rect().height())){
        pixmapItem = new QGraphicsPixmapItem(activated_photo_pixmap);
        const QRectF &boundingRect = pixmapItem->boundingRect();
        QPointF center = view->viewport()->rect().center() - boundingRect.center();
        pixmapItem->setPos(center);
    }
    else{
        pixmapItem = new QGraphicsPixmapItem(or_activated_photo_pixmap);
        const QRectF &boundingRect = pixmapItem->boundingRect();
        pixmapItem->setX((view->viewport()->rect().width()-boundingRect.width()) / 2);
    }

    scene->addItem(pixmapItem);
    // 设置为拖拽
    pixmapItem->setFlags(QGraphicsItem::ItemIsMovable);

    view->show();
}

void C_QPixmapItem::position_calculation(int w, int h) {
    // 点击后修改图片的尺寸

    // 得到原始图片的宽和高
    p_width = or_activated_photo_pixmap.width();
    p_height = or_activated_photo_pixmap.height();
    activated_photo_pixmap = or_activated_photo_pixmap.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    if (w>p_width && h>p_height){
        activated_photo_pixmap = or_activated_photo_pixmap;
    } else{
        activated_photo_pixmap = or_activated_photo_pixmap.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    }
}
