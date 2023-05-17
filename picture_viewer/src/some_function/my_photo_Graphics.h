//
// Created by top on 2023-04-23.
//

#ifndef PICTURE_VIEWER_MY_PHOTO_GRAPHICS_H
#define PICTURE_VIEWER_MY_PHOTO_GRAPHICS_H


#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include <QMessageBox>
#include <QTreeWidgetItem>
#include "QMenu"
#include <QSvgRenderer>
#include <QGraphicsSvgItem>

using namespace  std;
class My_Photo_Graphics : public QGraphicsView {
Q_OBJECT
signals:
public:
    QTreeWidgetItem **photo_actived_rootNode = nullptr; //这个指针永远指向active_item
    QCheckBox *that_checkBox= nullptr;
    QPixmap activated_photo_pixmap = QPixmap(); // 根据尺寸变化的缩放图
    QPixmap or_activated_photo_pixmap = QPixmap(); //原始图片
    explicit My_Photo_Graphics(QWidget *parent = nullptr);


public:
    void connect_checkbox();
    void click_show_photo();

private:
    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(or_activated_photo_pixmap); // 用于显示图片的场景
    QPixmap *or_background = new QPixmap(":ui/images/pic_b/wallhaven-nkqrgd.png"); // 设置背景的副本
    QPixmap *background = new QPixmap(":ui/images/pic_b/wallhaven-nkqrgd.png"); // 设置背景
    int p_width = or_activated_photo_pixmap.width();
    int p_height = or_activated_photo_pixmap.height();
    bool scaling = false;
    int mouse_x = 0;
    int mouse_y = 0;

    void Q_pixmap_show();
    void resizeEvent(QResizeEvent *event) override;
    // 处理鼠标滚轮事件
    void wheelEvent(QWheelEvent *event) override;
    // 右键菜单
    void contextMenuEvent(QContextMenuEvent *event) override;

};

class C_QPixmapItem : public QGraphicsPixmapItem{
public:
    QPixmap activated_photo_pixmap = QPixmap(); // 根据尺寸变化的缩放图
    QPixmap or_activated_photo_pixmap = QPixmap(); //原始图片
    C_QPixmapItem(QGraphicsPixmapItem *parent = nullptr);

public:
    void connect_checkbox();
    void click_show_photo();

private:
    float Scale = 1.0; //比例
    void Q_pixmap_show();
    void resizeEvent(QResizeEvent *event);
    void wheelEvent(QWheelEvent *event);

};

class C_SvgItem : public QGraphicsSvgItem{
public:
    QSvgRenderer activated_svg;
    C_SvgItem(QGraphicsSvgItem *parent = nullptr);

private:
    void Svg_show();
    void resizeEvent(QResizeEvent *event);
    void wheelEvent(QWheelEvent *event);
};
#endif
