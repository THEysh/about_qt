
#include <iostream>
#include <vector>
#include <QString>
#include <QStringList>
#include <QFileInfo>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QApplication>
#include "qdebug.h"
#include "Item_Interface.h"

class Animal {
public:
    virtual void move() { std::cout << "Animal moving\n"; }
};

class Car:Animal {
public:
    virtual void move() override{std::cout << "cat moving\n";}
    virtual void start() { std::cout << "Car starting\n"; }
    virtual void stop() { std::cout << "Car stopping\n"; }
};
class Blue_Car:Car{
public:
    void move() override{std::cout << "Blue_cat moving\n";}
    void start() override{ std::cout << "Blue_Car starting\n"; }
    void stop() override{ std::cout << "Blue_Car stopping\n"; }
};

class Zoo {
public:
    virtual void moveAll() = 0;
    virtual void startCar() = 0;
    virtual void stopCar() = 0;
};
class ZooImpl : public Zoo {
public:
    std::vector<Animal*> animals;
    std::vector<Car*> cars;
    Blue_Car bulecar;

    virtual void moveAll() {
        for (auto animal : animals) {
            animal->move();
        }
        for (auto car : cars) {
            car->move();
        }
    }

    virtual void startCar() {
        bulecar.start();
    }

    virtual void stopCar() {
        bulecar.stop();
    }
};
int main(int argc, char* argv[]) {
    QApplication app(argc, argv); // 创建 QApplication 对象
    ZooImpl zoo;
    zoo.cars.push_back(new Car());
    zoo.animals.push_back(new Animal());
    zoo.bulecar = Blue_Car();
    zoo.moveAll();
    zoo.startCar();
    zoo.stopCar();
    QString path = "asd.SVg";
    QFileInfo fileInfo(path);
    QStringList imageTypes = {"svg","jpg","png"};
    qDebug()<<((fileInfo.suffix().compare("svg", Qt::CaseInsensitive))==0);
    path = "C:\\Users\\Administrator\\Desktop\\新建文件夹\\Temp\\1684165169655.jpg";
    QPixmap temp_pixmap(path, imageTypes.join(",").toUtf8().constData());
    Item_Interface *image_items = nullptr;
    if (!temp_pixmap.isNull()) {
        qDebug() << "Image loaded successfully.";
        auto* item_pixmap = new QGraphicsPixmapItem(temp_pixmap);
        image_items = new C_QPixmapItem(item_pixmap);
        qDebug()<<image_items<<"avc";
        }

    return app.exec(); // 运行 QT 应用程序事件循环
}