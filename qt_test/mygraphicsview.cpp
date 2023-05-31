#include "mygraphicsview.h"
#include "QMouseEvent"
#include "QtMath"
#include "QGraphicsRectItem"
#include "QScrollBar"
MyGraphicsView::MyGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    // 设置背景色为白色
    setBackgroundBrush(Qt::white);

    // 创建一个矩形物体，添加到场景中
    QGraphicsRectItem *rectItem = new QGraphicsRectItem(0, 0, 100, 100);
    scene()->addItem(rectItem);

    // 将视图的中心点设置为场景中矩形物体的中心点
    setSceneRect(rectItem->boundingRect());
    setAlignment(Qt::AlignCenter);
}

void MyGraphicsView::wheelEvent(QWheelEvent *event)
{
    // 获取当前鼠标位置
    QPointF mousePos = this->mapToScene(event->pos());

    // 计算缩放比例
    qreal scaleFactor = qPow(2.0, event->delta() / 240.0);
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();

    // 缩放视图
    if (factor < 0.07 || factor > 100) return;
    scale(scaleFactor, scaleFactor);

    // 调整视图位置，使被缩放的物体以鼠标位置为中心缩放
    QPointF newMousePos = this->mapFromScene(mousePos);
    QPointF deltaMousePos = newMousePos - event->pos();
    horizontalScrollBar()->setValue(horizontalScrollBar()->value() + deltaMousePos.x());
    verticalScrollBar()->setValue(verticalScrollBar()->value() + deltaMousePos.y());
}
