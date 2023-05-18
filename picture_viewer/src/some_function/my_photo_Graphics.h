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
// 当两个类相互引用对方的成员变量或函数时，可以使用前向声明和成员函数定义分离等方法来解决：
//例如，类 A 与类 B 相互引用对方的成员变量或函数时，可以在类的头文件中使用前向声明来解决依赖关系，将另一个类的定义放在头文件的最后
// 在实现的.cpp文件中，必须包含2个.h(#include "My_Photo_Graphics.h",#include "Item_Interface.h")的头文件

class Item_Interface;// （前向声明）

class My_Photo_Graphics : public QGraphicsView {
Q_OBJECT
public:
    QTreeWidgetItem **photo_actived_rootNode = nullptr; //这个指针永远指向active_item
    QCheckBox *that_checkBox= nullptr;

    explicit My_Photo_Graphics(QWidget *parent = nullptr);
    Item_Interface *interface_photo_graphics = nullptr; //有前向声明不能创建对象，可以创建指针，要到对应的cpp文件引用头文件实现
    QGraphicsScene *scene = new QGraphicsScene();
    void graphics_load_image(const QString &path, const QStringList &type_img);

protected:

    QPixmap *or_background = new QPixmap(":ui/images/pic_b/wallhaven-nkqrgd.png"); // 设置背景的副本
    QPixmap *background = new QPixmap(":ui/images/pic_b/wallhaven-nkqrgd.png"); // 设置背景
    int mouse_x = 0;
    int mouse_y = 0;

    void click_element();
    void show_photo();
    std::pair<int, int> get_width_height();
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

