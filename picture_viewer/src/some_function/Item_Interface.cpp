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

Item_Interface::~Item_Interface() {

}

void Item_Interface::click_element() {

}

void Item_Interface::show_photo(QGraphicsView *view, QGraphicsScene *scene) {

}

void Item_Interface::wheelEvent(QWheelEvent *event) {

}




//====================================================================================================

C_QPixmapItem::C_QPixmapItem(QGraphicsPixmapItem *loadpixmap):
        pixmapItem(loadpixmap),
        scaling(true)
{
    or_activated_photo_pixmap = pixmapItem->pixmap();
    activated_photo_pixmap = pixmapItem->pixmap();
}

C_QPixmapItem::~C_QPixmapItem() {

}

void C_QPixmapItem::click_element() {
    Item_Interface::click_element();
}

void C_QPixmapItem::show_photo(QGraphicsView *view, QGraphicsScene *scene) {
    Item_Interface::show_photo(view,scene);

    position_calculation(view->width(),view->height());
    // 先将pixmapItem释放，防止内存泄漏
    delete pixmapItem;
    pixmapItem = nullptr;
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

void C_QPixmapItem::wheelEvent(QWheelEvent *event) {
    Item_Interface::wheelEvent(event);
    if (event->delta() > 0) {  // 缩放
        // 只对pixmapItem场景进行缩放
        pixmapItem->setScale(pixmapItem->scale() * 1.15);
    } else {  // 放大
        pixmapItem->setScale(pixmapItem->scale() / 1.15);
    }
}



//====================================================================================================

C_SvgItem::C_SvgItem(QGraphicsSvgItem *load_svgItem):
        svgItem(load_svgItem) //初始化
{
    if (svgItem != nullptr){
        svgRenderer = svgItem->renderer();
    }else{
        qDebug()<<"svgItem is null";
    }
}


C_SvgItem::~C_SvgItem() {
    delete svgRenderer;
    delete svgItem;
}

void C_SvgItem::click_element() {
    Item_Interface::click_element();
}

void C_SvgItem::show_photo(QGraphicsView *view, QGraphicsScene *scene) {
    Item_Interface::show_photo(view, scene);
    delete svgItem; //防止内存泄漏
    svgItem = new QGraphicsSvgItem(); //必须要创建一个新的svgItem并显示
    svgItem->setSharedRenderer(svgRenderer);

    const QRectF &boundingRect = svgItem->boundingRect();
    QPointF center = view->viewport()->rect().center() - boundingRect.center();
    svgItem->setPos(center); // 计算尺寸，让svgItem保持中心位置

    scene->addItem(svgItem); //将svg条目添加到场景中
    // 设置为拖拽
    svgItem->setFlags(QGraphicsItem::ItemIsMovable);
    view->show();
}

void C_SvgItem::wheelEvent(QWheelEvent *event) {
    Item_Interface::wheelEvent(event);
    if (event->delta() > 0) {  // 缩放
        // 只对pixmapItem场景进行缩放
        svgItem->setScale(svgItem->scale() * 1.15);
    } else {  // 放大
        svgItem->setScale(svgItem->scale() / 1.15);
    }
}

