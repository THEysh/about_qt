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

class Ball_class : public Object_category{
public:
    Ball_class();
};

// --------------------------------------------------------------------

class Ball : public Ball_class{
public:
    QRectF ball_rect;
    QPointF ball_cent;
    Velocity2D ball_v;
    double rad;
    QColor color;
    double m;
    QQueue<QPointF> trace_queue;
    int len_trace_queue = 40;

    Ball(QRectF rect, Velocity2D ball_v);

    void coordinate_change_df(QPointF &dpf);

    void set_v(Velocity2D &v);

private:
    static QColor generateRandomColor();

    void trace_push(QPointF &p);
};

// --------------------------------------------------------------------

class Polygon_boundary_class : public Object_category{

};

class Rect_boundary : public Polygon_boundary_class {
public:
    QPolygonF polygon;
    explicit Rect_boundary(const QVector<QPointF*>& coordinates);
    ~Rect_boundary() override;
};

#endif //BOLL_OBJECT_CATEGORY_H
