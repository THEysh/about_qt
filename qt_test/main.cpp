#include <QGraphicsView>
#include <QWheelEvent>
#include <QApplication>
#include <QMainWindow>
#include "QGraphicsRectItem"
class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QWidget *parent = nullptr) : QGraphicsView(parent) {
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    }

protected:
    void wheelEvent(QWheelEvent *event) override
    {
        // 获取当前的缩放比例
        qreal scaleFactor = transform().m11();

        // 根据滚轮的滚动方向调整缩放比例
        if (event->delta() > 0)
            scaleFactor *= 1.1;
        else
            scaleFactor /= 1.1;

        // 设置新的缩放比例
        setTransform(QTransform::fromScale(scaleFactor, scaleFactor));
        // 停止事件传播
        event->accept();
    }
};
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 创建场景
    QGraphicsScene scene;
    scene.setSceneRect(-200, -200, 400, 400);
    scene.addLine(-200, 0, 200, 0, QPen(Qt::red));
    scene.addLine(0, -200, 0, 200, QPen(Qt::red));

    // 创建视图并设置场景
    GraphicsView view;
    view.setScene(&scene);

    // 显示视图
    view.show();

    return a.exec();}
