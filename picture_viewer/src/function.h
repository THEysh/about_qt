//
// some_function.h
//
#ifndef QT_EXAM_FUNCTION_H
#define QT_EXAM_FUNCTION_H
#include <QApplication>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include "iostream"
#include <QDebug>
#include <QObject>
#include <QThread>
#include <QSignalMapper>
#include <QString>
#include <QPushButton>
#include "ui/ui_file/Qtree_ui.h"
#include "Qurl"
#include <QResource>
#include <QPixmap>
#include "QDir"
#include <QTimer>
#include <QDateTime>
#include <QPainter>
#include <QDesktopServices>
#include <QSplitter>


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
        photo_g = ui_f.graphicsView;  //这样是实现，ui_f.photo_label 和 这个类中的photo_label共用一个地址
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
    //设置窗口之间的拖动
    void connect_all(){

        qtree_widget->my_photo = photo_g;
        //这个指针永远指向active_item，photo_actived_rootNode指针指向activate_item所指向的地址
        photo_g->photo_actived_rootNode = &(qtree_widget->active_item);
    }
    void Splitter(){
        // 将树形控件和 photo_g 作为子控件添加到 QSplitter 中
        QSplitter* splitter = new QSplitter(Qt::Horizontal, Win);
        splitter->addWidget(qtree_widget);
        splitter->addWidget(photo_g);

        Win->setCentralWidget(splitter);
        // 使左侧 QWidget 的大小占比为 1，右侧 QWidget 的大小占比为 3
        splitter->setStretchFactor(1, 3);

    }
};


#endif //QT_EXAM_FUNCTION_H