#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWheelEvent>
#include "QtMath"
class MyGraphicsView : public QGraphicsView
{
public:
    MyGraphicsView(QGraphicsScene* scene) : QGraphicsView(scene) {}

protected:
    void wheelEvent(QWheelEvent* event) override
    {
        QPoint mousePos = mapFromGlobal(QCursor::pos()); // 获取鼠标在视图中的坐标
        QPointF scenePos = mapToScene(mousePos); // 获取鼠标在场景中的坐标

        setTransformationAnchor(QGraphicsView::AnchorUnderMouse); // 以鼠标位置为中心缩放
        qreal scaleFactor = qPow(qreal(2), event->delta() / 240.0); // 计算缩放比例
        scale(scaleFactor, scaleFactor); // 对视图进行缩放操作

        QPointF newScenePos = mapToScene(mousePos); // 获取缩放后鼠标在场景中的坐标
        QPointF delta = scenePos - newScenePos; // 计算缩放后场景偏移量
        translate(delta.x(), delta.y()); // 对视图进行偏移操作
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pix("C:\\Users\\Administrator\\Desktop\\新建文件夹\\image.jpg","bmp"); // 加载图片
    QGraphicsScene scene;
    scene.addPixmap(pix); // 在场景中添加图片

    MyGraphicsView view(&scene); // 创建视图并设置场景
    view.setRenderHint(QPainter::Antialiasing); // 开启抗锯齿
    view.setViewportUpdateMode(QGraphicsView::FullViewportUpdate); // 设置视图刷新模式

    view.show(); // 显示视图

    return a.exec();
}
