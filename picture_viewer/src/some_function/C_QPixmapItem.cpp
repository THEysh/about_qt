
#include "C_QPixmapItem.h"


C_QPixmapItem::C_QPixmapItem(Item_Interface *parent,QGraphicsPixmapItem *pixmapItem) {
    parent->interface_scene
}

void C_QPixmapItem::pixmap_show_photo() {
     // 查看是否需要自适应缩放:
    if (scaling || (or_activated_photo_pixmap.size().width() < this->ininterface_Photo_Graphics->viewport()->rect().width() &&
                    or_activated_photo_pixmap.size().height()<interface_Photo_Graphics->viewport()->rect().height())){
        pixmapItem = new QGraphicsPixmapItem(activated_photo_pixmap);
        const QRectF &boundingRect = pixmapItem->boundingRect();
        QPointF center = interface_Photo_Graphics->viewport()->rect().center() - boundingRect.center();
        pixmapItem->setPos(center);
    }
    else{
        pixmapItem = new QGraphicsPixmapItem(or_activated_photo_pixmap);
        const QRectF &boundingRect = pixmapItem->boundingRect();
        pixmapItem->setX((interface_Photo_Graphics->viewport()->rect().width()-boundingRect.width()) / 2);
    }
    scene->addItem(pixmapItem);
    // 设置为拖拽
    pixmapItem->setFlags(QGraphicsItem::ItemIsMovable);
    // interface_Photo_Graphics->setBackgroundBrush(QBrush(*background));

    interface_Photo_Graphics->show();
}

void C_QPixmapItem::click_element(){
    Item_Interface::click_element(); // 调用父类的同名函数
}

void C_QPixmapItem::position_calculation() {
    // 点击后修改图片的尺寸
    int w; int h;
    std::pair<int, int> w_h = get_width_height();
    w = w_h.first; h = w_h.second;
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
