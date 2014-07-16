#ifndef FLINE_H
#define FLINE_H

#include <QGraphicsPathItem>
#include <QObject>

class Fbox;
class Fcable;

class Fline : public QObject, public QGraphicsPathItem
{
    Q_OBJECT
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

    uint getLength() const;
    void setLength(uint value);
public slots:
    void updateLength();

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    QPointF begin, end;
    QVector<QPointF> points;
    QVector<QGraphicsEllipseItem *> ellipses;
    QVector<QGraphicsEllipseItem *> moveEllipses;
    QGraphicsTextItem *lengthText;
    void redraw();
};

#endif // FLINE_H
