#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMovie>
#include <QLabel>
#include <QTimeLine>
#include <memory>
#include <QGraphicsVideoItem>
#include <QMediaPlayer>
#include <QVBoxLayout>
#include <QTimer>
#include "QGraphicsItem"
#include "qdebug.h"
#include "QGraphicsProxyWidget"
#include "QObject"


class MainWindow : public QLabel {
public:
    MainWindow(QWidget *parent = nullptr) : QLabel(parent) {
        setWindowTitle("GIF Animation");
        // 创建一个 QMovie 对象
        QGraphicsScene* scene = new QGraphicsScene();
        QGraphicsView* view = new QGraphicsView(scene);
        QGraphicsProxyWidget* proxy = scene->addWidget(this);
// 创建 QGraphicsProxyWidget 对象，并将 QLabel 控件设置为其窗口小部件
        setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        setAlignment(Qt::AlignCenter);
        QMovie *movie = new QMovie("C:\\Users\\Administrator\\Desktop\\新建文件夹\\6dd.gif", QByteArray(), this);
        setMovie(movie);
        movie->start();
        proxy->setPos(0, 0);
        view->show();
        view->resize(1000,1000);
        connect(movie, &QMovie::frameChanged, [proxy,movie,this](int frameIndex){
            QSize temp_size =  movie->currentPixmap().size();
            qDebug() << "Current Frame Index: " << frameIndex;
            qDebug() << "Current Frame size: " << temp_size;
            this->setFixedSize(temp_size);
            qDebug() << "label size: " <<this->size();
            proxy->resize(temp_size);
            qDebug() << "proxy->resize: " <<proxy->size();
            // 缩放 prxy_unique 控件，使其与 mov_label 控件保持一致
            proxy->setTransform(QTransform::fromScale(1.0, 1.0));  // 先重置缩放比例
// 计算缩放比例
            double scale_x = static_cast<double>(this->width()) / temp_size .width();
            double scale_y = static_cast<double>(this->height()) / temp_size .height();
            proxy->setTransform(QTransform::fromScale(scale_x, scale_y));  // 设置缩放比例
        });
        connect(movie, &QMovie::resized, [](const QSize& size){
            qDebug() << "Animation Resized to " << size;
        });
        connect(movie, &QMovie::started, [movie](){
            qDebug() << "Animation started " ;
        });

        //movie->setScaledSize(QSize(1400, 900));  // 修改 au_movie 对象的大小为 200x200 像素

    }

};
class MainWindow2 : public QObject
{
public:
    std::unique_ptr<QMovie> au_movie;
    std::unique_ptr<QLabel> mov_label;
    std::unique_ptr<QGraphicsProxyWidget> prxy_unique;
    MainWindow2(const QString &path, QGraphicsView *view,QGraphicsScene *scene){
        au_movie = std::make_unique<QMovie>(path);
        au_movie->start();
        // 获取view的中心坐标
        mov_label = std::make_unique<QLabel>("", view);
        QPointF center = view->mapToScene(view->viewport()->rect().center());
        // 调整label的位置
        mov_label->move(center.toPoint() - QPoint(mov_label->width() / 2, mov_label->height() / 2));
        // 表示该QWidget对象的内容应该水平和垂直居中显示。
        mov_label->setAlignment(Qt::AlignCenter);
        mov_label->setMovie(au_movie.get());
        // 这行代码的作用是将当前对象（this）添加到QGraphicsScene中，并返回对应的QGraphicsProxyWidget指针。
        prxy_unique.reset(scene->addWidget(mov_label.get()));
        // 显示视图
        view->show();
        connect();
    }
    void connect() {
        if (au_movie == nullptr){
            qDebug()<<"C_GifItem::_connect(),bug";
            return;
        }
        //使用 "this" 关键字引入它的作用域,
        QObject::connect(au_movie.get(), &QMovie::frameChanged, [this](int frameIndex){
            QSize temp_size = au_movie->currentPixmap().size();
            mov_label->setFixedSize(temp_size);
            prxy_unique->resize(temp_size);
            qDebug() << "Current Frame Index: " << frameIndex;
            qDebug() << "Current Frame size: " << temp_size;
            qDebug() << "label size: " <<mov_label->size();
            qDebug() << "proxy->resize: " <<prxy_unique->size();
            // 下面步骤使 mov_label，prxy_unique 控件保持一致
            // mov_label->setFixedSize(size); 和 prxy_unique->setFixedSize(size); 这两行代码可以让 mov_label 控件和 prxy_unique
            // 控件的大小都设置为动画片段当前帧对应的 QPixmap 对象的大小，但是它们并不能使得 prxy_unique 控件和 mov_label 控件显示的内容一致。
            //这是因为 mov_label 控件是在 QGraphicsProxyWidget 控件的基础上创建出来的，它所显示的是 QMovie 对象，而 prxy_unique 控件所代表
            // 的是 mov_label 控件的 QWidget 子对象。因此，虽然它们的大小一致，但是它们所显示的内容可能不一致。因此还需要通过缩放 prxy_unique
            // 控件来保证其和 mov_label 控件显示的内容一致。
            prxy_unique->setTransform(QTransform::fromScale(1.0, 1.0));  // 先重置缩放比例
            double scale_x = static_cast<double>(mov_label->width()) / temp_size .width();
            double scale_y = static_cast<double>(mov_label->height()) / temp_size .height();
            prxy_unique->setTransform(QTransform::fromScale(scale_x, scale_y));  // 设置缩放比例
        });

    }

};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString path = "C:\\Users\\Administrator\\Desktop\\新建文件夹\\6dd.gif";
//    QGraphicsScene* scene = new QGraphicsScene();
//    QGraphicsView* view = new QGraphicsView(scene);
    // 创建 MainWindow2 对象
    // MainWindow2 window(path, view, scene);    QWidget w;

    // 创建一个 QGraphicsView 和 QGraphicsScene
    QGraphicsView view;
    QGraphicsScene scene(&view);
    view.setScene(&scene);
    QTimer timer;
    timer.start(33); // 33ms 即约等于一秒钟的 30 帧
    // 加载动态图
    QMovie *movie = new QMovie(path);
    movie->start();
    // 将 QMovie 放入 QGraphicsPixmapItem 中
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem();
    item->setPixmap(QPixmap::fromImage(movie->currentImage()));
    // 将 QGraphicsPixmapItem 添加到 QGraphicsScene 中
    scene.addItem(item);
    // 定时器更新 QPixmap

    QObject::connect(&timer, &QTimer::timeout, [&](){
        item->setPixmap(QPixmap::fromImage(movie->currentImage()));
    });


    // 播放 QMovie


    view.resize(640, 480);
    view.show();
    return app.exec();
}
