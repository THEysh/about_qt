//
// Created by top on 2023-05-24.
//

#include "Pic_Thread.h"
#include "Item_Interface.h"

Gif_WorkerThread::Gif_WorkerThread() {

}

void Gif_WorkerThread::run() {}

Item_Interface_Queue::Item_Interface_Queue(int load_max):
    max_len(load_max){

}

void Item_Interface_Queue::enqueue(const std::shared_ptr<Item_Interface>& data) {
    if (item_data.size() < max_len) {
        item_data.enqueue(data);
    } else{
        item_data.dequeue();
        item_data.enqueue(data);
    }
}

bool Item_Interface_Queue::empty() const {
    return item_data.isEmpty();
}

size_t Item_Interface_Queue::size() const {
    return item_data.size();
}

void Item_Interface_Queue::show_all(){
    if (item_data.isEmpty()){
        qDebug()<<"is empty";
        return;
    }
    for (const std::shared_ptr<Item_Interface>& i : item_data){
        qDebug()<<i.get()<<",";
    }
    qDebug()<<"----------------------------------";
}

std::shared_ptr<Item_Interface> Item_Interface_Queue::at(int idx){
    if (idx>item_data.size()){
        return item_data.back();
    } else{
        return item_data.at(idx);
    }
}