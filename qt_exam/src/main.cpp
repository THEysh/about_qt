#include <QApplication>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include "iostream"
#include "myfirst.h"
#include "function.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto MainWindow = new QMainWindow();
    Ui_MainWindow ui_f{};
    ui_f.setupUi(MainWindow);
    //创建一个信号接受者，用于接收信号（这个类里面有槽函数）
    ThreadReceiver receiver(ui_f); double sleep_time = 1; long dim =  123456789;

    receiver.button1_connect(receiver.ui_f.pushButton,sleep_time);
    receiver.button2_connect(receiver.ui_f.pushButton_2,sleep_time, dim); //将dim10进制转为2进制(10亿以内)
    MainWindow->show();

    return QApplication::exec();
}
