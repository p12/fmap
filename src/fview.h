#ifndef FVIEW_H
#define FVIEW_H

#include <QGraphicsView>

class Fview : public QGraphicsView
{
public:
    Fview();
protected:
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    QPointF mLast;
};

#endif // FVIEW_H
