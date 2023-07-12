#include <iostream>
#include <cmath>
#include <QVector>
#include <QTransform>
#include "QDebug"
#include <QtWidgets>

class Vector2D{
// 逆时针为正
public:
Vector2D(double angle = 0.0, double v = 0.0) : angle(angle), v(v) {}
    QVector<Vector2D> velocity_decomposing(double horizontal_angle) {
        // 将速度分解
        int integer_part = static_cast<int>(horizontal_angle);
        double decimal_part = horizontal_angle - static_cast<double>(integer_part); // 转为int和小数部分
        double vertical_angle = (integer_part+90) % 360 + decimal_part;

        double radian = (angle-horizontal_angle)*M_PI / 180;
        double vx = cos(radian)*v;
        double vy = sin(radian)*v;

        if (vx<0){
            vx = fabs(vx);
            horizontal_angle += 180;
        }
        if (vy<0){
            vy = fabs(vy);
            vertical_angle += 180;
        }
        qDebug()<<QString("vx:%1 vx_angle:%2,  vy:%3 vx_angle:%4").arg(vx).arg(horizontal_angle).arg(vy).arg(vertical_angle);
        return QVector<Vector2D>{Vector2D(horizontal_angle,vx),Vector2D(vertical_angle,vy)};
    }
    double angle;
    double v;
private:
};

class LineLabel : public QLabel
{
public:
    QPointF v1; QPointF v2; QPointF v_p;
    explicit LineLabel(QWidget* parent = nullptr) : QLabel(parent) {}

    QPointF polarToCartesian(double angle, double radius) {
        // 将角度转换为弧度
        double radian = angle * M_PI / 180.0;
        QPointF cartesian(radius * cos(radian), radius * sin(radian));
        return cartesian;
    }

    void draw_line(QPointF a, QPointF b, QPointF c){
        v1 = a;
        v2 = b;
        v_p = c;
    }

protected:
    void paintEvent(QPaintEvent* event) override
    {
        QLabel::paintEvent(event);
        QPainter painter(this);

        QPen pen(Qt::red); // 创建红色画笔对象
        pen.setWidth(4);   // 设置线宽
        pen.setStyle(Qt::DashLine);   // 将线条样式设置为虚线

        painter.setPen(pen); // 应用画笔到绘制器上
        auto a = QPointF(rect().left(),rect().top() + rect().height()/2);
        auto b =  QPointF(rect().right(),rect().top() + rect().height()/2);
        auto c = QPointF(rect().left() + rect().width()/2,rect().top());
        auto d = QPointF(rect().left() + rect().width()/2,rect().bottom());
        painter.drawLine(a,b);
        painter.drawLine(c,d);
        pen.setWidth(8);
        painter.setPen(pen); // 应用画笔到绘制器上
        painter.drawPoint(rect().center());


        int k = 20;
        // 创建一个平移变换矩阵，将原点平移到rect().center()，并镜像
        QTransform transform_move;
        transform_move.translate(rect().width()/2,rect().height()/2);
        transform_move.scale(1, -1);

        pen.setWidth(5);
        pen.setColor(Qt::blue);
        painter.setPen(pen); // 应用画笔到绘制器上
        painter.drawLine(rect().center(),transform_move.map(v1*k));
        painter.drawLine(rect().center(),transform_move.map(v2*k));

        pen.setWidth(5);
        pen.setColor(Qt::black);
        painter.setPen(pen); // 应用画笔到绘制器上
        painter.drawLine(rect().center(),transform_move.map(v_p*k));
        qDebug()<<rect().center();
        qDebug()<<transform_move.map(v_p*k);

    }
};

Vector2D velocity_composition(Vector2D v1, Vector2D v2){
    if (v1.v<0){
        v1.v = fabs(v1.v);
        int integer_part = static_cast<int>(v1.angle);
        double decimal_part = v1.angle - static_cast<double>(integer_part); // 转为int和小数部分
        v1.angle = (integer_part+180) % 360 + decimal_part;
    }
    if (v2.v<0){
        v2.v = fabs(v2.v);
        int integer_part = static_cast<int>(v2.angle);
        double decimal_part = v2.angle - static_cast<double>(integer_part); // 转为int和小数部分
        v2.angle = (integer_part+180) % 360 + decimal_part;
    }
    double new_angle = v2.angle-v1.angle;
    // 将度转换为弧度
    double theta = new_angle * M_PI / 180.0;
    double new_v = sqrt(v1.v*v1.v +v2.v*v2.v+ 2*cos(theta)*v1.v*v2.v);
    double cost=(new_v*new_v + v1.v*v1.v -v2.v*v2.v)/(2*new_v*v1.v);
    double angle = acos(cost);

    // 将弧度转换为度
    double degree = angle * 180.0 / M_PI;
    qDebug()<<QString("new：%1,%2").arg(new_v).arg(degree);
    return Vector2D{new_angle,new_v};
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    double angel = 188;
    double v = 20;
    Vector2D v1(angel, v);
    auto re = v1.velocity_decomposing(90);

    LineLabel label;
    label.v_p = label.polarToCartesian(angel,v);
    label.v1 = label.polarToCartesian(re[0].angle,re[0].v);
    label.v2 = label.polarToCartesian(re[1].angle,re[1].v);

    label.resize(700,700);
    label.show();
    return a.exec();
}
