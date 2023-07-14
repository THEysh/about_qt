//
// Created by top on 2023-07-11.
//
#ifndef BOLL_COLLISION_H
#define BOLL_COLLISION_H
#include <cmath>
#include <utility>
#include <QColor>
#include <QObject>
#include <QRectF>
#include "QDebug"
#include <QQueue>
#include <QLineF>
#include <QTransform>
#include <QVector2D>
// 坐标系,象限如下
//   3 | 4
//  ------>
//   2 | 1

class Ball;
class Rect_boundary;

// -----------------------------------------------------------------------

class Velocity2D{
public:
    explicit Velocity2D(double angle = 0.0, double v = 0.0);
    void _set_cartesian_coordinate();

    QVector<Velocity2D> velocity_decomposing(double horizontal_angle) const;

    QVector<Velocity2D> horizontal_decomposition() const;

    Velocity2D operator+(const  Velocity2D& other) const;

    void set_v(const double new_angle, const double new_v);

    double get_v() const;

    double get_angle() const;

    QPointF get_cartesian_coordinate() const;

    void show_log() const;
private:
    double angle;
    double v;
    QPointF cartesian_pooint;
    QTransform velocity_transform;

};

// 这里是函数声明
static Velocity2D weight_composition(Velocity2D& v_x, Velocity2D& v_y);

// -----------------------------------------------------------------------

class Collision : public QObject{
public:
    double restitution = 1;
    Collision();
    void collision_calculation(double dt, Ball &ball, Rect_boundary &bound) const;

    void collision_calculation(double dt, Ball &ball, QVector2D &p1, QVector2D &p2) const;

    static std::pair<double, QPointF> ShortestDistance_point(const QVector2D& p1, const QVector2D& p2, const QVector2D& point);

};

//        v_y = v_y + g*dt; // 计算新的y方向速度
//        ball->x = ball->x + v_x*dt;
//        ball->y = ball->y + v_y*dt; // 计算新位置
//        // 计算y方向
//        if (ball->y  >= bound->height - ball->rad) {
//            // 将 y 设置为最大值
//            ball->y = bound->height - ball->rad;
//            // 计算反弹后的速度, 更新小球位置和速度
//            v_y = -restitution * v_y;
//            ball->y = ball->y + v_y * dt;
//        }
//        else if (ball->y <= 0 + ball->rad ) {
//            ball->y = ball->rad;
//            v_y = -restitution * v_y;
//            ball->y = ball->y + v_y * dt;
//        }
//        // 计算x方向
//        if (ball->x >= bound->width - ball->rad){
//            ball->x = bound->width - ball->rad;
//            // 计算反弹后的速度
//            v_x = -restitution * v_x;
//            ball->x = ball->x + v_x * dt;
//        }
//        else if(ball->x <= 0 + ball->rad){
//            ball->x = ball->rad;
//            v_x = -restitution * v_x;
//            ball->x = ball->x + v_x*dt;
//        }
//        // 更新速度
//        ball->set_velocity(v_x, v_y);


//    void collision_calculation(double dt, ball *ball_1,  ball *ball_2) {
//        double dis= distance(ball_1->x,ball_1->y,ball_2->x,ball_2->y);
//        if (dis>=(ball_1->rad+ball_2->rad)){
//            // 不碰撞, 返回
//            return;
//        }else{
//            pat.push_back({ball_1->x,ball_1->y,ball_2->x,ball_2->y});
//        }
//
//        double v_x_1, v_y_1, v_x_2, v_y_2, m1, m2;
//        auto boll_v_1 = ball_1->get_velocity();
//        v_x_1 = std::get<0>(boll_v_1);
//        v_y_1 = std::get<1>(boll_v_1);
//        auto boll_v_2 = ball_2->get_velocity();
//        v_x_2 = std::get<0>(boll_v_2);
//        v_y_2 = std::get<1>(boll_v_2);
//        m1 = ball_1->m; m2 = ball_2->m;
//
//        auto velocity = [&](double v1, double v2) -> std::pair<double, double>{
//            double new_v1,new_v2;
//            new_v1 = ((m1-m2)*v1 + 2*m2*v2)/(m1+m2);
//            new_v2 = ((m2-m1)*v2 + 2*m1*v1)/(m1+m2);
//            return std::make_pair(new_v1, new_v2);
//        };
//        auto result_x= velocity(v_x_1, v_x_2);
//        auto result_y= velocity(v_y_1, v_y_2);
//        ball_1->set_velocity(result_x.first, result_y.first);
//        ball_2->set_velocity(result_x.second, result_y.second);
//    }



#endif //BOLL_COLLISION_H
