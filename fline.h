#ifndef FLINE_H
#define FLINE_H

#include <QGraphicsPathItem>

class Fbox;
class Fcable;

class Fline : public QGraphicsPathItem
{
public:
    Fline(QPointF p1, QPointF p2);
    Fbox *box1;
    Fbox *box2;
    Fcable *cable1;
    Fcable *cable2;
    int moduleCount, fiberCount;     // count modules and fibers
    enum { Type = UserType + 2 };
    int type() const;

    QVector<QPointF> getPoints() const;
    void setPoints(const QVector<QPointF> &value);

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    QPointF begin, end;
    QVector<QPointF> points;
    QVector<QGraphicsEllipseItem *> ellipses;
    QVector<QGraphicsEllipseItem *> moveEllipses;
    void redraw();
};

#endif // FLINE_H
