#include <QtWidgets>

class MyTreeWidget : public QTreeWidget {
public:
    MyTreeWidget(QWidget *parent = nullptr) : QTreeWidget(parent) {
        setDragEnabled(true);
        setSelectionMode(QAbstractItemView::MultiSelection);
    }
protected:
    QMimeData *mimeData(const QList<QTreeWidgetItem *> items) const override {
        QMimeData *mimeData = new QMimeData;
        QByteArray encodedData;
        QDataStream stream(&encodedData, QIODevice::WriteOnly);
        for (auto item : items) {
            QString text = item->text(0);
            auto text2 = item->data(0,Qt::UserRole);
            stream << text<< text2.toString();
        }
        mimeData->setData("application/x-qtreewidget-values", encodedData);
        return mimeData;
    }
};

class MyGraphicsView : public QGraphicsView {
public:
    MyGraphicsView(QWidget *parent = nullptr) : QGraphicsView(parent), scene(new QGraphicsScene) {
        setScene(scene);
        setAcceptDrops(true);
    }
protected:
    void dragEnterEvent(QDragEnterEvent *event) override {
        if (event->mimeData()->hasFormat("application/x-qtreewidget-values")) {
            event->acceptProposedAction();
        } else {
            event->ignore();
        }
    }

    void dragMoveEvent(QDragMoveEvent *event) override {
        if (event->mimeData()->hasFormat("application/x-qtreewidget-values")) {
            event->acceptProposedAction();
        } else {
            event->ignore();
        }
    }

    void dropEvent(QDropEvent *event) override {
        if (event->mimeData()->hasFormat("application/x-qtreewidget-values")) {
            QByteArray encodedData = event->mimeData()->data("application/x-qtreewidget-values");
            QDataStream stream(&encodedData, QIODevice::ReadOnly);
            int i = 0;
            while (!stream.atEnd()) {
                QString text;
                stream >> text;
                qDebug()<<"stream"<<text;
                auto item = new QGraphicsTextItem(text);
                item->setPos(event->pos() + QPointF(i * 20, i * 20));
                scene->addItem(item);
                i++;
            }
            event->acceptProposedAction();
        } else {
            event->ignore();
        }
    }

private:
    QGraphicsScene *scene = nullptr;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MyTreeWidget treeWidget;
    treeWidget.setColumnCount(1);
    treeWidget.setHeaderLabels({ "Values" });
    for (int i = 1; i <= 10; i++) {
        auto item = new QTreeWidgetItem(&treeWidget, { QString("Item %1").arg(i) });
        item->setData(0, Qt::UserRole, "i * 10");
    }
    treeWidget.show();

    MyGraphicsView graphicsView;
    graphicsView.resize(400, 300);
    graphicsView.show();

    return app.exec();
}
