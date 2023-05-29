#include <QCoreApplication>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include <QDebug>

// 定义需要异步调用的函数
int fun(int index)
{
    int result = 0;
    // 计算一段时间，模拟耗时操作
    for (int i = 0; i < 10000000; i++)
        result += i;

    qDebug() << QString("fun(): %1 completed.").arg(index);

    return result;
}

int fun2(int index)
{
    int result = 0;
    // 计算一段时间，模拟耗时操作
    for (int i = 0; i < 100000000; i++)
        result += i;

    qDebug() << QString("fun2(): %1 completed.").arg(index);

    return result;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 定义 QFuture 和 QFutureWatcher 对象
    QFuture<int> future, future2;
    //QFutureWatcher<int> watcher;

    // 连接信号槽，监控计算完成信号
//    QObject::connect(&watcher, &QFutureWatcher<int>::finished, [&]() {
//        //qDebug() << "The previous calculation has completed.";
//    });

    // 循环多次调用 fun()
    for (int i = 0; i < 5; i++) {

        // 如果上一次计算尚未完成，取消上一次计算
        if (future.isRunning()) {
            future.cancel();
            qDebug() << "The previous calculation has been cancelled.";
        }
        // 等待 future2 计算完成
        if (future2.isRunning()) {
            qDebug() << "Waiting for the previous calculation to complete...";
            future2.waitForFinished();
            qDebug() << "The previous calculation has completed.";
        }
        if (i==2){
            future2 = QtConcurrent::run(fun2, i);
        }
        // 开启新的一次函数计算
        future = QtConcurrent::run(fun, i);
        // 监控计算结果
        //watcher.setFuture(future);
    }

    return a.exec();
}

