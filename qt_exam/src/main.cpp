#include <QApplication>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include "iostream"
#include "ui/myfirst_ui.h"
#include "ui/Qstring_Interface_switching_ui.h"
#include "function.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    auto MainWindow = new QMainWindow();
    Ui_MainWindow ui_f{};
    ui_f.setupUi(MainWindow);
    ThreadReceiver receiver_main(ui_f);
    MainWindow->show();

    auto MainWindow2 = new QMainWindow();
    Ui_Interface_MainWindow ui_interface{};
    ui_interface.setupUi(MainWindow2);
    Interface_Class ui_interface_main(ui_interface);
    MainWindow2->show();



    return QApplication::exec();

}
