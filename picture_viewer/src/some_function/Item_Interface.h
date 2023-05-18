

#ifndef ITEM_INTERFACE_H
#define ITEM_INTERFACE_H
#include "QObject"
#include "C_QPixmapItem.h"
#include "My_Photo_Graphics.h"

// 这个地方不能继承My_Photo_Graphics 因为：
/*在进行初始化时，需要首先创建 My_Photo_Graphics 的实例，然后将该实例传递给 Item_Interface 的构造函数。
因此，在创建 My_Photo_Graphics 对象时，不能够通过将指向 Item_Interface 对象的指针作为参数传递来初始化接口。
正确的做法是在 My_Photo_Graphics 的构造函数中，先创建 interface_photo_graphics 对象，然后将该对象的指针传递给 Item_Interface 的构造函数。*/
class Item_Interface : public QObject{
Q_OBJECT
public:
    explicit Item_Interface(My_Photo_Graphics *parent = nullptr);
    void interface_load_image(const QString &path, const QStringList &type_img);
    QGraphicsScene *interface_scene = nullptr;
protected:
    // 重写父类的虚函数
    virtual void click_element();
    virtual void show_photo(void (*my_fun_Pointer)());

    const char *image_type_list; // 获取image的种类

private:

};


#endif // ITEM_INTERFACE_H




//
//class C_SvgItem : public Item_interface{
//public:
//    QSvgRenderer activated_svg;
//    C_SvgItem(Item_interface *parent = nullptr);
//protected:
//
//private:
//    void Svg_show();
//    void resizeEvent(QResizeEvent *event);
//    void wheelEvent(QWheelEvent *event);
//};

