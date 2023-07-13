#include <ctime>
#include <QTime>
#include <QVector>
#include "src/Collision.h"
#include <QtWidgets>
#include <random>

// 随机数引擎
std::mt19937 random_gen(std::chrono::system_clock::now().time_since_epoch().count());
template<typename T>
T get_random(T min, T max){
    std::uniform_real_distribution<T> dis(min, max);
    return dis(random_gen);
}

class CustomWidget : public QWidget {
public:
    CustomWidget(QWidget *parent = nullptr) :
            QWidget(parent),
            interval(10),
            collision(),
            bound(QVector<QPointF*>{
                    new QPointF(0, 0),
                    new QPointF(0, 800),
                    new QPointF(800, 800),
                    new QPointF(800, 0),
            }){
        this->resize(800,800);
        // 设置计时器更新帧数
        timer.setInterval(interval);
        // 创建小球
        for(int i = 1; i < 2; i++){
            // 使用 push_back 函数添加对象
            double radius = get_random(15.0,40.0);
            double x = get_random(0.0, 800 - 2*radius);
            double y = get_random(0.0, 800 - 2*radius);
            // 使用左上角坐标 (x, y)、宽度和高度创建矩形。将其用于圆的绘制
            QRectF ball_rect(x,y,2*radius,2*radius);
            double angle = get_random(0.0, 360.0);
            double v = get_random(400.0,1000.0);
            auto ball_v = Velocity2D(angle,v);
            balls.push_back(new ball(ball_rect, ball_v));
        }
        QObject::connect(&timer, &QTimer::timeout, [&]() {
            // qDebug() << "定时器触发，当前时间：" << QTime::currentTime().toString("hh:mm:ss");
            double dt =  static_cast<double>(interval) / static_cast<double>(1000);
            for (auto ball:balls){
                collision.collision_calculation(dt, ball, &bound);
            }
            update();
        });
        timer.start();
    }

protected:
    QTimer timer;
    int interval;
    Collision collision;
    Rect_boundary bound;
    QVector<ball*> balls;

    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true); // 开启抗锯齿
        QPen pen(Qt::darkCyan);
        pen.setWidth(5);
        painter.setPen(pen);

        // 绘制边界
        QPolygon polygon;
        for (auto p:bound.coordinates){
            polygon<<p->toPoint();
        }
        painter.setBrush(Qt::black); // 设置填充颜色为蓝色
        painter.drawPolygon(polygon);
        // 绘制圆
        for (auto ball:balls) {
            painter.setBrush(ball->color);
            // 计算圆的位置和大小
            painter.drawEllipse(ball->ball_rect);
            painter.drawPoint(ball->ball_cent);

            if (ball->trace_queue.size()==2){
                for (int i = 0; i < 2; ++i) {
                    pen.setWidth(10);
                    painter.setPen(pen);
                    painter.drawPoint(ball->trace_queue[i]);
                    pen.setWidth(5);
                    painter.setPen(pen);
                }
            }

        }
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    CustomWidget widget;
    widget.setWindowTitle("绘制圆形示例");
    widget.show();

    return app.exec();
}
