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
#include <QDebug>
#include <QThread>
#include <QSignalMapper>
#include <QString>
using namespace  std;

class ThreadReceiver : public QObject
{
    //这个类用于多线程信号通信，do_work_Something函数绘睡眠，睡眠完成后会发送信号“work is done”
Q_OBJECT
signals:
    void signal_1(QString result);
    //定义一个信号，并定义与这个信号连接的槽函数 void onworkFinished(int result)
    // 构造这个类时，将信号连接起来
public slots:
    // 定义1个槽函数
    void onworkFinished(QString result); // onworkFinished用于判断是否完成 doSomething 函数，
    void do_work_Something();

public:
    ThreadReceiver(){
        connect(this, &ThreadReceiver::signal_1, this, &ThreadReceiver::onworkFinished);
    }
};


#endif //QT_EXAM_FUNCTION_H
