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
public:
    void create_objects(QRectF rect, Velocity2D ball_v);  // 纯虚函数，用于创建子类对象
    template<typename T1>
    T1 get_objects(){
        return T1();
    }
    template<typename T2>
    T2& operator[](int index) {
        return T2();
    }
    virtual int size(){}
private:
    Object_category* polygon_object = nullptr;
};

class Ball_class : public Object_category{
public:
    ~Ball_class() override;
    Ball_class();
    Ball_class(QRectF rect, Velocity2D ball_v);
    explicit Ball_class(Ball* ball);
    explicit Ball_class(QVector<Ball*>& some_balls);
    void add_ball(QRectF rect, Velocity2D ball_v);
    void add_ball(Ball *ball);
    QVector<Ball*>& get_objects();
    Ball& operator[](int index);
    int size() override;
private:
    QVector<Ball*> balls;
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

    void coordinate_change_df(const QPointF &dpf);

    void set_v(Velocity2D &v);

private:
    static QColor generateRandomColor();

    void trace_push(QPointF &p);
};

// --------------------------------------------------------------------

class Polygon_boundary_class : public Object_category{
public:
    ~Polygon_boundary_class() override;
    Polygon_boundary_class();
    explicit Polygon_boundary_class(Rect_boundary* rect_bound);
    explicit Polygon_boundary_class(QVector<Rect_boundary*>& some_rect_bounds);
    void add_rect_polygon(Rect_boundary* rect_bound);
    void add_rect_polygon(const QVector<QPointF*>& coordinates);
    QVector<Rect_boundary*>& get_objects();
    Rect_boundary& operator[](int index);
    int size() override;
private:
    QVector<Rect_boundary *> rect_polygons;
};

// --------------------------------------------------------------------

class Rect_boundary : public Polygon_boundary_class {
public:
    ~Rect_boundary() override;
    explicit Rect_boundary(const QVector<QPointF*>& coordinates);
    QPolygonF& get_polygon();
    QPointF& operator[](int index);
    int size() override;
private:
    QPolygonF polygon;
};

#endif //BOLL_OBJECT_CATEGORY_H
