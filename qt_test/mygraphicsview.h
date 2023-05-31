#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>

class MyGraphicsView : public QGraphicsView
{
public:
    MyGraphicsView(QWidget *parent = nullptr);

protected:
    void wheelEvent(QWheelEvent *event) override;
};

#endif // MYGRAPHICSVIEW_H
