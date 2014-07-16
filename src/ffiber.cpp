#include "ffiber.h"

#include "fcolors.h"
#include <QVector>

const int WIDTH = 82;
const int HEIGHT = 12;

Ffiber::Ffiber()
{
    setRect(0, 0, WIDTH, HEIGHT);
}

Ffiber::Ffiber(int x, int y, int color, QGraphicsItem *p) : QGraphicsRectItem(p)
{
    setRect(0, 0, WIDTH, HEIGHT);
    setBrush(brushes[color]);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setPos(x, y);
    welded = 0;
    colorText = new QGraphicsTextItem(textColors[color], this);
    colorText->setPos(10, -8);
    colorText->hide();
}
FlogicFiber *Ffiber::getLogicFiber() const
{
    return logicFiber;
}

void Ffiber::setLogicFiber(FlogicFiber *value)
{
    logicFiber = value;
}
bool Ffiber::isWelded() const
{
    return welded;
}

void Ffiber::setWelded(bool value)
{
    welded = value;
}

void Ffiber::toPrint()
{
    oldBrush = brush();
    setBrush(Qt::white);
    colorText->show();
}

void Ffiber::toView()
{
    setBrush(oldBrush);
    colorText->hide();
}

