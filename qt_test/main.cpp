#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QApplication>
#include "qdebug.h"
class MyWidget : public QWidget {
public:
    MyWidget(QWidget *parent = nullptr);
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    int a=0; int b=0; int c=0;
};

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    setAcceptDrops(true);
}

void MyWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
    qDebug()<<"a"<<a++;
}

void MyWidget::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
    qDebug()<<"b"<<b++;
}

void MyWidget::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasUrls()) {
        QList<QUrl> urls = mimeData->urls();
        for (const QUrl &url : urls) {
            QString filePath = url.toLocalFile();
            qDebug() << "Dropped file path: " << filePath;
        }
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
    qDebug()<<"c"<<c++;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MyWidget widget;

    widget.setWindowTitle("Drag and Drop Example");
    widget.setGeometry(100, 100, 600, 400);
    widget.show();
    return app.exec();
}
