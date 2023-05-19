

#ifndef ITEM_INTERFACE_H
#define ITEM_INTERFACE_H
#include "QObject"
#include "my_photo_Graphics.h"

// 把不同类型显示的图片抽样出来
class Item_Interface : public QObject{
Q_OBJECT
public:
    explicit Item_Interface();
    ~Item_Interface() override;
    virtual void click_element();
    virtual void show_photo(QGraphicsView *view, QGraphicsScene *scene);
    virtual void wheelEvent(QWheelEvent *event);
};

class C_QPixmapItem : public Item_Interface{
Q_OBJECT
public:
    explicit C_QPixmapItem(QGraphicsPixmapItem *pixmapItem);
    ~C_QPixmapItem() override;
    void click_element() override;
    void show_photo(QGraphicsView *view, QGraphicsScene *scene); //传入当前的场景，更新图片大小

protected:
    QPixmap activated_photo_pixmap = QPixmap(); // 根据尺寸变化的缩放图
    QPixmap or_activated_photo_pixmap = QPixmap(); //原始图片
    void wheelEvent(QWheelEvent *event) override;
private:
    void position_calculation(int w, int h);
    QGraphicsPixmapItem *pixmapItem = nullptr;
    int p_width = 0;
    int p_height = 0;
    bool scaling = false; //是否需要自适应缩放
};

class C_SvgItem : public Item_Interface{
Q_OBJECT
public:
    explicit C_SvgItem(QGraphicsSvgItem* svgItem);
    ~C_SvgItem() override;
    void click_element() override;
    void show_photo(QGraphicsView *view, QGraphicsScene *scene); //传入当前的场景，更新图片大小
protected:
    void wheelEvent(QWheelEvent *event) override;
private:
    QGraphicsSvgItem* svgItem = nullptr;
    QSvgRenderer* svgRenderer = nullptr;
    int p_width = 0;
    int p_height = 0;
    bool scaling = false; //是否需要自适应缩放
};


#endif // ITEM_INTERFACE_H




//
//class C_SvgItem : public Item_interface{
//public:
//    QSvgRenderer activated_svg;
//    C_SvgItem(Item_interface *parent = nullptr);
//protected:

//private:
//    void Svg_show();
//    void resizeEvent(QResizeEvent *event);
//    void wheelEvent(QWheelEvent *event);
//};

