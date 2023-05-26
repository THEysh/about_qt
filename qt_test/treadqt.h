#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H
#include <QDebug>
#include <QMutex>
#include <QThreadPool>
#include <QRunnable>
#include <QThread>
#include "QObject"


class WorkerThread : public QThread {
Q_OBJECT
public:
    void run();
    void forrun(int a);
signals:
    void resultReady(const QString &result);
};



class C_CustomTask :  public QObject,public QRunnable {
Q_OBJECT //要继承2个才能找到宏
public:
    int id_ = 0;

    explicit C_CustomTask(int i) :id_(i){}
    void run() override {}
};

class Task1 : public C_CustomTask {
Q_OBJECT
public:
    QMutex *mutex;
    explicit Task1(int id,QMutex *mutex): C_CustomTask(id), mutex(mutex) {}
    void run() override {
        mutex->lock();
        qInfo() << "Task " << id_ << " started!";
        for (int i = 3000; i > 0; i--) {

            qDebug() << "Task " << id_ << ": " << i;

        }
        qInfo() << "Task " << id_ << " finished!";
        mutex->unlock();
    }
};

class Task2 : public C_CustomTask {
Q_OBJECT
public:
    QMutex &mutex;
    explicit Task2(int id,QMutex &mutex): C_CustomTask(id), mutex(mutex) {}
    void run() override {
        mutex.lock();
        qInfo() << "Task " << id_ << " started!";
        for (int i = 2000; i > 0; i--) {

            qDebug() << "Task " << id_ << ": " << i;

        }
        mutex.unlock();
        qInfo() << "Task " << id_ << " finished!";
    }
};
#endif // WORKERTHREAD_H
