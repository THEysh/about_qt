//
// Created by top on 2023-07-11.
//

#ifndef BOLL_COLLISION_H
#define BOLL_COLLISION_H
#include <cmath>
#include <utility>
#include <QColor>
#include <QObject>
#include "QDebug"

class ball: public QObject{
public:
    float x; float y; float rad; QColor color; float m;
    ball(float x, float y, float rad):
            x(x),
            y(y),
            rad(rad),
            m(rad),
            color(generateRandomColor()){}

    std::tuple<float, float>  get_velocity() {
        return std::make_tuple(v_x, v_y);
    }
    void set_velocity(float new_v_x, float new_v_y){
           v_y = new_v_y; v_x = new_v_x;
    }

private:
    float v_y = 0;
    float v_x = 100;
    QColor generateRandomColor()
    {
        int red = qrand() % 256;
        int green = qrand() % 256;
        int blue = qrand() % 256;
        return QColor::fromRgb(red, green, blue);
    }
};

// --------------------------------------------------------------------
class Rect_boundary : public QObject {
public:
    float width;
    float height;
    Rect_boundary(float w, float h) : width(w), height(h) {
    }
};
// -----------------------------------------------------------------------

class Collision : public QObject{
public:
    float g = 0;
    float restitution = 0.8;
    QVector<QVector<float>> pat;
    Collision(){}

    float distance(float x1, float y1, float x2, float y2) {
        float dx = x2 - x1;
        float dy = y2 - y1;
        float dist = std::sqrt(dx*dx + dy*dy);
        return dist;
    }

    void collision_calculation(float dt, ball *ball, Rect_boundary *bound) {
        float v_x, v_y;
        auto result_v = ball->get_velocity();
        v_x = std::get<0>(result_v);
        v_y = std::get<1>(result_v);
        v_y = v_y + g*dt; // 计算新的y方向速度

        ball->x = ball->x + v_x*dt;
        ball->y = ball->y + v_y*dt; // 计算新位置
        // 计算y方向
        if (ball->y  >= bound->height - ball->rad) {
            // 将 y 设置为最大值
            ball->y = bound->height - ball->rad;
            // 计算反弹后的速度, 更新小球位置和速度
            v_y = -restitution * v_y;
            ball->y = ball->y + v_y * dt;
        }
        else if (ball->y <= 0 + ball->rad ) {
            ball->y = ball->rad;
            v_y = -restitution * v_y;
            ball->y = ball->y + v_y * dt;
        }
        // 计算x方向
        if (ball->x >= bound->width - ball->rad){
            ball->x = bound->width - ball->rad;
            // 计算反弹后的速度
            v_x = -restitution * v_x;
            ball->x = ball->x + v_x * dt;
        }
        else if(ball->x <= 0 + ball->rad){
            ball->x = ball->rad;
            v_x = -restitution * v_x;
            ball->x = ball->x + v_x*dt;
        }
        // 更新速度
        ball->set_velocity(v_x, v_y);
    }

    void collision_calculation(float dt, ball *ball_1,  ball *ball_2) {
        float dis= distance(ball_1->x,ball_1->y,ball_2->x,ball_2->y);
        if (dis>=(ball_1->rad+ball_2->rad)){
            // 不碰撞, 返回
            return;
        }else{
            pat.push_back({ball_1->x,ball_1->y,ball_2->x,ball_2->y});
        }

        float v_x_1, v_y_1, v_x_2, v_y_2, m1, m2;
        auto boll_v_1 = ball_1->get_velocity();
        v_x_1 = std::get<0>(boll_v_1);
        v_y_1 = std::get<1>(boll_v_1);
        auto boll_v_2 = ball_2->get_velocity();
        v_x_2 = std::get<0>(boll_v_2);
        v_y_2 = std::get<1>(boll_v_2);
        m1 = ball_1->m; m2 = ball_2->m;



//        auto velocity = [&](float v1, float v2) -> std::pair<float, float>{
//            float new_v1,new_v2;
//            new_v1 = ((m1-m2)*v1 + 2*m2*v2)/(m1+m2);
//            new_v2 = ((m2-m1)*v2 + 2*m1*v1)/(m1+m2);
//            return std::make_pair(new_v1, new_v2);
//        };
//        auto result_x= velocity(v_x_1, v_x_2);
//        auto result_y= velocity(v_y_1, v_y_2);
//        ball_1->set_velocity(result_x.first, result_y.first);
//        ball_2->set_velocity(result_x.second, result_y.second);

    }
};


#endif //BOLL_COLLISION_H
