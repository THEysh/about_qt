//
// function.cpp
//

#include "iostream"
#include "function.h"
#include <thread>
#include "mutex"
#include <random>
#include <QMetaType>
#include <QString>
void ThreadReceiver::onworkFinished(QString result) {
    cout<<result.toStdString()<<endl;
}

void ThreadReceiver::do_work_Something(){
//QObject::connect()是Qt框架中用于建立信号和槽连接的函数，其定义如下：
//bool QObject::connect(const QObject *sender, const char *signal,
//                      const QObject *receiver, const char *method,
//                      Qt::ConnectionType type = Qt::AutoConnection);

//在这种情况下，Lambda表达式本身就是“receiver”，因为它是由connect()函数直接连接到信号上的槽函数。
//对于一些简单的场景，我们可以使用Lambda表达式来代替普通的槽函数，并且不需要创建一个专门的接收对象，这样可以使代码更加简洁。当然，在复杂的场景下，可能需要定义一个专门的接收对象来处理信号和槽之间的连接关系。
    auto *t = new QThread;
    QObject::connect(t, &QThread::started,[this]() {
        std::cout << "sleep start" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //睡眠x毫秒
        std::cout << "sleep end" << std::endl;
        QString result = "work is done";
        emit this->signal_1( result);
    });
    t->start();

//    这种写法会造成界面卡顿
//    std::thread t([](){
//        std::cout << "sleep start" << std::endl;
//        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
//        std::cout << "sleep end" << std::endl;
//    });
//    t.join();
}








