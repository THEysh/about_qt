#include <QCoreApplication>
#include <QObject>
#include <QThread>
#include <QDebug>
#include <QTimer>
#include "treadqt.h"
//
//int main(int argc, char *argv[]) {
//    QCoreApplication app(argc, argv);
//    WorkerThread worker;
//    QObject::connect(&worker, &WorkerThread::resultReady, &app, [](const QString &result) {
//        qDebug() << "Result received:" << result;
//        QCoreApplication::exit();
//    });
//    worker.start();
//
//    return app.exec();
//}
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QMovie>
#include <QDebug>
#include <memory>
#include "QMouseEvent"
class MyView : public QGraphicsView {
public:
    MyView(QWidget* parent = nullptr) : QGraphicsView(parent) {
        setMouseTracking(true);
        scene = new QGraphicsScene();
        setScene(scene);

        au_movie = std::make_unique<QMovie>("C:\\Users\\Administrator\\Desktop\\新建文件夹\\AA7.gif");
        au_movie->start();

        graphics_gifItem_unique = new QGraphicsPixmapItem();
        QRect myRect(0,0,au_movie->currentImage().width(),au_movie->currentImage().height());
        graphics_gifItem_unique->setPixmap(QPixmap::fromImage(au_movie->currentImage()));
        graphics_gifItem_unique->setPos(0, 0);
        gif_rect = graphics_gifItem_unique->pixmap().rect();
        or_pixmap = QPixmap::fromImage(au_movie->currentImage());
        scene->addItem(graphics_gifItem_unique);

        timer.setInterval(50);
        timer.start();
        connect(&timer, &QTimer::timeout, [this, view_width = width(), view_height = height()](){
            or_pixmap = QPixmap::fromImage(au_movie->currentImage());
            QRect or_rect = or_pixmap.rect();
            std::unique_ptr<QPixmap> gif_pixmap;
            if ((view_width > or_rect.width()) && (view_height > or_rect.height())) {
                gif_pixmap = std::make_unique<QPixmap>(or_pixmap);
            } else {
                gif_pixmap = std::make_unique<QPixmap>(or_pixmap.scaled(view_width, view_height, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            }
            graphics_gifItem_unique->setPixmap(*gif_pixmap);
            gif_rect = graphics_gifItem_unique->pixmap().rect();
        });
    }

protected:
    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            m_lastPos = event->pos();
        }
        QGraphicsView::mousePressEvent(event);
    }

    void mouseMoveEvent(QMouseEvent* event) override {
        if (event->buttons() & Qt::LeftButton) {
            QPointF offset = event->pos() - m_lastPos;
            translate(offset.x(), offset.y());
            m_lastPos = event->pos();
        }
        QGraphicsView::mouseMoveEvent(event);
    }

private:
    QGraphicsScene* scene;
    std::unique_ptr<QMovie> au_movie;
    QPixmap or_pixmap;
    std::unique_ptr<QPixmap> gif_pixmap;
    QGraphicsPixmapItem* graphics_gifItem_unique;
    QRect gif_rect;
    QTimer timer;
    QPoint m_lastPos;
};

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    MyView view;
    view.show();
    return app.exec();
}