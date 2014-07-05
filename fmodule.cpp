#include "fmodule.h"
#include "fcolors.h"

Fmodule::Fmodule(int pos)
{
    setBrush(brushes[pos]);
    setFlag(QGraphicsItem::ItemIsSelectable);
    colorText = new QGraphicsTextItem(textColors[pos], this);
    colorText->setPos(0, -8);
    colorText->hide();
}

int Fmodule::type() const
{
    return Type;
}

void Fmodule::toPrint()
{
    oldBrush = brush();
    setBrush(Qt::white);
    colorText->show();
}

void Fmodule::toView()
{
    setBrush(oldBrush);
    colorText->hide();
}
