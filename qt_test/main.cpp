#include <QtWidgets>

class DragWidget : public QWidget
{
public:
    DragWidget(QWidget *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
};

DragWidget::DragWidget(QWidget *parent)
        : QWidget(parent) {
    setMinimumSize(200, 200);
    setAcceptDrops(true);
}

void DragWidget::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasFormat("text/plain"))
        event->acceptProposedAction();
}

void DragWidget::dragMoveEvent(QDragMoveEvent *event) {
    if (event->mimeData()->hasFormat("text/plain")) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->ignore();
    }
}

void DragWidget::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasFormat("text/plain")) {
        QByteArray data = event->mimeData()->data("text/plain");
        QString text = data.constData();
        QLabel *label = new QLabel(text, this);
        label->move(event->pos());
        label->show();
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->ignore();
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    DragWidget widget;
    widget.show();

    return app.exec();
}
