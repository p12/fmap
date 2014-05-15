#include "fline.h"
#include "fbox.h"
#include <QPen>

Fline::Fline()
{
    setFlags(QGraphicsItem::ItemIsSelectable);
    QPen pen;
    pen.setColor(Qt::gray);
    pen.setWidth(2);
    setPen(pen);
}

int Fline::type() const
{
    return Type;
}
