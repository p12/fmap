#include "fhomeweld.h"
#include <QPen>
#include <QPainterPath>

FhomeWeld::FhomeWeld()
{
    setFlag(QGraphicsItem::ItemIsSelectable);

    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::darkGray);
    setPen(pen);

    QPainterPath path;
    path.lineTo(20, 0);
    path.addEllipse(20, -6, 12, 12);
    setPath(path);
}
