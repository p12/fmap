#include "fdiagram.h"
#include <QtGui>

const int MRGN = 25;
Fdiagram::Fdiagram()
{
    setVisible(0);
    setRect(0, 0, 150, 250);

    // Address of box
    addr = new QLineEdit;
    addr->setFixedWidth(100);
    QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget(this);
    proxy->setWidget(addr);
    proxy->setPos(25, 5);
}

void Fdiagram::addCable(QString s)
{
    QRectF r(0, 0, 70, 100);
    cVec << new QGraphicsRectItem(r, this);

    // check Fdiagram width
    int w = MRGN;
    foreach (QGraphicsRectItem *r, cVec)
        w += r->rect().width() + MRGN;
    if (rect().width() < w)
    {
        setRect(0, 0, w, rect().height());
        addr->setFixedWidth(w - 2 * MRGN);
    }

    // set position per cable count
    int x, y, bW, cW;
    bW = rect().width();     // Box width
    y = (rect().height() - cVec[0]->rect().height()) / 2;
    x = (bW  - cVec[0]->rect().width()) / 2;

    switch (cVec.size())
    {
    case 1:
        cVec[0]->setPos(x, y);
        break;
    case 2:
        cVec[0]->setPos(MRGN, y);
        cW = cVec[1]->rect().width();   // Cable width
        cVec[1]->setPos(bW - MRGN - cW, y);
        break;
    case 3:
        cVec[0]->setPos(x, y);
        cVec[1]->setPos(MRGN, y);
        cW = cVec[2]->rect().width();    // Cable width
        cVec[2]->setPos(bW - MRGN - cW, y);
        break;
    }
}

bool Fdiagram::sceneEventFilter(QGraphicsItem *watched, QEvent *event)
{
    if (event->type() == QEvent::GraphicsSceneMousePress)
        if(isVisible())
            setVisible(0);
        else
            setVisible(1);

    return false;
}
