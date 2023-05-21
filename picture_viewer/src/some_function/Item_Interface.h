

#ifndef ITEM_INTERFACE_H
#define ITEM_INTERFACE_H
#include "QObject"
#include "my_photo_Graphics.h"
#include "memory"
// 把不同类型显示的图片抽样出来
class Item_Interface : public QObject{
Q_OBJECT
public:
    explicit Item_Interface();
    ~Item_Interface() override;
    virtual void click_element();
    virtual void show_photo(QGraphicsView *view, QGraphicsScene *scene);
    virtual void wheelEvent(QWheelEvent *event);
    virtual void resizeEvent(QResizeEvent *event, QGraphicsView *view, QGraphicsScene *scene);
};


class C_QPixmapItem : public Item_Interface{
Q_OBJECT
public:
    explicit C_QPixmapItem(const QString &path, const QStringList &imageTypes);
    ~C_QPixmapItem() override;
    void click_element() override;
    void show_photo(QGraphicsView *view, QGraphicsScene *scene); //传入当前的场景，更新图片大小

protected:
    void wheelEvent(QWheelEvent *event) override;
    void resizeEvent(QResizeEvent *event, QGraphicsView *view, QGraphicsScene *scene) override;
private:
    void position_calculation(int w, int h, QGraphicsView *view);

    QPixmap activated_photo_pixmap = QPixmap(); // 根据尺寸变化的缩放图
    QPixmap or_activated_photo_pixmap = QPixmap(); //原始图片
    std::unique_ptr<QGraphicsPixmapItem> graphics_pixmapItem_unique;
    int p_width = 0;
    int p_height = 0;
    bool scaling = false; //是否需要自适应缩放
};




class C_SvgItem : public Item_Interface{
Q_OBJECT
public:
    explicit C_SvgItem(const QString &path);
    ~C_SvgItem() override;
    void click_element() override;
    void show_photo(QGraphicsView *view, QGraphicsScene *scene); //传入当前的场景，更新图片大小
protected:
    void wheelEvent(QWheelEvent *event) override;
    void resizeEvent(QResizeEvent *event, QGraphicsView *view, QGraphicsScene *scene) override;
private:
    void position_calculation(QGraphicsView *view);
    std::unique_ptr<QSvgRenderer> svgrender_unique = nullptr;
    std::unique_ptr<QGraphicsSvgItem> graphics_svgItem_unique = nullptr;
    int p_width = 0;
    int p_height = 0;
    bool scaling = false; //是否需要自适应缩放
};


#endif // ITEM_INTERFACE_H

