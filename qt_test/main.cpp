
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

#include <QApplication>
#include <QGraphicsSvgItem>
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QSvgRenderer>
#include <QWheelEvent>
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


class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QGraphicsScene* scene, QWidget* parent = nullptr)
            : QGraphicsView(scene, parent)
    {
    }

protected:
    void wheelEvent(QWheelEvent* event) override
    {
        double scaleFactor = 1.15;
        if (event->delta() > 0) {
            // 放大
            scale(scaleFactor, scaleFactor);
        } else {
            // 缩小
            scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        }
    }
};


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene; //创建场景

    QGraphicsSvgItem* svgItem = new QGraphicsSvgItem();
    svgItem->setSharedRenderer(new QSvgRenderer(QStringLiteral(
                                                        "F:\\code\\c_code\\about_qt\\picture_viewer\\src\\ui\\images\\pic_2d\\images-solid.svg")));
    svgItem->setScale(1);  // 缩放SVG图像为原图像的50%

    scene.addItem(svgItem); //将svg条目添加到场景中

    GraphicsView view(&scene); //创建自定义视图类并在场景中查看元素

    view.setScene(&scene);
    view.setRenderHint(QPainter::Antialiasing, true); //设置为抗锯齿渲染
    view.setViewportUpdateMode(QGraphicsView::FullViewportUpdate); //设置视口更新模式
    view.setMouseTracking(true); // 启用鼠标跟踪

    QMainWindow mainWindow;
    mainWindow.setCentralWidget(&view); //使用视图作为主窗口的中央小部件
    mainWindow.show();

    return a.exec();
}
