#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    QLabel *label = new QLabel("Hello Qt!");
    label->setAlignment(Qt::AlignCenter);
    window.setWindowFlags(Qt::FramelessWindowHint);

    // 添加“最小化”按钮
    QPushButton *minimizeButton = new QPushButton("-");
    minimizeButton->setFixedSize(20, 20);
    QObject::connect(minimizeButton, &QPushButton::clicked, &window, &QWidget::showMinimized);

    // 添加“最大化”按钮
    QPushButton *maximizeButton = new QPushButton("+");
    maximizeButton->setFixedSize(20, 20);
    QObject::connect(maximizeButton, &QPushButton::clicked, [&window]() {
        if (window.isMaximized()) {
            window.showNormal();
        } else {
            window.showMaximized();
        }
    });

    // 添加“关闭”按钮
    QPushButton *closeButton = new QPushButton("x");
    closeButton->setFixedSize(20, 20);
    QObject::connect(closeButton, &QPushButton::clicked, &app, &QApplication::quit);

    // 创建水平布局，并依次添加按钮和标签
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(minimizeButton);
    layout->addWidget(maximizeButton);
    layout->addWidget(closeButton);
    layout->addWidget(label);

    // 创建新的 Widget 并设置水平布局作为其布局
    QWidget *widget = new QWidget();
    widget->setLayout(layout);
    // window.setCentralWidget(widget);

    window.setWindowTitle("My Qt Window");
    window.show();

    return app.exec();
}
