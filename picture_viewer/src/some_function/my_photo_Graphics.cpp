//
// Created by top on 2023-04-23.
//

#include "qdebug.h"
#include <QLabel>
#include <QGuiApplication>
#include <QtGui/QClipboard>
#include <QFileInfo>
#include "My_Photo_Graphics.h"
#include "Item_Interface.h"
#include "qdebug.h"
#include <QSysInfo>
#include <memory>

My_Photo_Graphics::My_Photo_Graphics(QWidget *parent):
// 定义初始化
        QGraphicsView(parent),
        graphics_Item_unique(new Item_Interface()),
        scene(new QGraphicsScene())

{
    background.load(":ui/images/pic_b/wallhaven-nkqrgd.png");
    or_background.load(":ui/images/pic_b/wallhaven-nkqrgd.png");
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
    //初始化背景等等
    show_image_item();
}

void My_Photo_Graphics::wheelEvent(QWheelEvent *event) {
    QGraphicsView::wheelEvent(event);
    const QPointF scenePos = mapToScene(event->pos()); // 获取滚轮事件发生的场景坐标
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    if (graphics_Item_unique!= nullptr){
        graphics_Item_unique->wheelEvent(event);
    } else{
        qDebug()<<"My_Photo_Graphics::wheelEvent";
        return;
    }
    // 将场景坐标映射回视图坐标，以确保变换锚点正确(更新)
    const QPointF viewPoint = mapFromScene(scenePos);
    setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    centerOn(viewPoint);
}

void My_Photo_Graphics::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    qDebug()<<"SIZE:"<<this->size();
    // 更新背景的尺寸
    QRect new_rect(QPoint(0, 0), this->size());
    scene->setSceneRect(new_rect);
    background = or_background.scaled(this->size(), Qt::IgnoreAspectRatio);
    this->setBackgroundBrush(QBrush(background));

    // 更新graphics_Item_unique尺寸
    if (graphics_Item_unique!= nullptr){
        graphics_Item_unique->resizeEvent(event,this, scene);
    }
    else{
        qDebug()<<"My_Photo_Graphics::resizeEvent bug!!";
    }
}

void My_Photo_Graphics::graphics_load_image(const QString &path, const QStringList &imageTypes) {
    // 进行判断，是加入什么类型的图片
    QFileInfo fileInfo(path);

    if (fileInfo.suffix().compare("svg", Qt::CaseInsensitive) == 0){
        qDebug() << "The file is an SVG ,load ...";
        //这是一个使用C++11提供的智能指针模板函数std::make_unique()来创建一个指向C_SvgItem对象的unique_ptr，
        // 其中path是作为构造函数参数传递给C_SvgItem的。std::make_unique()可以用于创建可以管理其生命周期的堆分配
        //对象的std::unique_ptr。与直接使用 new 创建对象相比，使用std::make_unique()可以更加安全和方便.
        graphics_Item_unique = std::make_unique<C_SvgItem>(path);
    }
    else if ((fileInfo.suffix().compare("gif", Qt::CaseInsensitive) == 0)){
        qDebug() << "The file is an gif,load ...";
        return;
    }
    else if (imageTypes.contains(fileInfo.suffix(), Qt::CaseInsensitive)) {
        qDebug() << "The file is ipg,png...,load ...";
        graphics_Item_unique = std::make_unique<C_QPixmapItem>(path,imageTypes);
    }
    else {
        qDebug() << "Unsupported image format: " << path;
        return;
    }
    show_image_item();
}

void My_Photo_Graphics::show_image_item() {
    /*初始化背景
    QGraphicsView 组件的背景和场景是两个不同的概念，因此不同的代码片段可能会对它们的大小进行不同的调整。
    前面两行代码设置场景大小与视图大小一致，即将场景矩形设置为 (0, 0, width, height)，其中 width 和 height 分别为视图的宽和高。
    这样可以确保场景的大小与视图相同，从而使所有的图形项都能够完整地显示在视图中。如果不进行这个设置，场景的大小可能会被设置为默认值，
    这可能导致某些图形项被裁剪或者部分显示。*/
    //scene->clear();

    if ((scene!= nullptr)&&(graphics_Item_unique!= nullptr)){
        graphics_Item_unique->show_photo(this,scene);
    }
    else{
        qDebug()<<"scene:"<<scene<<",image_item:"<<graphics_Item_unique.get();
    }
}

My_Photo_Graphics::~My_Photo_Graphics() {
    // delete other dynamically allocated resources if any
    delete scene;
    qDebug() << "this is : ~My_Photo_Graphics";

}

void My_Photo_Graphics::contextMenuEvent(QContextMenuEvent *event){
    QMenu menu(this);
    QAction *right_rotate = menu.addAction("右旋转90°");
    QAction *left_rotate = menu.addAction("左旋转90°");
    //上面的被qt管理，不会内存泄漏

    connect(right_rotate, &QAction::triggered, [this]() {// 旋转图片，例如90度
        graphics_Item_unique->phot_rotate(true,this);
    });
    connect(left_rotate, &QAction::triggered, [this]() {// 旋转图片，例如90度
        graphics_Item_unique->phot_rotate(false,this);
    });
    menu.exec(event->globalPos());
}



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