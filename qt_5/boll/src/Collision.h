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
extern double MINNUM;
double MINNUM = 1e-6;

class Velocity2D{
public:
    explicit Velocity2D(double angle = 0.0, double v = 0.0) : angle(angle), v(v){
        velocity_transform.scale(1,-1);
        __set_cartesian_coordinate();
    }
    void __set_cartesian_coordinate(){
        // 以原点，设置当前速度的直接坐标系
        double this_radian = angle*M_PI / 180;
        double x = v * cos(this_radian);
        double y = v * sin(this_radian);
        cartesian_pooint.setX(x);
        cartesian_pooint.setY(y);
        cartesian_pooint = velocity_transform.map(cartesian_pooint);
    }

    QVector<Velocity2D> velocity_decomposing(double horizontal_angle) const {
        // 将速度分解
        int integer_part = static_cast<int>(horizontal_angle);
        double decimal_part = horizontal_angle - static_cast<double>(integer_part); // 转为int和小数部分
        double vertical_angle = (integer_part+270) % 360 + decimal_part;
        double radian = (angle-horizontal_angle)*M_PI / 180;
        // 应用变换矩阵，进行坐标系变换,Y轴向下延伸，X轴向右延伸
        QPointF transformedPoint = velocity_transform.map(QPointF(cos(radian)*v, sin(radian)*v));
        double vx = transformedPoint.x();
        double vy = transformedPoint.y();
//        qDebug()<<QString("vx:%1 vx_angle:%2,  vy:%3 vx_angle:%4").arg(vx).arg(horizontal_angle).arg(vy).arg(vertical_angle);
        return QVector<Velocity2D>{Velocity2D(horizontal_angle,vx),Velocity2D(vertical_angle,vy)};
    }

    QVector<Velocity2D> horizontal_decomposition() const{
        return velocity_decomposing(0);
    }

    Velocity2D operator+(const  Velocity2D& other) const {
        // 角度一致才能相加
        if (fabs(other.get_angle()-angle)>MINNUM){
            throw std::runtime_error("角度不一致");
        }
        Velocity2D result(angle,v + other.get_v());
        return result;
    }

    void set_v(const double new_angle, const double new_v) {
        angle = new_angle;
        v = new_v;
        __set_cartesian_coordinate();
    }

    double get_v() const{
        return v;
    }

    double get_angle() const{
        return angle;
    }

    QPointF get_cartesian_coordinate(){
        return cartesian_pooint;
    }

    void show_log() const{
        qDebug()<<QString("v:%1, angle:%2, cartesian_pooint:").arg(v).arg(angle)<<cartesian_pooint;
    }
private:
    double angle;
    double v;
    QPointF cartesian_pooint;
    QTransform velocity_transform;

};

Velocity2D weight_composition(Velocity2D &v_x, Velocity2D &v_y) {
    // 将x 和 y 方向的速度合成 。输入的速度必须要求是x，y轴方向(0, 270)
    if (fabs(v_x.get_angle() - 0) > MINNUM || fabs(v_y.get_angle() - 270) > MINNUM ) {
        throw std::runtime_error("分解分量的角度必须要为0,或者90");
    }
    if (fabs(v_x.get_v()) < MINNUM){
        return v_y;
    }
    else if(fabs(v_y.get_v()) < MINNUM){
        return v_x;
    }else{
        // 坐标系,象限如下,所以需要在计算结果添加负号
        //   3 | 4
        //  ------>
        //   2 | 1
        double new_degrees;
        double radians = std:: atan(v_y.get_v()/v_x.get_v());
        if (radians > 0){
            // 在 1,3象限
            if (v_x.get_v()>0 && v_y.get_v()>0){
                // 1象限
                new_degrees = -radians * (180.0 / M_PI) ;
            } else{
                new_degrees = -radians * (180.0 / M_PI) - 180 ;
            }
        }else{
            // 在 2,4象限
            if (v_x.get_v()>0 && v_y.get_v()<0){
                // 4象限
                new_degrees = -radians * (180.0 / M_PI) ;
            } else{
                new_degrees = -radians * (180.0 / M_PI) - 180;
            }
        }
        double new_v = sqrt(std::pow(v_y.get_v(), 2) + std::pow(v_x.get_v(), 2));
        return Velocity2D{new_degrees,new_v};
    }
}
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

    void coordinate_change(QRectF r){
        ball_rect = r;
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
        if (trace_queue.size()==2){
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

// -----------------------------------------------------------------------

class Collision : public QObject{
public:
    double restitution = 1;
    Collision()= default;

    void collision_calculation(double dt, ball *ball, Rect_boundary *bound) const {
        for (int i=0; i < bound->coordinates.size(); i++){
            QVector2D p1, p2;
            if (i == bound->coordinates.size()-1){
                p1.setX(static_cast<float>(bound->coordinates[i]->x()));
                p1.setY(static_cast<float>(bound->coordinates[i]->y()));
                p2.setX(static_cast<float>(bound->coordinates[0]->x()));
                p2.setY(static_cast<float>(bound->coordinates[0]->y()));
            }else{
                p1.setX(static_cast<float>(bound->coordinates[i]->x()));
                p1.setY(static_cast<float>(bound->coordinates[i]->y()));
                p2.setX(static_cast<float>(bound->coordinates[i+1]->x()));
                p2.setY(static_cast<float>(bound->coordinates[i+1]->y()));
            }
            QVector2D ball_cent_vector2d(static_cast<float>(ball->ball_cent.x()),static_cast<float>(ball->ball_cent.y()));
            double distance;
            QPointF footPoint;
            std::tie(distance, footPoint) = ShortestDistance_point(p1, p2, ball_cent_vector2d);
            if (distance < ball->rad){
                // 碰撞, 球心至垂足点
                QLineF vertical_line(ball->ball_cent, footPoint);
                auto re = ball->ball_v.velocity_decomposing( vertical_line.angle());
                // 碰撞速度根据计算取反向
                re[0].set_v(re[0].get_angle(),-re[0].get_v()*restitution);
                // 速度分解成x, y
                Velocity2D ball_v_x(0,0);
                Velocity2D ball_v_y(270,0);
                for(const auto& v : re){
                    if(fabs(v.get_v()-0)<MINNUM){
                        continue;
                    }
                    auto dem_v = v.horizontal_decomposition();
                    ball_v_x = ball_v_x + dem_v[0];
                    ball_v_y = ball_v_y + dem_v[1];
                }
                // 分解的速度合成
                auto composition_re = weight_composition(ball_v_x, ball_v_y);
                // 设置新的速度
                ball->set_v(composition_re);
                // 设置新的位置

                while (true){
                    auto dx = ball_v_x.get_v()*dt;
                    auto dy = ball_v_y.get_v()*dt;
                    QPointF dpf(dx, dy);
                    ball->coordinate_change_df(dpf);
                    ball_cent_vector2d.setX(ball->ball_cent.x());
                    ball_cent_vector2d.setY(ball->ball_cent.y());
                    std::tie(distance, footPoint) = ShortestDistance_point(p1, p2, ball_cent_vector2d);
                    if (distance > ball->rad){
                        break;
                    }
                }
            }
        }
        auto v_xy = ball->ball_v.horizontal_decomposition();
        auto dx = v_xy[0].get_v()*dt;
        auto dy = v_xy[1].get_v()*dt;
        QPointF dpf(dx, dy);
        ball->coordinate_change_df(dpf);
    }

    static std::pair<double, QPointF> ShortestDistance_point(const QVector2D& p1, const QVector2D& p2, const QVector2D& point)
    {
        // p1,p2, 线段起点,终点。point点的位置
        QVector2D line = p2 - p1;   // 线段向量
        QVector2D pointToStart = point - p1;  // 点到线段起点的向量

        float dotProduct = QVector2D::dotProduct(pointToStart, line);  // 点到线段起点向量与线段向量的点积
        float lengthSquared = line.lengthSquared();  // 线段向量长度的平方
        // 判断点在线段延长线上的情况 (向量内积的定义) 由a·b = |a||b|cos(θ)的推理而来
        if (dotProduct < 0) {
            QPointF p = p1.toPoint();
            return std::pair<double, QPointF>{point.distanceToPoint(p1), p};  // 返回点到线段起点的距离
        }
        // |b|cos(θ)>|a| 即表示右侧的情况
        if (dotProduct > lengthSquared) {
            QPointF p = p2.toPoint();
            return std::pair<double, QPointF>{point.distanceToPoint(p2), p};  // 返回点到线段终点的距离
        }
        // 计算垂足坐标
        QVector2D projection = p1 + (dotProduct / lengthSquared) * line;
        QPointF p = projection.toPointF();
        // 返回点到垂足的距离
        return std::pair<double, QPointF>{point.distanceToPoint(projection), p} ;
    }

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
