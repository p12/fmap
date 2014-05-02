#include "fbox.h"
#include "fdiagram.h"


Fbox::Fbox()
{
    setFlags(QGraphicsItem::ItemIsSelectable);
    setRect(0, 0, 30, 30);
    diagram = new Fdiagram(this);
    diagram->setPos(0, 50);
}

void Fbox::setupFilter()
{
    installSceneEventFilter(diagram);
}
