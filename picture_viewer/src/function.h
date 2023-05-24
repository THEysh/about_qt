//
// some_function.h
//
#ifndef QT_EXAM_FUNCTION_H
#define QT_EXAM_FUNCTION_H


#include <QWidget>
#include <QMainWindow>
#include <QSplitter>
#include "ui/ui_file/Qtree_ui.h"

using namespace  std;

class Inherit_UI : public QWidget{
Q_OBJECT
signals:

public slots:
public:
    Inherit_UI(Ui_Qtree_Class_UI &ui_f, QMainWindow *Win){
        this->Win = Win;
        ui_f.setupUi(Win);
        this->ui_f = ui_f;
        photo_g = ui_f.graphicsView;//这样是实现，ui_f.photo_label 和 这个类中的photo_label共用一个地址
        qtree_widget = ui_f.treeWidget_1;

        this->connect_all();
        this->Splitter();
    }
private:
    QMainWindow *Win;
    Ui_Qtree_Class_UI ui_f;
    My_Qtreewidget *qtree_widget = nullptr;
    My_Photo_Graphics *photo_g = nullptr;
private:
    void connect_all(){
        // 让两个对象连接起来
        qtree_widget->my_photo = photo_g;
        // photo_g->photo_in_treewidget = qtree_widget;


        Win->setWindowTitle("image");
        QIcon icon(":ui/images/pic_2d/images-solid.svg");
        Win->setWindowIcon(icon);
    }
    //设置窗口之间的拖动
    void Splitter(){
        // 将树形控件和 photo_g 作为子控件添加到 QSplitter 中
        QSplitter* splitter = new QSplitter(Qt::Horizontal);
        splitter->addWidget(ui_f.verticalWidget);
        splitter->addWidget(photo_g);
        //设置分隔条的宽度
        splitter->setHandleWidth(1);
        // 使左侧 QWidget 的大小占比为 1，右侧 QWidget 的大小占比为 3
        splitter->setStretchFactor(1, 3);
        // 添加
        ui_f.horizontalLayout_1->addWidget(splitter);

    }
};


#endif //QT_EXAM_FUNCTION_H