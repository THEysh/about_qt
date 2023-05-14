#include <QApplication>
#include <QWidget>

class TransparentWidget : public QWidget {
public:
    TransparentWidget() {
        setWindowFlags(Qt::FramelessWindowHint);
        setAttribute(Qt::WA_TranslucentBackground);
        setWindowOpacity(0.5); // 设置透明度为50%
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    TransparentWidget widget;
    widget.show();
    return app.exec();
}
