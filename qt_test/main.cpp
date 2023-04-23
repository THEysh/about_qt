#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <iostream>

using namespace std;

class MyWidget : public QWidget {
public:
    explicit MyWidget(QWidget *parent = nullptr) : QWidget(parent) {}

protected:
    void mouseMoveEvent(QMouseEvent* event) override {
        if (event->buttons() == Qt::LeftButton){
            cout << "1111: (" << event->pos().x() << ", " << event->pos().y() << ")" << endl;
        }
        cout << "Mouse position: (" << event->pos().x() << ", " << event->pos().y() << ")" << endl;
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MyWidget widget;
    widget.setFixedSize(400, 300);
    widget.show();

    return QApplication::exec();
}
