//
// Created by top on 2023-05-25.
//

#ifndef QT_TEST_ITEM_INTERFACE_QUEUE_H
#define QT_TEST_ITEM_INTERFACE_QUEUE_H
#include <QQueue>
#include <memory>
#include "QDebug"
#include "QObject"

class Item_Interface_Queue:public QObject {
    Q_OBJECT
public:

    Item_Interface_Queue(){
    };
public:
    QQueue<int> m_data; // 存储数据的队列
    // 入队函数
    void enqueue(int data) {
        if (m_data.size() < 5) {
            m_data.enqueue(data);
        } else{
            m_data.enqueue(data);
            m_data.dequeue();
        }
    }
    // 判断队列是否为空
    bool empty() const {
        return m_data.isEmpty();
    }
    // 获取队列中元素数量
    size_t size() const {
        return m_data.size();
    }

    void show_all(){
        if (m_data.isEmpty()){
            qDebug()<<"is empty";
            return;
        }
        for (auto i : m_data){
            qDebug()<<i<<",";
        }
        qDebug()<<"----------------------------------";
    }

};


#endif //QT_TEST_ITEM_INTERFACE_QUEUE_H
