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
#include "Pic_Thread.h"
#include <QSvgRenderer>
#include <QGraphicsSvgItem>
#include <memory>


class My_Qtreewidget;
class Item_Interface;

class My_Photo_Graphics : public QGraphicsView {
Q_OBJECT
public:
    explicit My_Photo_Graphics(QWidget *parent);
    ~My_Photo_Graphics() override;
    QGraphicsScene *scene = nullptr;
    void graphics_load_image(const QString &path, const QStringList &type_img);
    My_Qtreewidget *in_tree;
protected:
    QPixmap or_background;
    QPixmap background;
    void show_image_item();

    void resizeEvent(QResizeEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
private:
//    std::unique_ptr<Item_Interface> graphics_Item_unique;
    Item_Interface_Queue item_queue;
    int item_queue_idx = 0;

};

#endif // MY_PHOTO_GRAPHICS_H


