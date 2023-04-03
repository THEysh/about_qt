#include <QApplication>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include "myfirst.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto *frame = new QFrame();
    Ui_Form ui_f{};
    ui_f.setupUi(frame);
    frame->show();
//    frame->setFrameStyle(QFrame::Box | QFrame::Raised);
//
//    QLabel *label = new QLabel("Hello World!");
//    QHBoxLayout *layout = new QHBoxLayout();
//    layout->addWidget(label);
//    frame->setLayout(layout);
//
//    frame->show();

    return QApplication::exec();
}
