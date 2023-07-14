//
// Created by top on 2023-07-14.
//

#ifndef BOLL_OBJECT_CATEGORY_H
#define BOLL_OBJECT_CATEGORY_H
#include <QObject>
#include <QRectF>
#include <QQueue>
#include "Collision.h"

class Object_category : public QObject {

};

// --------------------------------------------------------------------

class ball: public QObject{
public:
    QRectF ball_rect;
    QPointF ball_cent;
    Velocity2D ball_v;
    double rad;
    QColor color;
    double m;
    QQueue<QPointF> trace_queue;
    int len_trace_queue = 10;
    ball(const QRectF rect, Velocity2D ball_v):
            ball_rect(rect),
            rad(rect.width()/2),
            m(rect.width()/2),
            ball_v(std::move(ball_v)),
            color(generateRandomColor()){
        ball_cent = rect.center();
    }

    void coordinate_change_df(QPointF &dpf){
        ball_rect.translate(dpf);
        ball_cent = ball_rect.center();
        trace_push(ball_cent);
    }

    void set_v(Velocity2D &v){
        ball_v = v;
    }

private:
    static QColor generateRandomColor()
    {
        int red = qrand() % 256;
        int green = qrand() % 256;
        int blue = qrand() % 256;
        return QColor::fromRgb(red, green, blue);
    }

    void trace_push(QPointF &p){
        if (trace_queue.size() == len_trace_queue){
            trace_queue.dequeue();
            trace_queue.enqueue(p);
        } else{
            trace_queue.enqueue(p);
        }
    }
};

// --------------------------------------------------------------------
class Rect_boundary : public QObject {
public:
    QVector<QPointF*> coordinates;
    explicit Rect_boundary(QVector<QPointF*> coordinates) : coordinates(std::move(coordinates)) {
    }
};

#endif //BOLL_OBJECT_CATEGORY_H
