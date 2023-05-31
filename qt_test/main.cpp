#include <QtWidgets>

class ImageViewer : public QGraphicsView
{
public:
    ImageViewer(QWidget *parent = nullptr)
            : QGraphicsView(parent)
    {
        scene_ = new QGraphicsScene(this);
        setScene(scene_);

        // 加载图片
        QPixmap pixmap("C:\\Users\\Administrator\\Desktop\\myimage\\2.tif");

        // 根据窗口大小和图片大小计算缩放比例
        qreal scaleRatio = qMin(qreal(1.0), qMin(qreal(width()) / pixmap.width(), qreal(height()) / pixmap.height()));

        // 创建图元并添加到场景中
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap.scaled(pixmap.width() * scaleRatio, pixmap.height() * scaleRatio));
        scene_ = new QGraphicsScene(this);
        scene_->addItem(item);
        setScene(scene_);
        // 将场景大小设置为视口大小
        setSceneRect(0, 0, item->boundingRect().width(), item->boundingRect().height());
        // 设置窗口大小为固定的 (500, 500)
        setFixedSize(500, 500);
        // 设置平滑滚动和抗锯齿选项
        setRenderHint(QPainter::SmoothPixmapTransform, true);
        setRenderHint(QPainter::Antialiasing, true);
        setRenderHint(QPainter::HighQualityAntialiasing, true);
        // 设置视口模式和对齐方式
        setDragMode(QGraphicsView::ScrollHandDrag);
        setAlignment(Qt::AlignCenter);
        // 安装事件过滤器来捕获鼠标滚轮事件
        viewport()->installEventFilter(this);
    }

protected:
    bool eventFilter(QObject *watched, QEvent *event) override
    {
        if (watched == viewport() && event->type() == QEvent::Wheel)
        {
            // 阻止滚轮事件传递到父对象，避免控件滚动
            event->accept();
            // 缩放因子为 1.1，可以根据需要进行调整
            qreal scaleFactor = 1.1;
            QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);
            // 启用高质量渲染提示
            setRenderHint(QPainter::HighQualityAntialiasing);
            if (wheelEvent->delta() > 0)
            {
                scale(scaleFactor, scaleFactor);
                setRenderHint(QPainter::SmoothPixmapTransform, true);
            }
            else
            {
                scale(1 / scaleFactor, 1 / scaleFactor);
                setRenderHint(QPainter::SmoothPixmapTransform, false);
            }

            return true;
        }

        return false;
    }

private:
    QGraphicsScene *scene_;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ImageViewer viewer;
    viewer.show();

    return app.exec();
}
