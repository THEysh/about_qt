//
// Created by top on 2023-07-11.
//

#include "Collision.h"
#include "Object_category.h"

extern double MINNUM;
double MINNUM = 1e-6;

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

Velocity2D::Velocity2D(double angle, double v) :
        angle(angle),
        v(v) {
    velocity_transform.scale(1, -1);
    _set_cartesian_coordinate();
}

void Velocity2D ::_set_cartesian_coordinate(){
    // 以原点，设置当前速度的直角坐标系(根据角度拆分)
    double this_radian = angle*M_PI / 180;
    double x = v * cos(this_radian);
    double y = v * sin(this_radian);
    cartesian_pooint.setX(x);
    cartesian_pooint.setY(y);
    cartesian_pooint = velocity_transform.map(cartesian_pooint);
}

QVector<Velocity2D> Velocity2D :: velocity_decomposing(double horizontal_angle) const {
    // 将速度分解
    double vertical_angle = std::fmod(horizontal_angle + 270, 360);
    double radian = (angle-horizontal_angle)*M_PI / 180;
    // 应用变换矩阵，进行坐标系变换,Y轴向下延伸，X轴向右延伸
    QPointF transformedPoint = velocity_transform.map(QPointF(cos(radian)*v, sin(radian)*v));
    double vx = transformedPoint.x();
    double vy = transformedPoint.y();
//        qDebug()<<QString("vx:%1 vx_angle:%2,  vy:%3 vx_angle:%4").arg(vx).arg(horizontal_angle).arg(vy).arg(vertical_angle);
    return QVector<Velocity2D>{Velocity2D(horizontal_angle,vx),Velocity2D(vertical_angle,vy)};
}

QVector<Velocity2D> Velocity2D :: horizontal_decomposition() const{
    return velocity_decomposing(0);
}

Velocity2D Velocity2D :: operator+(const  Velocity2D& other) const {
    // 角度一致才能相加
    if (fabs(other.get_angle()-angle)>MINNUM){
        throw std::runtime_error("角度不一致");
    }
    Velocity2D result(angle,v + other.get_v());
    return result;
}

void Velocity2D :: set_v(const double new_angle, const double new_v) {
    angle = new_angle;
    v = new_v;
    _set_cartesian_coordinate();
}

double Velocity2D :: get_v() const{
    return v;
}

double Velocity2D :: get_angle() const{
    return angle;
}

QPointF Velocity2D :: get_cartesian_coordinate() const{
    return cartesian_pooint;
}

void Velocity2D :: show_log() const{
    qDebug()<<QString("v:%1, angle:%2, cartesian_pooint:").arg(v).arg(angle)<<cartesian_pooint;
}

// ------------------------------------------------------------

Collision::Collision(){}

void Collision :: collision_calculation(double dt, Ball &ball, Rect_boundary &bound) const {
        auto v_xy = ball.ball_v.horizontal_decomposition();
        auto dx = v_xy[0].get_v()*dt;
        auto dy = v_xy[1].get_v()*dt;
        QPointF dpf(dx, dy);
        ball.coordinate_change_df(dpf);
        for (int i=0; i < bound.size(); i++){
            QVector2D p1, p2;
            if (i == bound.size()-1){
                p1.setX(static_cast<float>(bound[i].x()));
                p1.setY(static_cast<float>(bound[i].y()));
                p2.setX(static_cast<float>(bound[0].x()));
                p2.setY(static_cast<float>(bound[0].y()));
            }else{
                p1.setX(static_cast<float>(bound[i].x()));
                p1.setY(static_cast<float>(bound[i].y()));
                p2.setX(static_cast<float>(bound[i+1].x()));
                p2.setY(static_cast<float>(bound[i+1].y()));
            }
            // 描写 球体,线段的碰撞
            collision_calculation(dt, ball, p1, p2);
        }
    }

void Collision :: collision_calculation(double dt, Ball &ball, QVector2D &p1, QVector2D &p2) const{
        QVector2D ball_cent_vector2d(static_cast<float>(ball.ball_cent.x()),static_cast<float>(ball.ball_cent.y()));
        double distance; QPointF footPoint;
        std::tie(distance, footPoint) = ShortestDistance_point(p1, p2, ball_cent_vector2d);

        if ((distance - ball.rad) < MINNUM){
            // 碰撞, 球心至垂足点
            QLineF vertical_line(ball.ball_cent, footPoint);
            auto re = ball.ball_v.velocity_decomposing( vertical_line.angle());
            // 碰撞速度根据计算取反向
            re[0].set_v(re[0].get_angle(),- re[0].get_v()*restitution);
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
            ball.set_v(composition_re);
            while (true){
                // 对当前状态操作至 不碰撞为止，一般执行1--2步
                auto change_dx = ball_v_x.get_v()*dt;
                auto change_dy = ball_v_y.get_v()*dt;
                QPointF change_dpf(change_dx, change_dy);
                ball.coordinate_change_df(change_dpf);
                ball_cent_vector2d.setX(static_cast<float>(ball.ball_cent.x()));
                ball_cent_vector2d.setY(static_cast<float>(ball.ball_cent.y()));
                std::tie(distance, footPoint) = ShortestDistance_point(p1, p2, ball_cent_vector2d);
                if ((distance - ball.rad) > MINNUM){
                    // 不碰撞
                    break;
                }
            }
        }
    }

std::pair<double, QPointF> Collision :: ShortestDistance_point(const QVector2D& p1, const QVector2D& p2, const QVector2D& point)
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

