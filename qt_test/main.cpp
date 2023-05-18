#include <iostream>
#include <QString>
#include "qdebug.h"

#include <QFileInfo>
#include <QDebug>
void callbackFunc(int result) {
    std::cout << "Result: " << result << std::endl;
}

void callbackFunc2(int result) {
    std::cout << "Result: " << result << std::endl;
}
void doSomething(int a, int b, void (*callback)(int)) {
    int result = a + b;
    callback(result);
}

int main() {
    doSomething(11, 2, callbackFunc2);
    doSomething(1, 2, callbackFunc);

    QString fileName = "/asd/das/example.sVg";
    QFileInfo fileInfo(fileName);

    if (fileInfo.suffix().compare("svg", Qt::CaseInsensitive) == 0) {
        qDebug() << "The file is an SVG format file.";
    } else {
        qDebug() << "The file is not an SVG format file.";
    }
    int a = 3;

    return 0;
}
