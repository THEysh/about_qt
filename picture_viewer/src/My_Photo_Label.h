//
// Created by top on 2023-04-14.
//

#ifndef QT_EXAM_MY_PHOTO_LABEL_H
#define QT_EXAM_MY_PHOTO_LABEL_H
#include <QLabel>
#include <QPixmap>
#include <QDateTime>
#include <QPainter>
#include <iostream>
#include <QMouseEvent>
#include "qdebug.h"
#include "Qtimer"
using namespace std;

class My_Photo_Label : public QLabel
{
Q_OBJECT
signals:

public:
    QPixmap activated_photo_pixmap = QPixmap(); // 根据尺寸变化的缩放图
    QPixmap or_activated_photo_pixmap = QPixmap(); //原始图片
    explicit My_Photo_Label(QWidget *parent = nullptr) : QLabel(parent) {}
    int pot_x = 0;
    int pot_y = 0;
private:
    int mouse_x = 0;
    int mouse_y = 0;
    QTimer* timer_mousepress = new QTimer();


public:
    void click_show_photo(){
        int w = this->geometry().width();
        int h = this->geometry().height();
        activated_photo_pixmap = or_activated_photo_pixmap.scaled(w,h,Qt::KeepAspectRatio);
        calculate_center_pos(activated_photo_pixmap);

        //如果放大过于模糊，就把他做出原始的尺寸，并更新pot位置
        _update_pixmap();
        update(); //单击更新图片
    }

protected:

    void paintEvent(QPaintEvent *event) override
    {
        QLabel::paintEvent(event); //先执行父类
        QPainter painter(this); // 在这个label上创建一个painter,在paintEvent函数中创建QPainter对象，并且在完成绘图工作后要及时销毁该对象。
        this->setPixmap(QPixmap()); //设置一个空对象

        QPoint pos(pot_x, pot_y); // 获取事件的新位置
        painter.drawPixmap(pos,activated_photo_pixmap);

    }

    pair<int,int> calculate_center_pos(QPixmap &p){
        //给一个QPixmap对象p， 计算p与this label居中的位置
        int p1 = this->geometry().width()/2;
        int p2 = p.size().width()/2;
        int p3 = this->geometry().height()/2;
        int p4 = p.size().height()/2;
        pot_x = p1-p2; pot_y = p3-p4;
        return make_pair(p1-p2,p3-p4);
    }

    void resizeEvent(QResizeEvent *event) override
    {
        QSize size = event->size(); //执行父类
        qDebug("Label size: %d x %d", size.width(), size.height());
        int w = this->geometry().width();
        int h = this->geometry().height();
        activated_photo_pixmap = or_activated_photo_pixmap.scaled(w,h,Qt::KeepAspectRatio);
        calculate_center_pos(activated_photo_pixmap);
        //如果放大过于模糊，就把他做出原始的尺寸，并更新pot位置
        _update_pixmap();
        update();
    }

    void mouseMoveEvent(QMouseEvent* event) override {
        //函数是在鼠标移动时触发的，不是鼠标按下时触发的。因此，当你按下鼠标左键并移动时，
        //mouseMoveEvent 函数将被连续调用，但在每次调用时，event->button() 会返回鼠标当前按下的按钮，并不一定是左键。
        //将 event->button() 改为 event->buttons()，并使用按位与运算符 & 来判断是否按下了左键。
        //具体来说，button() 方法返回当前鼠标按钮的状态，该状态通常用一个二进制数表示，每个比特位代表一个鼠标按钮，比如左键、右键和中键，不同的值代表不同的状态，
        //例如 0 表示没有任何鼠标按钮被按下，1 表示左键被按下，2 表示右键被按下，3 表示左右键同时被按下，以此类推。
        //而 buttons() 方法则返回全部鼠标按钮的状态，它返回的值是一个组合数，即将多个比特位进行 OR 操作得到的结果，表示所有被按下的鼠标按钮的状态。
        //因此，将 event->button() 改为 event->buttons() 的区别在于前者只能获取单个鼠标按钮的状态，而后者可以获取所有鼠标按钮的状态。
        //至于运算符 &，它通常用于对两个二进制数进行按位与操作。在这里，它可以用来判断某个特定的鼠标按钮是否被按下，例如通过以下代码获取左键是否被按下：
        // event->buttons()：返回一个表示当前鼠标按下的所有按钮的按位掩码（bitmask），其中每个位表示一个按钮
        // 获取鼠标当前位置和上次位置
        if (event->buttons() & Qt::LeftButton) {
            _photo_move(event);
        }
    }

    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton) {
            //执行这个事件表示，左键点击时记录更新鼠标的第一个位置，随后借用"event->x() - mouse_x"方法计算出pot_x的差更新移动的距离
            mouse_x = event->x();
            mouse_y = event->y();
        }
    }

    void wheelEvent(QWheelEvent *event) override{
        // 鼠标滚轮事件,numDegrees和numSteps都是为了方便而定义的整数变量，分别表示滚轮旋转的度数和步骤数。
        int numDegrees = event->delta() / 8;
        int numSteps = numDegrees / 15;
//        int origWidth = or_activated_photo_pixmap.width();
//        int origHeight = or_activated_photo_pixmap.height();
//        int a,b,c,d;
//        cout<<origWidth<<","<<origHeight<<endl;
//        cout<<pot_x<<",pot_y:"<<pot_y<<endl;
//        double CTx = 100;
//        double CTy = (double)activated_photo_pixmap.width()*CTx/activated_photo_pixmap.height();
//        a = pot_x + CTx;
//        b = pot_y + CTy;
//        c = activated_photo_pixmap.width() - 2 * CTx;
//        d = activated_photo_pixmap.height() - 2 * CTy;
//        a = (double)origWidth*CTx/activated_photo_pixmap.width();
//        b = (double)origHeight*CTy/activated_photo_pixmap.height();
//        c = (double)origWidth*c/activated_photo_pixmap.width();
//        d = (double)origHeight*d/activated_photo_pixmap.height();
//        cout<<a<<",:a<"<<b<<","<<c<<","<<d<<endl;
//        QRect rectToScale(a, b, c, d);
        //QPixmap rect_pixmap = or_activated_photo_pixmap.copy(rectToScale);

        //activated_photo_pixmap =  or_activated_photo_pixmap.scaled( this->geometry().width(),  this->geometry().height(),Qt::KeepAspectRatio);
        // calculate_center_pos(activated_photo_pixmap);
        // 如果放大过于模糊，就把他做出原始的尺寸，并更新pot位置
        // _update_pixmap();
        // update();

        //cout<<"event->x():"<<event->x()<<"event->y():"<<event->y()<<endl;
        //cout<<"w:"<<w<<"h"<<h<<endl;
        //activated_photo_pixmap = or_activated_photo_pixmap.scaled(QSize(2800, 2800), Qt::KeepAspectRatio);



    }

    void _photo_move(QMouseEvent* event){

        pot_x = pot_x + event->x() - mouse_x;
        pot_y = pot_y + event->y() - mouse_y;
        mouse_x = event->x(); mouse_y = event->y();
        update();
        event->accept();
    }

    void _update_pixmap(){
        if (or_activated_photo_pixmap.size().width() < activated_photo_pixmap.size().width() ||
            or_activated_photo_pixmap.size().height() < activated_photo_pixmap.size().height())
        {
            activated_photo_pixmap = or_activated_photo_pixmap;
            calculate_center_pos(or_activated_photo_pixmap);
        }
        else{
        }
    }

};


#endif //QT_EXAM_MY_PHOTO_LABEL_H
