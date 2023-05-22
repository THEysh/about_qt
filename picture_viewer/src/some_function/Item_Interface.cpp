//
// Created by top on 2023-05-17.
//

#include <QFileInfo>
#include <memory>
#include <QMovie>
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

void Item_Interface::phot_rotate(bool is_right,QGraphicsView *view) {

}

void Item_Interface::position_calculation(QGraphicsView *view) {

}

//====================================================================================================

C_QPixmapItem::C_QPixmapItem(const QString &path, const QStringList &imageTypes):
    scaling(true)
{
    or_activated_photo_pixmap.load(path, imageTypes.join(',').toUtf8().constData());
    p_width = or_activated_photo_pixmap.width();
    p_height = or_activated_photo_pixmap.height();
    photo_pixmap_unique = std::make_unique<QPixmap>(or_activated_photo_pixmap);
//    activated_photo_pixmap = or_activated_photo_pixmap.scaled(p_width, p_height, Qt::KeepAspectRatio);
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
    //activated_photo_pixmap = or_activated_photo_pixmap.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    if (w>p_width && h>p_height){
        photo_pixmap_unique.reset(&or_activated_photo_pixmap);

    }else{
        photo_pixmap_unique.reset(new QPixmap(or_activated_photo_pixmap.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation)));
    }
    // 查看是否需要自适应缩放:
    if (scaling || (or_activated_photo_pixmap.size().height()< view->viewport()->rect().height())){
        // 这两个语句的效果是相同的，都会创建一个新的QGraphicsPixmapItem对象，并用std::unique_ptr对象管理该对象的内存
        graphics_pixmapItem_unique->setPixmap(*photo_pixmap_unique);
        const QRectF &boundingRect = graphics_pixmapItem_unique->boundingRect();
        QPointF center = view->viewport()->rect().center() - boundingRect.center();
        graphics_pixmapItem_unique->setPos(center);
    }
    else{
        graphics_pixmapItem_unique->setPixmap(*photo_pixmap_unique);
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
    position_calculation(view->width(),view->height(),view); //位置更新
}

void C_QPixmapItem::phot_rotate(bool is_right,QGraphicsView *view){
    Item_Interface::phot_rotate(is_right,view);
    if ((graphics_pixmapItem_unique!= nullptr)&&is_right){
        or_activated_photo_pixmap = or_activated_photo_pixmap.transformed(QTransform().rotate(90));  // 旋转90度
    } else if((graphics_pixmapItem_unique!= nullptr)&&!is_right){
        or_activated_photo_pixmap = or_activated_photo_pixmap.transformed(QTransform().rotate(-90));  // 旋转90度
    } else{ return;}
    position_calculation(view->width(),view->height(),view); //位置更新

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

    const QRectF &boundingRect = graphics_svgItem_unique->boundingRect();
    qDebug()<<"QRectF &boundingRect"<<boundingRect;
    QPointF center = view ->viewport()->rect().center() - boundingRect.center();
    qDebug()<<"center:"<<center;
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

void C_SvgItem::phot_rotate(bool is_right, QGraphicsView *view) {
    Item_Interface::phot_rotate(is_right,view);
    if ((graphics_svgItem_unique != nullptr)&&is_right) { // 检查指针是否为 nullptr
        graphics_svgItem_unique->setTransform(QTransform().rotate(90), true);
    } else if ((graphics_svgItem_unique != nullptr)&&!is_right){
        graphics_svgItem_unique->setTransform(QTransform().rotate(-90), true);
    } else{ return;}
    position_calculation(view);
}

// --------------------------------------------------------------------------
C_GifItem::C_GifItem(const QString &path,QGraphicsView *view,QGraphicsScene *scene)
    {

        au_movie = std::make_unique<QMovie>(path);
        au_movie->start();

        graphics_gifItem_unique = std::make_unique<QGraphicsPixmapItem>();
        gif_pixmap = std::make_unique<QPixmap>(QPixmap::fromImage(au_movie->currentImage()));
        graphics_gifItem_unique->setPixmap(*gif_pixmap);
        // 设置为拖拽 ,要在不为nullpter设置拖拽
        graphics_gifItem_unique->setFlags(QGraphicsItem::ItemIsMovable);
        // 将 QGraphicsPixmapItem 添加到 QGraphicsScene 中
        scene->addItem(graphics_gifItem_unique.get());
        // 定时器更新 QPixmap
        timer.start(16); // 33ms 即约等于一秒钟的 30 帧
        // 连接信号
        _connect();
}

C_GifItem::~C_GifItem(){
    // 释放内存, 因为智能指针，就是不写，内存也会被释放
}
void C_GifItem::_connect() {
    if (au_movie == nullptr){
        qDebug()<<"C_GifItem::_connect(),bug";
        return;
    }
    // 异步更新画面
    QObject::connect(&timer, &QTimer::timeout, [this](){
        gif_pixmap = std::make_unique<QPixmap>(QPixmap::fromImage(au_movie->currentImage()));
        graphics_gifItem_unique->setPixmap(*gif_pixmap);
    });
    //使用 "this" 关键字引入它的作用域,
    QObject::connect(au_movie.get(), &QMovie::frameChanged, [this](int frameIndex){
        QSize temp_size = au_movie->currentPixmap().size();
        qDebug() << "Current Frame Index: " << frameIndex;
        qDebug() << "Current Frame size: " << temp_size;
    });
    connect(au_movie.get(), &QMovie::resized, [](const QSize& size){
        qDebug() << "Animation Resized to " << size;
    });
    connect(au_movie.get(), &QMovie::started, [](){
        qDebug() << "Animation started, Animation started " ;
    });
}

void C_GifItem::show_photo(QGraphicsView *view, QGraphicsScene *scene) {
    Item_Interface::show_photo(view, scene);
    // 更新坐标
    position_calculation(view);
    view->show();
}

void C_GifItem::click_element() {
    Item_Interface::click_element();
}

void C_GifItem::wheelEvent(QWheelEvent *event) {
    Item_Interface::wheelEvent(event);
    if (graphics_gifItem_unique == nullptr){
        qDebug()<<"C_GifItem::wheelEvent bug";
    }
    if (event->delta() > 0) {  // 缩放
        // 只对pixmapItem场景进行缩放
        graphics_gifItem_unique->setScale(graphics_gifItem_unique->scale() * 1.15);
    } else {  // 放大
        graphics_gifItem_unique->setScale(graphics_gifItem_unique->scale() / 1.15);
    }
}

void C_GifItem::resizeEvent(QResizeEvent *event, QGraphicsView *view, QGraphicsScene *scene) {
    Item_Interface::resizeEvent(event, view, scene);
    position_calculation(view);
}

void C_GifItem::phot_rotate(bool is_right, QGraphicsView *view) {
    Item_Interface::phot_rotate(is_right, view);
    if (graphics_gifItem_unique == nullptr){
        qDebug()<<"C_GifItem::wheelEvent bug";
    }
    if ((graphics_gifItem_unique != nullptr)&&is_right) { // 检查指针是否为 nullptr
        graphics_gifItem_unique->setTransform(QTransform().rotate(90), true);
    } else if ((graphics_gifItem_unique != nullptr)&&!is_right){
        graphics_gifItem_unique->setTransform(QTransform().rotate(-90), true);
    } else{ return;}
    position_calculation(view);
}

void C_GifItem::position_calculation(QGraphicsView *view) {
    Item_Interface::position_calculation(view);
    if (graphics_gifItem_unique == nullptr){
        qDebug()<<"C_GifItem::wheelEvent bug";
    }
    const QRectF &boundingRect = graphics_gifItem_unique->boundingRect();
    qDebug()<<"QRectF &boundingRect"<<boundingRect;
    QPointF center = view ->viewport()->rect().center() - boundingRect.center();
    qDebug()<<"center:"<<center;
    graphics_gifItem_unique->setPos(center);
}


