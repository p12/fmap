#include "fhomeweld.h"
#include <QPen>
#include <QPainterPath>

FhomeWeld::FhomeWeld()
{
    setFlag(QGraphicsItem::ItemIsSelectable);

    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::gray);
    setPen(pen);

    QPainterPath path;
    path.lineTo(20, 0);
    path.lineTo(20, 80);
    setPath(path);
}
