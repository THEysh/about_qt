#include <iostream>
#include <cmath>
#include <QVector>
#include <QTransform>
#include "QDebug"
#include <QtWidgets>

class Vector2D{
// 逆时针为正
public:
Vector2D(double angle = 0.0, double v = 0.0) : angle(angle), v(v) {
    }
    QVector<Vector2D> velocity_decomposing(double horizontal_angle) {
        // 将速度分解
        int integer_part = static_cast<int>(horizontal_angle);
        double decimal_part = horizontal_angle - static_cast<double>(integer_part); // 转为int和小数部分
        double vertical_angle = (integer_part+270) % 360 + decimal_part;
        double radian = (angle-horizontal_angle)*M_PI / 180;
        qreal vx = v * qCos(radian);    // 使用 qCos 函数计算 x 坐标
        qreal vy = v * qSin(radian);    // 使用 qSin 函数计算 y 坐标
        vy = -vy; // 坐标轴转换需要镜像y轴
        qDebug()<<QString("vx:%1 vx_angle:%2,  vy:%3 vx_angle:%4").arg(vx).arg(horizontal_angle).arg(vy).arg(vertical_angle);
        return QVector<Vector2D>{Vector2D(horizontal_angle,vx),Vector2D(vertical_angle,vy)};
    }

    double get_v(){
        return v;
    }

    double get_angle(){
        return angle;
    }

private:
    double angle;
    double v;
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
        transform_move.scale(1,-1);
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

std::pair<double, QPointF> dis_cal(const QPointF& point, const QLineF& line){
    // 计算点到直线的距离
    qreal dx = line.dx();
    qreal dy = line.dy();
    qreal px = point.x() - line.p1().x();
    qreal py = point.y() - line.p1().y();
    qreal distance = std::abs(dy * px - dx * py) / std::sqrt(dx * dx + dy * dy);
    // 计算垂足点
    qreal t = (dx * px + dy * py) / (dx * dx + dy * dy);
    qreal fx = line.p1().x() + t * dx;
    qreal fy = line.p1().y() + t * dy;

    return std::pair<double, QPointF>{distance, QPointF(fx, fy)};
};

std::pair<double, QPointF> ShortestDistance_point(const QVector2D& p1, const QVector2D& p2, const QVector2D& point)
{
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

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    double angle = 315.55555;
    double v = 1.41421;
    Vector2D v1(angle, v);
    auto re = v1.velocity_decomposing(0);

    LineLabel label;
    label.v_p = label.polarToCartesian(angle,v);
    label.v1 = label.polarToCartesian(re[0].get_angle(),re[0].get_v());
    label.v2 = label.polarToCartesian(re[1].get_angle(),re[1].get_v());

    label.resize(700,700);
    label.show();
    // 创建一个QTransform对象
    QTransform tran;

    // 定义一个待变换的点
    QPointF point(5, -5);
    // 设置平移变换
    tran.translate(5, 5);
    tran.scale(1,-1);
    // 应用变换到点上
    QPointF transformedPoint = tran.map(point);

    qDebug() << "原始点：" << point;
    qDebug() << "变换后的点：" << transformedPoint;
    for (int i =0 ;i <100;i++){
        QPointF tempp1(rand()%10,rand()%10);
        QPointF tempp2(rand()%10,rand()%10);
        QLineF l1(tempp1,tempp2);
        QLineF l2(tempp2,tempp1);
        double remainder = std::fmod(l2.angle()+180, 360);
        qDebug() << "ddd：" << l1.angle()<< l2.angle()<<  remainder;
    }


    return a.exec();
}
