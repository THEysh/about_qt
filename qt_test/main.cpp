#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include <QWheelEvent>

class MyGraphicsView : public QGraphicsView {
public:
    explicit MyGraphicsView(QWidget *parent = nullptr) : QGraphicsView(parent) {
        // 将场景设置为滚动条跟随内容变化而自动调整大小
//        setResizeAnchor(QGraphicsView::AnchorUnderMouse);
//        setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
//        setRenderHint(QPainter::Antialiasing, true);
//        setRenderHint(QPainter::TextAntialiasing, true);
    }

protected:
    // 处理鼠标滚轮事件
    void wheelEvent(QWheelEvent *event) override {
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse); // 设置变换锚点
        double scaleFactor = 1.15;
        if (event->delta() > 0) {  // 缩放
            scale(scaleFactor, scaleFactor);
        } else {  // 放大
            scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        }
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QGraphicsScene scene;  // 新建一个场景
    QGraphicsEllipseItem *ellipseItem = new QGraphicsEllipseItem(-50, -50, 100, 100);  // 创建一个圆形图元
    ellipseItem->setBrush(QBrush(Qt::green));  // 设置图元的填充颜色
    ellipseItem->setPos(50, 50);  // 设置图元位置
    scene.addItem(ellipseItem);  // 将图元添加到场景中
    MyGraphicsView view;  // 新建一个视图
    view.setScene(&scene);  // 将场景设置为视图的场景
    view.show();  // 显示视图
    return app.exec();
}
