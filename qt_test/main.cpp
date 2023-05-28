#include <QtWidgets>
#include <QtConcurrent/QtConcurrent>

void mySort(QList<QString> inputList)
{
    // 排序输入列表
    QList<QString> outputList = inputList;
    std::sort(outputList.begin(), outputList.end());

    // 将结果输出到标准输出流
    for (const QString& str : outputList) {
        qDebug() << str;
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QList<QString> myList = {"c", "a", "d", "b"};
    QFuture<void> future = QtConcurrent::run([=]() {
        mySort(myList);
    });
    qDebug()<<"hello";
    return app.exec();
}
