//
// Created by top on 2023-05-24.
//

#ifndef PICTURE_VIEWER_PIC_THREAD_H
#define PICTURE_VIEWER_PIC_THREAD_H
#include <QThread>
#include "Item_Interface.h"
#include <QGraphicsView>
#include <QMutex>
#include "memory"
#include "qdebug.h"
class Gif_WorkerThread : public QThread {
Q_OBJECT

public:
    Gif_WorkerThread();
    void run();

private:
    QMutex mutex;
signals:
    void resultReady(const QString &result); //信号
};

class Gif_Rect_Sig : public QObject
{
Q_OBJECT
public:
    Gif_Rect_Sig(const QRect &rect){
        gif_rect = rect;
    }
signals:
    void sizeChanged(const QRect &rect);

public slots:
    void checkRect(const QRect &rect)
    {
        if ((rect.size().width() != gif_rect.size().width())||(rect.size().height() != gif_rect.size().height())) {
            gif_rect = rect;
            emit sizeChanged(rect);
        }
    }
public:
    void set_gif_rect(const QRect &rect){
        gif_rect = rect;
    }
    QRect get_gif_rect(){
        return gif_rect;
}
private:
    QRect gif_rect;
};


#endif //PICTURE_VIEWER_PIC_THREAD_H
