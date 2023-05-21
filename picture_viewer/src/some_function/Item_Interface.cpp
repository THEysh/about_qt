//
// Created by top on 2023-05-17.
//

#include <QFileInfo>
#include <memory>
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

void Item_Interface::resizeEvent(QResizeEvent *event, QGraphicsView *view, QGraphicsScene *scene) {

}

//====================================================================================================

C_QPixmapItem::C_QPixmapItem(const QString &path, const QStringList &imageTypes){
    or_activated_photo_pixmap.load(path, imageTypes.join(',').toUtf8().constData());
    p_width = or_activated_photo_pixmap.width();
    p_height = or_activated_photo_pixmap.height();
    activated_photo_pixmap = or_activated_photo_pixmap.scaled(p_width, p_height, Qt::KeepAspectRatio);

    if (!or_activated_photo_pixmap.isNull()) {
        qDebug() << "Image loaded successfully.";
        // 创建一个指向 QGraphicsPixmapItem 对象的指针，并将其传递给 C_QPixmapItem 类的构造函数
        graphics_pixmapItem_unique = std::make_unique<QGraphicsPixmapItem>();
        graphics_pixmapItem_unique->setPixmap(or_activated_photo_pixmap);
    }
    else {
        qDebug() << "Failed to load image from" << path;
    }

}

C_QPixmapItem::~C_QPixmapItem() {
}

void C_QPixmapItem::click_element() {
    Item_Interface::click_element();
}

void C_QPixmapItem::show_photo(QGraphicsView *view, QGraphicsScene *scene) {
    Item_Interface::show_photo(view,scene);
    qDebug()<<"graphics_pixmapItem_unique->pixmap():"<<graphics_pixmapItem_unique->pixmap();
    // 根据画面进行位置调整
    position_calculation(view->width(),view->height(),view);

    scene->addItem(graphics_pixmapItem_unique.get());
    // 设置为拖拽
    graphics_pixmapItem_unique->setFlags(QGraphicsItem::ItemIsMovable);
    view->show();
}

void C_QPixmapItem::position_calculation(int w, int h,QGraphicsView *view) {
    // 得到原始图片的宽和高
    p_width = or_activated_photo_pixmap.width();
    p_height = or_activated_photo_pixmap.height();
    activated_photo_pixmap = or_activated_photo_pixmap.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    if (w>p_width && h>p_height){
        activated_photo_pixmap = or_activated_photo_pixmap;
    }else{
        activated_photo_pixmap = or_activated_photo_pixmap.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    }
    // 查看是否需要自适应缩放:
    if (scaling || (or_activated_photo_pixmap.size().height()< view->viewport()->rect().height())){
        // 这两个语句的效果是相同的，都会创建一个新的QGraphicsPixmapItem对象，并用std::unique_ptr对象管理该对象的内存
        graphics_pixmapItem_unique->setPixmap(activated_photo_pixmap);
        const QRectF &boundingRect = graphics_pixmapItem_unique->boundingRect();
        QPointF center = view->viewport()->rect().center() - boundingRect.center();
        graphics_pixmapItem_unique->setPos(center);
    }
    else{
        graphics_pixmapItem_unique->setPixmap(or_activated_photo_pixmap);
        const QRectF &boundingRect = graphics_pixmapItem_unique->boundingRect();
        graphics_pixmapItem_unique->setX((view->viewport()->rect().width()-boundingRect.width()) / 2);
    }
}

void C_QPixmapItem::wheelEvent(QWheelEvent *event) {
    Item_Interface::wheelEvent(event);
    if (event->delta() > 0) {  // 缩放
        // 只对pixmapItem场景进行缩放
        graphics_pixmapItem_unique->setScale(graphics_pixmapItem_unique->scale() * 1.15);
    } else {  // 放大
        graphics_pixmapItem_unique->setScale(graphics_pixmapItem_unique->scale() / 1.15);
    }
}

void C_QPixmapItem::resizeEvent(QResizeEvent *event, QGraphicsView *view, QGraphicsScene *scene) {
    Item_Interface::resizeEvent(event, view, scene);
    if (graphics_pixmapItem_unique!= nullptr){
        position_calculation(view->width(),view->height(),view);
        // 查看是否需要自适应缩放:
        if (scaling || (or_activated_photo_pixmap.size().height()< view->viewport()->rect().height())){
            // 这两个语句的效果是相同的，都会创建一个新的QGraphicsPixmapItem对象，并用std::unique_ptr对象管理该对象的内存
            // graphics_pixmapItem_unique.reset(new QGraphicsPixmapItem()) ;
            graphics_pixmapItem_unique->setPixmap(activated_photo_pixmap);
            const QRectF &boundingRect = graphics_pixmapItem_unique->boundingRect();
            QPointF center = view->viewport()->rect().center() - boundingRect.center();
            graphics_pixmapItem_unique->setPos(center);
        }
        else{
            // graphics_pixmapItem_unique.reset(new QGraphicsPixmapItem());
            graphics_pixmapItem_unique->setPixmap(or_activated_photo_pixmap);
            const QRectF &boundingRect = graphics_pixmapItem_unique->boundingRect();
            graphics_pixmapItem_unique->setX((view->viewport()->rect().width()-boundingRect.width()) / 2);
        }
    } else{
        qDebug()<<"C_QPixmapItem::resizeEvent,graphics_pixmapItem_unique:"<<graphics_pixmapItem_unique.get();
    }
}


//====================================================================================================

C_SvgItem::C_SvgItem(const QString &path):
        svgrender_unique(new QSvgRenderer()),
        graphics_svgItem_unique(new QGraphicsSvgItem())
{
    bool loadResult = svgrender_unique ->load(path); // 加载 SVG 文件
    if (loadResult){
        graphics_svgItem_unique->setSharedRenderer(svgrender_unique.get());
        graphics_svgItem_unique->setScale(1);
    }
    else{
        qDebug()<<"QSvgRenderer load fail";
    }
}

C_SvgItem::~C_SvgItem() {

}

void C_SvgItem::click_element() {
    Item_Interface::click_element();
}

void C_SvgItem::show_photo(QGraphicsView *view, QGraphicsScene *scene) {
    Item_Interface::show_photo(view, scene);
    // 计算尺寸，让svgItem保持中心位置
    position_calculation(view);

    scene->addItem(graphics_svgItem_unique.get()); //将svg条目添加到场景中
    //     设置为拖拽
    graphics_svgItem_unique->setFlags(QGraphicsItem::ItemIsMovable);
    view->show();
}

void C_SvgItem::position_calculation(QGraphicsView *view) {
    graphics_svgItem_unique->setSharedRenderer(svgrender_unique.get());
    const QRectF &boundingRect = graphics_svgItem_unique->boundingRect();
    QPointF center = view ->viewport()->rect().center() - boundingRect.center();
    graphics_svgItem_unique->setPos(center);
}

void C_SvgItem::wheelEvent(QWheelEvent *event) {
    Item_Interface::wheelEvent(event);
    if (event->delta() > 0) {  // 缩放
        // 只对pixmapItem场景进行缩放
        graphics_svgItem_unique->setScale(graphics_svgItem_unique->scale() * 1.15);
    } else {  // 放大
        graphics_svgItem_unique->setScale(graphics_svgItem_unique->scale() / 1.15);
    }
}

void C_SvgItem::resizeEvent(QResizeEvent *event, QGraphicsView *view, QGraphicsScene *scene) {
    Item_Interface::resizeEvent(event, view, scene);
    position_calculation(view);
}



