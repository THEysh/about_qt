//
// Created by top on 2023-05-24.
//

#include "treadqt.h"


void WorkerThread::run() {
    // 在这里编写需要在线程中运行的代码
    // 执行任务...
    sleep(1); // 模拟耗时操作
    QString result = "Task completed!";
    emit resultReady(result); // 发送任务完成信号
}
