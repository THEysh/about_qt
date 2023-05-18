//
// Created by top on 2023-05-17.
//

#include <QFileInfo>
#include "Item_Interface.h"
#include "qDebug.h"
#include "qdebug.h"

Item_Interface::Item_Interface(){

}
void Item_Interface::click_element() {

}

void Item_Interface::show_photo(QGraphicsView *view, QGraphicsScene *scene) {
    qDebug()<<"void Item_Interface::show_photo(QGraphicsView *view, QGraphicsScene *scene) ";
    view->setBackgroundBrush(QBrush(*background));
}


//====================================================================================================

C_QPixmapItem::C_QPixmapItem(QGraphicsPixmapItem *loaditem)
        : pixmapItem(loaditem)
{
    pixmapItem = loaditem;
}
void C_QPixmapItem::click_element() {
    Item_Interface::click_element();
}

void C_QPixmapItem::show_photo(QGraphicsView *view, QGraphicsScene *scene) {
    Item_Interface::show_photo(view,scene);

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
