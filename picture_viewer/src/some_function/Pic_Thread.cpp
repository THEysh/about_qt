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
    all_z_val.resize(load_max);
    std::fill(all_z_val.begin(), all_z_val.end(), 0);}

void Item_Interface_Queue::enqueue(const std::shared_ptr<Item_Interface>& data) {
    if (item_data.size() < max_len) {
        item_data.enqueue(data);
    } else{
        // 使用临时智能指针变量保存队首元素,用于删除，离开作用域，临时智能指针变量销毁，同时会自动释放管理的对象
        std::shared_ptr<Item_Interface> temp_ptr = item_data.dequeue();
        item_data.enqueue(data);
    }
    // 新加入的z轴值为它的之前的最大值加1
    int temp_z = max_z()+1;
    all_z_val.push_back(temp_z);
    data->set_z_val(temp_z);
    qDebug()<<"size,Item_Interface_Queue::enqueue:"<<item_data.size();
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

int Item_Interface_Queue::max_z(){
    // 计算最大z-val
    // 复制 queue 到 vector
    // 找到最大值
    int maxValue = *std::max_element(all_z_val.begin(), all_z_val.end());
    for (int i=0;i<all_z_val.size();i++){
        qDebug() << "all_z_val:" << all_z_val.at(i);
    }
    qDebug() << "The max value in the queue is:" << maxValue;
    return maxValue;
}
