#include "fweld.h"
#include <QPen>

Fweld::Fweld()
{
    setFlags(QGraphicsItem::ItemIsSelectable);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::gray);
    setPen(pen);
}
