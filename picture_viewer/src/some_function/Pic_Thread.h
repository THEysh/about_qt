//
// Created by top on 2023-05-24.
//

#ifndef PICTURE_VIEWER_PIC_THREAD_H
#define PICTURE_VIEWER_PIC_THREAD_H
#include <QThread>
#include "Item_Interface.h"
#include <QGraphicsView>
#include <QMutex>
#include <QQueue>
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


class Item_Interface_Queue:public QObject {
Q_OBJECT
public:
    Item_Interface_Queue(){};
public:
    QQueue<Item_Interface *> item_data; // 存储数据的队列
    // 入队函数
    void enqueue(Item_Interface *data) {
        if (item_data.size() < 5) {
            item_data.enqueue(data);
        } else{
            Item_Interface *old_data = item_data.head();
            item_data.dequeue();
            delete old_data;
            item_data.enqueue(data);
        }
    }
    // 判断队列是否为空
    bool empty() const {
        return item_data.isEmpty();
    }
    // 获取队列中元素数量
    size_t size() const {
        return item_data.size();
    }

    void show_all(){
        if (item_data.isEmpty()){
            qDebug()<<"is empty";
            return;
        }
        for (auto i : item_data){
            qDebug()<<i<<",";
        }
        qDebug()<<"----------------------------------";
    }

    Item_Interface* at(int idx){
        if (idx>item_data.size()){
            return item_data.back();
        } else{
            return item_data.at(idx);
        }
    }
};

#endif //PICTURE_VIEWER_PIC_THREAD_H
