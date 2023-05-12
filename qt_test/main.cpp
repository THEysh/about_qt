
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsBlurEffect>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene scene;
    QGraphicsView view(&scene);

    QPixmap originalPixmap("F:\\code\\c_code\\about_qt\\picture_viewer\\src\\ui\\images\\pic_2d\\wallhaven-3z32j3.jpg");


    // 生成高斯模糊图片
    QPixmap blurredPixmap = originalPixmap;
    QGraphicsBlurEffect blurEffect;
    blurEffect.setBlurRadius(150);

    blurredPixmap = blurredPixmap.scaled(view.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    blurEffect.setBlurHints(QGraphicsBlurEffect::QualityHint);

    QGraphicsPixmapItem *blurItem = new QGraphicsPixmapItem(blurredPixmap);
    blurItem->setGraphicsEffect(&blurEffect);
    scene.addItem(blurItem);

    // 设置QGraphicsView的背景
    view.setBackgroundBrush(blurItem->pixmap());

    view.show();
    return a.exec();
}
