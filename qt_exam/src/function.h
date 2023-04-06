//
// function.h
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
#include "myfirst.h"

using namespace  std;

class ThreadReceiver : public QObject
{
    /**
     * /这个类用于多线程信号通信，do_work_Something函数绘睡眠，睡眠完成后会发送信号“work is done”,主函数可以参考如下：
     */
Q_OBJECT
public:
    Ui_MainWindow ui_f{};
signals:
    void signal_1(QWidget *qw, QString q_ans);
    //定义一个信号，并定义与这个信号连接的槽函数 void onworkFinished
    // 构造这个类时，将信号连接起来,一般情况函数onworkFinished，和signal_1的传参类型是一致的
    // 因为signal_1发出一个A类型的信号，onworkFinished也应该要接收一个A类型的信号表示任务完成
public slots:
    // 定义槽函数
    void onworkFinished(QWidget *qw, const QString& q_ans) const; // onworkFinished用于判断是否完成 doSomething 函数，
    void do_work_Something(QWidget *qw, double sleep_time); //多线程睡眠，计算随机数的一个乘法
    void do_work_decimal_to_binary(QWidget *qw,double sleep_time,long number); //多线程睡眠，计算十进制转二进制
public:
    ThreadReceiver(Ui_MainWindow ui_f){
        // 创建信号的连接
        this->ui_f = ui_f;
        QObject::connect(this, &ThreadReceiver::signal_1, this, &ThreadReceiver::onworkFinished);

    }

    void button1_connect(QPushButton *button, double sleep_time);

    void button2_connect(QPushButton *button, double sleep_time, long number);

    void print_meg(const QString& text) const;

};


#endif //QT_EXAM_FUNCTION_H
