#include <QApplication>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include "iostream"
#include "myfirst.h"
#include "function.h"
#include <QMetaType>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto *MainWindow = new QMainWindow();
    Ui_MainWindow ui_f{};
    ui_f.setupUi(MainWindow);

    //创建一个信号接受者，用于接收信号（这个类里面有槽函数）
    ThreadReceiver receiver;
    QObject::connect(ui_f.pushButton, &QPushButton::clicked, &receiver, &ThreadReceiver::do_work_Something);


    MainWindow->show();

//    frame->setFrameStyle(QFrame::Box | QFrame::Raised);
//    QLabel *label = new QLabel("Hello World!");
//    QHBoxLayout *layout = new QHBoxLayout();
//    layout->addWidget(label);
//    frame->setLayout(layout);
//    frame->show();
    return QApplication::exec();
}
