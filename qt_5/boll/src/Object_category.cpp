//
// Created by top on 2023-07-14.
//

#include "Object_category.h"
Ball_class :: Ball_class(){};

Ball :: Ball(const QRectF rect, Velocity2D ball_v):
        ball_rect(rect),
        rad(rect.width()/2),
        m(rect.width()/2),
        ball_v(std::move(ball_v)),
        color(generateRandomColor()){
    ball_cent = rect.center();
}

void Ball :: coordinate_change_df(QPointF &dpf){
    ball_rect.translate(dpf);
    ball_cent = ball_rect.center();
    trace_push(ball_cent);
}

void Ball :: set_v(Velocity2D &v){
    ball_v = v;
}

QColor Ball :: generateRandomColor()
{
    int red = qrand() % 256;
    int green = qrand() % 256;
    int blue = qrand() % 256;
    return QColor::fromRgb(red, green, blue);
}

void Ball :: trace_push(QPointF &p){
    if (trace_queue.size() == len_trace_queue){
        trace_queue.dequeue();
        trace_queue.enqueue(p);
    } else{
        trace_queue.enqueue(p);
    }
}

Rect_boundary :: Rect_boundary(const QVector<QPointF*>& coordinates) {
    for (auto c : coordinates){
        polygon<<*c;
    }
}

Rect_boundary::~Rect_boundary() {
    for (auto point : polygon) {
        delete &point;
    }
}