//
// Created by top on 2023-05-17.
//

#ifndef PICTURE_VIEWER_C_QPIXMAPITEM_H
#define PICTURE_VIEWER_C_QPIXMAPITEM_H


#include <QPixmap>
#include "Item_Interface.h"


class C_QPixmapItem : public QObject{
    Q_OBJECT
public:
    C_QPixmapItem(Item_Interface *parent, QGraphicsPixmapItem *pixmapItem);

protected:
    QPixmap activated_photo_pixmap = QPixmap(); // 根据尺寸变化的缩放图
    QPixmap or_activated_photo_pixmap = QPixmap(); //原始图片

    void click_element();
    void pixmap_show_photo();
    void position_calculation();
private:
    QGraphicsPixmapItem *pixmapItem = nullptr;
    int p_width = 0;
    int p_height = 0;
    bool scaling = false; //是否需要自适应缩放
};


#endif //PICTURE_VIEWER_C_QPIXMAPITEM_H
