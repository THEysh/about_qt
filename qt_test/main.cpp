#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 创建场景和视图
    QGraphicsScene scene;
    QGraphicsView view(&scene);

    // 加载网络图片
    QUrl url("https://lmg.jj20.com/up/allimg/tp09/210H51R3313N3-0-lp.jpg");
    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(QNetworkRequest(url));
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QByteArray data = reply->readAll();
    QPixmap pixmap;
    pixmap.loadFromData(data);

    // 创建PixmapItem并设置图片
    QGraphicsPixmapItem pixmapItem(pixmap);
    scene.addItem(&pixmapItem);


    // 允许平移和缩放
    view.setDragMode(QGraphicsView::ScrollHandDrag);
    view.setInteractive(true);
    view.setRenderHint(QPainter::SmoothPixmapTransform);
    view.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view.setBackgroundBrush(Qt::white);
    view.setRenderHint(QPainter::Antialiasing, true);
    view.setRenderHint(QPainter::TextAntialiasing, true);
    view.setRenderHint(QPainter::HighQualityAntialiasing, true);
    view.setRenderHint(QPainter::SmoothPixmapTransform);
    // 调整视图大小
    view.fitInView(&pixmapItem, Qt::KeepAspectRatio);
    // 显示视图
    view.show();

    return app.exec();
}
