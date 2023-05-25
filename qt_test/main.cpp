#include <QQueue>
#include <memory>
#include "QDebug"
#include "QObject"
#include "Item_Interface_Queue.h"


int main(){
    Item_Interface_Queue q1s;

    for (int i = 0; i < 10; ++i) {
        q1s.enqueue(i);
        q1s.show_all();
    }
    return 0;
}
