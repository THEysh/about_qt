#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMovie>
#include <QLabel>
#include <QTimeLine>
#include "QGraphicsItem"
#include "qdebug.h"
#include "QGraphicsProxyWidget"
#include "QObject"

class MovieItem : public QObject, public QGraphicsItem
{
public:
    MovieItem(const QString& fileName, int width = 0, int height = 0, QGraphicsItem* parent = nullptr)
            : QObject(),
            QGraphicsItem(parent),
            m_movie(new QMovie(fileName, QByteArray(), this)),
            m_transform()
    {
        if (width != 0 && height != 0) {
            m_movie->setScaledSize(QSize(width, height));
        }
        qDebug()<<m_movie->speed();
        m_movie->setSpeed(1);
        m_movie->start();
        qDebug()<<m_movie->speed();

    }

    QRectF boundingRect() const override
    {
        return QRectF(0, 0, m_movie->currentPixmap().width(), m_movie->currentPixmap().height());
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override
    {
        painter->setTransform(m_transform);
        painter->drawPixmap(0, 0, m_movie->currentPixmap());
        m_movie->jumpToNextFrame();
        update();
    }

    int type() const override
    {
        return UserType + 1;
    }

    void setScale(qreal sx, qreal sy)
    {
        m_transform.scale(sx, sy);
    }

    void setRotation(qreal angle)
    {
        m_transform.rotate(angle);
    }


private:
    QMovie* m_movie;
    QTransform m_transform;
};

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
            qDebug() << "Current Frame Index: " << frameIndex;
            qDebug() << "Current Frame size: " << movie->currentPixmap().size();
            this->setFixedSize(movie->currentPixmap().size());
            qDebug() << "label size: " <<this->size();
            proxy->resize(movie->currentPixmap().size());
            qDebug() << "proxy->resize: " <<proxy->size();
        });
        connect(movie, &QMovie::resized, [](const QSize& size){
            qDebug() << "Animation Resized to " << size;
        });
        connect(movie, &QMovie::started, [movie](){
            qDebug() << "Animation started " ;
        });

    }

};
//
//class MainWindow2 : public QLabel {
//Q_OBJECT
//
//public:
//    MainWindow2(QWidget *parent = nullptr) : QLabel(parent) {
//        setWindowTitle("GIF Animation");
//        setFixedSize(400, 400);
//        setAlignment(Qt::AlignCenter);
//        QMovie *movie = new QMovie("C:\\Users\\Administrator\\Desktop\\新建文件夹\\6dd.gif", QByteArray(), this);
//        connect(movie, SIGNAL(frameChanged(int)), this, SLOT(onFrameChanged(int)));
//        connect(movie, SIGNAL(stateChanged(QMovie::MovieState)), this, SLOT(onStateChanged(QMovie::MovieState)));
//        connect(movie, SIGNAL(finished()), this, SLOT(onFinished()));
//        connect(movie, SIGNAL(resized(const QSize&)), this, SLOT(onResized(const QSize&)));
//        setMovie(movie);
//        movie->start();
//    }
//
//private slots:
//    void onFrameChanged(int frameIndex) {
//        qDebug() << "Current Frame Index: " << frameIndex;
//    }
//
//    void onStateChanged(QMovie::MovieState state) {
//        qDebug() << "Animation State Changed:" << state;
//    }
//
//    void onFinished() {
//        qDebug() << "Animation Finished";
//    }
//
//    void onResized(const QSize &size) {
//        qDebug() << "Animation Resized to " << size;
//    }
//};



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.show();
    return app.exec();
}
