//
// Created by top on 2023-04-23.
//

#ifndef MY_PHOTO_GRAPHICS_H
#define MY_PHOTO_GRAPHICS_H
#include "QObject"
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include <QMessageBox>
#include <QTreeWidgetItem>
#include "QMenu"
#include <QSvgRenderer>
#include <QGraphicsSvgItem>
#include "Item_Interface.h"

class My_Photo_Graphics : public QGraphicsView {
Q_OBJECT
public:
//    QTreeWidgetItem **photo_actived_rootNode = nullptr; //这个指针永远指向active_item
//    QCheckBox *that_checkBox = nullptr;
    explicit My_Photo_Graphics(QWidget *parent);
    ~My_Photo_Graphics() override;
    QGraphicsScene *scene = nullptr;
    void graphics_load_image(const QString &path, const QStringList &type_img);

protected:
    QPixmap *background = nullptr; // 设置背景
    QPixmap *or_background = nullptr; // 设置背景
    void show_image_item();
    Item_Interface *image_item = nullptr; //创建的图片对象还没被确定，先定义其父类

    void resizeEvent(QResizeEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

};

#endif // MY_PHOTO_GRAPHICS_H



//void Q_pixmap_show();
//void resizeEvent(QResizeEvent *event) override;
//// 处理鼠标滚轮事件
//void wheelEvent(QWheelEvent *event) override;
//// 右键菜单
//void contextMenuEvent(QContextMenuEvent *event) override;

