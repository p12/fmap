#include "ffiber.h"

#include <QBrush>
#include <QVector>

const QColor red    ("#ffa1a1");
const QColor green  ("#caddac");
const QColor blue   ("#9eb9ff");
const QColor yellow ("#faebc3");
const QColor brown  ("#dfa654");
const QColor black  ("#6f6b66");
const QColor natural("#dfdedb");
const QColor white  ("#f2f2f1");

QBrush brushes[] = {
    QBrush(red),
    QBrush(green),
    QBrush(blue),
    QBrush(yellow),
    QBrush(brown),
    QBrush(black),
    QBrush(natural),
    QBrush(white)
};

Ffiber::Ffiber()
{
    setRect(0, 0, 45, 5);
}

Ffiber::Ffiber(int x, int y, int color, QGraphicsItem *p) : QGraphicsRectItem(p)
{
    setRect(0, 0, 45, 5);
    setBrush(brushes[color]);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setPos(x, y);
}
FlogicFiber *Ffiber::getLogicFiber() const
{
    return logicFiber;
}

void Ffiber::setLogicFiber(FlogicFiber *value)
{
    logicFiber = value;
}
