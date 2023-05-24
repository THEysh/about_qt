#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>

class WorkerThread : public QThread {
Q_OBJECT

public:
    void run();
    void forrun(int a);
signals:
    void resultReady(const QString &result);
};

#endif // WORKERTHREAD_H
