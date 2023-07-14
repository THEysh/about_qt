#include <QtWidgets>

class CustomWidget : public QWidget {
public:
    CustomWidget(QWidget *parent = nullptr) : QWidget(parent) {}

protected:
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true); // 设置抗锯齿模式

        // 指定圆心坐标和半径
        int centerX = 100;
        int centerY = 100;
        int radius = 20;

        // 绘制圆形
        painter.setPen(Qt::black); // 设置画笔颜色
        painter.setBrush(Qt::red); // 设置刷子颜色
        painter.drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    CustomWidget widget;
    widget.setWindowTitle("绘制圆形示例");
    widget.resize(200, 200);
    widget.show();

    return app.exec();
}
