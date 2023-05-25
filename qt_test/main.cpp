#include <QQueue>
#include <memory>
#include <QPixmap>
#include <QLabel>
#include <QApplication>
#include "QDebug"
#include "QObject"
#include "Item_Interface_Queue.h"
#include "QUuid"

int main(int argc, char *argv[]){
    Item_Interface_Queue q1s(3);

    for (int i = 0; i < 10; ++i) {
        q1s.enqueue(i);
        q1s.show_all();
    }
    qDebug()<<q1s.at(80);

    QUuid uuid = QUuid::createUuid();

    qDebug() << "随机字符串：" << uuid;
    QApplication app(argc, argv);

    return app.exec();
    return 0;
}
