#include <QQueue>
#include <memory>
#include "QDebug"
#include "QObject"
#include "Item_Interface_Queue.h"


int main(){
    Item_Interface_Queue q1s(3);

    for (int i = 0; i < 10; ++i) {
        q1s.enqueue(i);
        q1s.show_all();
    }

    qDebug()<<q1s.at(80);
    return 0;
}
