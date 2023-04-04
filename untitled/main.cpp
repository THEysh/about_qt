#include <QApplication>
#include <QPushButton>

#include <QtWidgets>

class MyMainWindow : public QMainWindow
{
public:
    MyMainWindow(QWidget *parent = nullptr) : QMainWindow(parent)
    {
        // 设置窗口标题和大小
        setWindowTitle(tr("My Window"));
        setFixedSize(480, 720); // 宽高比例为6:9

        // 创建一个标签并设置图片
        QLabel *label = new QLabel(this);
        QPixmap pixmap(":/image/image.jpg");
        label->setPixmap(pixmap);
        label->setScaledContents(true);

        // 将标签居中放置在窗口中央
        QGridLayout *layout = new QGridLayout;
        layout->addWidget(label, 0, 0, Qt::AlignCenter);
        QWidget *widget = new QWidget;
        widget->setLayout(layout);
        setCentralWidget(widget);

        // 设置窗口大小策略为 Expanding
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

protected:
    void resizeEvent(QResizeEvent *event) override
    {
        // 调用父类的resizeEvent()函数
        QMainWindow::resizeEvent(event);
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyMainWindow w;
    w.show();
    return a.exec();
}
