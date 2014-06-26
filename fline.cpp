#include "fline.h"
#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

Fline::Fline(QPointF p1, QPointF p2) :
    begin(p1), end(p2)
{
    points << p1 << p2;
    ellipses << new QGraphicsEllipseItem
             << new QGraphicsEllipseItem;
    moveEllipses << new QGraphicsEllipseItem
                 << new QGraphicsEllipseItem;
    setFlags(QGraphicsItem::ItemIsSelectable);

    QPen pen;
    pen.setColor(Qt::gray);
    pen.setWidth(2);
    setPen(pen);

    redraw();
}

int Fline::type() const
{
    return Type;
}

void Fline::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF p = event->pos();
    QPointF intersect;
    QPointF ten(5, 5);
    QLineF  line(p - ten, p + ten);

    for (int i = 1; i < points.size(); i++)
    {
        if (QLineF(points[i - 1], points[i]).intersect(line, &intersect) == QLineF::BoundedIntersection){
            points.insert(i, p);
            QGraphicsEllipseItem *e = new QGraphicsEllipseItem(p.x() - 4, p.y() - 4, 8, 8, this);
            ellipses.insert(i, e);
            moveEllipses.insert(i, new QGraphicsEllipseItem(p.x() - 20, p.y() - 20, 40, 40));
            e->setBrush(Qt::gray);
            redraw();
            break;
        }
    }
}

void Fline::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF p = event->pos();
    QGraphicsEllipseItem e(p.x() - 5, p.y() - 5, 10, 10);
    for (int i = 1; i < ellipses.size(); i++)
        if (moveEllipses[i]->contains(p))
        {
            ellipses[i]->setRect(p.x() - 4, p.y() - 4, 8, 8);
            moveEllipses[i]->setRect(p.x() - 20, p.y() - 20, 40, 40);
            points[i] = p;
            redraw();
            break;
        }
}
QVector<QPointF> Fline::getPoints() const
{
    return points;
}

void Fline::setPoints(const QVector<QPointF> &value)
{
    points = value;
    foreach (QGraphicsEllipseItem *e, ellipses)
        delete e;
    foreach (QGraphicsEllipseItem *m, moveEllipses)
        delete m;

    ellipses.clear();
    moveEllipses.clear();
    ellipses << new QGraphicsEllipseItem;
    moveEllipses << new QGraphicsEllipseItem;

    for (int i = 1; i < points.size() - 1; i++) {
        ellipses << new QGraphicsEllipseItem(points[i].x() - 4, points[i].y() - 4, 8, 8, this);
        moveEllipses << new QGraphicsEllipseItem(points[i].x() - 20, points[i].y() - 20, 40, 40);
        ellipses.last()->setBrush(Qt::gray);
    }
    ellipses << new QGraphicsEllipseItem;
    moveEllipses << new QGraphicsEllipseItem;

    redraw();
}


void Fline::redraw()
{
    QPainterPath path(begin);
    for (int i = 1; i < points.size(); i++)
        path.lineTo(points[i]);
    setPath(path);
}
