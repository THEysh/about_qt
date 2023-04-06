//
// function.cpp
//
#include "iostream"
#include "function.h"
#include <thread>
#include "mutex"
#include <QMetaType>
#include <QString>
using namespace std;

void ThreadReceiver::onworkFinished(QWidget *qw,const QString& q_ans) const {

    this->print_meg(q_ans);
    qw->setEnabled(true);

}

void ThreadReceiver::print_meg(const QString& text) const {
    this->ui_f.textBrowser->setPlainText(text);
}

void ThreadReceiver::do_work_Something(QWidget *qw, double sleep_time){
//QObject::connect()是Qt框架中用于建立信号和槽连接的函数，其定义如下：
//bool QObject::connect(const QObject *sender, const char *signal,
//                      const QObject *receiver, const char *method,
//                      Qt::ConnectionType type = Qt::AutoConnection);
//在这种情况下，Lambda表达式本身就是“receiver”，因为它是由connect()函数直接连接到信号上的槽函数。
//对于一些简单的场景，我们可以使用Lambda表达式来代替普通的槽函数，并且不需要创建一个专门的接收对象，这样可以使代码更加简洁。
//当然，在复杂的场景下，可能需要定义一个专门的接收对象来处理信号和槽之间的连接关系。
//lambda函数,[]这里填的是在lambda函数中需要用的变量，[=]表示函数外的所有变量都导入。（）填的是lambda函数的输入参数，{}是lambda函数范围

    // 定义一个lambda函数 ( -> )表示返回
    auto mylambdaFunc = [](int arg1, const QString& arg2, double sleep_time, QWidget *qw)-> std::pair<QWidget*, int>{

        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long> (sleep_time*1000))); //睡眠x毫秒
        return std::make_pair(static_cast<QWidget*>(qw), arg1*arg1);
    };
    auto *t = new QThread;
    qw->setEnabled(false);
    QObject::connect(t, &QThread::started,[=]() {
        //完成任务发出信号
        auto seed = std::chrono::system_clock::now().time_since_epoch().count(); //生成随机分布的seed
        std::mt19937 gen(seed);
        std::uniform_int_distribution<> dis(1, 100);
        int random_number = dis(gen);
        //这是在qthread开启多线程，需要一个信号机制，在多线程的内，又写一个lambda函数
        auto sig_ans = mylambdaFunc(random_number,"work done",sleep_time, qw);
        QString q_ans = QString("work done,the %1*%1 ans is %2").arg(random_number).arg(random_number*random_number);
        emit signal_1(sig_ans.first, q_ans);
    });

    this->print_meg("sleep start");
    this->print_meg(QString("sleep time: %1 s").arg(sleep_time));
    t->start();
//    这种写法会造成界面卡顿
//    std::thread t([](){
//        std::cout << "sleep start" << std::endl;
//        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
//        std::cout << "sleep end" << std::endl;
//    });
//    t.join();
}

void ThreadReceiver::do_work_decimal_to_binary(QWidget *qw, double sleep_time, long number) {

    auto mylambdaFunc = [sleep_time](long number)-> QString{
        long decimalNum = number;
        string binary;
        while (number > 0) {
            binary = to_string(number % 2) + binary;
            number /= 2;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds((long int) round(sleep_time*1000))); //睡眠500毫秒

        return QString("The decimalNum %1 to binary equivalent is:").arg(decimalNum) + QString::fromStdString(binary);
    };
    auto *t = new QThread;
    qw->setEnabled(false);
    QObject::connect(t,&QThread::started,[=](){
        auto q_ans = mylambdaFunc(number);
        emit signal_1(qw, q_ans);
    });
    this->print_meg("sleep start");
    this->print_meg(QString("sleep time: %1 s").arg(sleep_time));
    t->start();



}

void ThreadReceiver::button1_connect(QPushButton *button, double sleep_time)  {
    // 连接clicked()信号和槽函数
    QObject::connect(button, &QPushButton::clicked, this,
                     [this, test_lab = make_pair(button, sleep_time)]
                     {
                         this->do_work_Something(test_lab.first,test_lab.second);});
}

void ThreadReceiver::button2_connect(QPushButton *button, double sleep_time, long number) {
    // 连接clicked()信号和槽函数
    QObject::connect(button, &QPushButton::clicked, this,
                     [this,button,sleep_time, number]
                     {
                         this->do_work_decimal_to_binary(button,sleep_time, number);});
}





















