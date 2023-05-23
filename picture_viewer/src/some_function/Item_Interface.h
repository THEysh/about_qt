

#ifndef ITEM_INTERFACE_H
#define ITEM_INTERFACE_H

#include <QLabel>
#include <QTimer>
#include "QObject"
#include "my_photo_Graphics.h"
#include "memory"
#include "QGraphicsProxyWidget"

// 把不同类型显示的图片抽样出来
class Item_Interface : public QObject{
Q_OBJECT
public: //公共接口
    explicit Item_Interface();
    ~Item_Interface() override;
    virtual void click_element();
    virtual void show_photo(QGraphicsView *view, QGraphicsScene *scene);
    virtual void wheelEvent(QWheelEvent *event, QGraphicsView *view);
    virtual void resizeEvent(QResizeEvent *event, QGraphicsView *view, QGraphicsScene *scene);
    virtual void phot_rotate(bool is_right, QGraphicsView *view);
protected:
    virtual void position_calculation(QGraphicsView *view);
};


class C_QPixmapItem : public Item_Interface{
Q_OBJECT
public:
    explicit C_QPixmapItem(const QString &path, const QStringList &imageTypes);
    ~C_QPixmapItem() override;
    void click_element() override;
    void show_photo(QGraphicsView *view, QGraphicsScene *scene); //传入当前的场景，更新图片大小

protected:
    void wheelEvent(QWheelEvent *event,QGraphicsView *view) ;
    void resizeEvent(QResizeEvent *event, QGraphicsView *view, QGraphicsScene *scene) override;
    void phot_rotate(bool is_right, QGraphicsView *view) override;
    void position_calculation(int w, int h, QGraphicsView *view);

private:
    QPixmap or_activated_photo_pixmap = QPixmap(); //原始图片
    std::unique_ptr<QPixmap> photo_pixmap_unique;
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
    void wheelEvent(QWheelEvent *event,QGraphicsView *view) override;
    void resizeEvent(QResizeEvent *event, QGraphicsView *view, QGraphicsScene *scene) override;
    void phot_rotate(bool is_right, QGraphicsView *view) override;
    void position_calculation(QGraphicsView *view) override;
private:
    std::unique_ptr<QSvgRenderer> svgrender_unique = nullptr;
    std::unique_ptr<QGraphicsSvgItem> graphics_svgItem_unique = nullptr;

};

class C_GifItem : public Item_Interface{
Q_OBJECT
public:
    C_GifItem(const QString &path,QGraphicsView *view,QGraphicsScene *scene);
    ~C_GifItem() override;
    void click_element() override;
    void show_photo(QGraphicsView *view, QGraphicsScene *scene); //传入当前的场景，更新图片大小
protected:
    void wheelEvent(QWheelEvent *event,QGraphicsView *view) override;
    void resizeEvent(QResizeEvent *event, QGraphicsView *view, QGraphicsScene *scene) override;
    void phot_rotate(bool is_right, QGraphicsView *view) override;
    void position_calculation(QGraphicsView *view) override;
private:
    void _connect();
    std::unique_ptr<QMovie> au_movie;
    std::unique_ptr<QPixmap> gif_pixmap;
    std::unique_ptr<QGraphicsPixmapItem> graphics_gifItem_unique;
    QTimer timer;
};
#endif // ITEM_INTERFACE_H

