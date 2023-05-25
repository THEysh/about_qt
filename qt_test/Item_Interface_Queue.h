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

    Item_Interface_Queue(int load_len=5){
        max_len = load_len;
    };
private:
    int max_len;
public:
    QQueue<int> m_data; // 存储数据的队列
    // 入队函数
    void enqueue(int data) {
        if (m_data.size() < max_len) {
            m_data.enqueue(data);
        } else{
            m_data.enqueue(data);
            m_data.dequeue();
        }
        qDebug()<<"m_data.size()"<<m_data.size();
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

    int at(int idx){
        if (idx>m_data.size()){
            return m_data.back();
        } else{
            return m_data.at(idx);
        }
    }

};


#endif //QT_TEST_ITEM_INTERFACE_QUEUE_H
