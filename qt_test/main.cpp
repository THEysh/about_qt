#include <QCoreApplication>
#include <QDebug>
#include <QMutex>
#include <QThreadPool>
#include <QRunnable>
#include "treadqt.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 创建线程池
    QThreadPool* pool = QThreadPool::globalInstance();

    // 设置线程池最大线程数
    pool->setMaxThreadCount(2);
    QMutex mutex;
    // 创建2个自定义任务并添加到线程池中
    auto task1 = new Task1(1,&mutex);
    auto task2 = new Task2(2,mutex);
    pool->start(task1);
    pool->start(task2);

    return a.exec();
}
