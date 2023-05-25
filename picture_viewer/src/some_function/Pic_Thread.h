//
// Created by top on 2023-05-24.
//

#ifndef PICTURE_VIEWER_PIC_THREAD_H
#define PICTURE_VIEWER_PIC_THREAD_H
#include <QThread>
#include <QGraphicsView>
#include <QMutex>
#include <QQueue>
#include "memory"
#include "qdebug.h"

class  Item_Interface;

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

class Item_Interface_Queue:public QObject {
Q_OBJECT
public:
    explicit Item_Interface_Queue(int max_len=2);
private:
    int max_len;
public:
    int max_z_val=0; //永远保存最大的y值
    QQueue< std::shared_ptr<Item_Interface> > item_data; // 存储数据的队列
    // 入队函数
    void enqueue(const std::shared_ptr<Item_Interface>& data);
    // 判断队列是否为空
    bool empty() const;
    // 获取队列中元素数量
    size_t size() const;
    void show_all();
    std::shared_ptr<Item_Interface> at(int idx);
    int max_z();
};

#endif //PICTURE_VIEWER_PIC_THREAD_H
