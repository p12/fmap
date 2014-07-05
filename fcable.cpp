#include "fcable.h"
#include "ffiber.h"
#include "fweld.h"
#include "fmodule.h"
#include "fdiagram.h"
#include "flogicfiber.h"

#include <QBrush>
#include <QtGlobal>
#include <QGraphicsSceneMouseEvent>

// from ffiber.h
extern QBrush brushes[];

// header size
const int CABLE_HEADER = 0;
const int MODULE_HEADER = 12;
const int MODULE_FOOTER = 7;

// vert and horiz module margin
const int VERT_MOD_MARG = 0;
const int HORIZ_MOD_MARG = 0;

// vert and horiz fiber margin
const int VERT_FIB_MARG = 0;
const int HORIZ_FIB_MARG = 0;

const int FIB_WIDTH =  Ffiber().rect().width();
const int FIB_HEIGHT = Ffiber().rect().height();

Fcable::Fcable(int mCount, QVector<FlogicFiber *> &indexes, QString str, QGraphicsItem *p) : QGraphicsRectItem(p)
{
    Counter = 0;
    int fCount = indexes.size() / mCount;
    int mHeight = MODULE_HEADER + MODULE_FOOTER +
                    (FIB_HEIGHT + VERT_FIB_MARG) * fCount;
    int mWidth = FIB_WIDTH + HORIZ_FIB_MARG * 2 + 10;

    // module create
    for (int i = 0; i < mCount; i++)
    {
        int x = HORIZ_MOD_MARG;
        int y = CABLE_HEADER + (mHeight + VERT_MOD_MARG) * i;
        
        Fmodule *module = new Fmodule(i);
        modules << module;
        module->setRect(0, 0, mWidth, mHeight);
        module->setPos(x, y);
        module->setParentItem(this);
        
        // fiber create
        for (int j = 0; j < fCount; j++)
        {
            int xx = x + HORIZ_FIB_MARG;
            int yy = y + MODULE_HEADER + (FIB_HEIGHT + VERT_FIB_MARG) * j;
            fibers << new Ffiber(xx, yy, j, this);
            fibers.last()->setLogicFiber(indexes[i * fCount + j]);
            indexes[i * fCount + j]->fibers << fibers.last();
        }
    }

    // Set title cable name
    address = new QGraphicsTextItem(str, this);
    address->setPos(0, -30);
    address->setDefaultTextColor(Qt::darkGray);

    // Calculate cable size
    int cHeight = CABLE_HEADER + (mHeight + VERT_MOD_MARG) * mCount;
    int w1 = mWidth + HORIZ_MOD_MARG * 2 + 40;
    int w2 = address->boundingRect().width();
    int cWidth = qMax(w1, w2);

    setRect(0, 0, cWidth, cHeight);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

int Fcable::type() const
{
    return Type;
}

QString Fcable::getAddress() const
{
    return address->toPlainText();
}

void Fcable::toPrint()
{
    oldBrush = brush();
    setBrush(Qt::white);
    foreach (Fmodule *module, modules) {
        module->toPrint();
    }
    foreach (Ffiber *fiber, fibers) {
        fiber->toPrint();
    }
}

void Fcable::toView()
{
    setBrush(oldBrush);
    foreach (Fmodule *module, modules) {
        module->toView();
    }
    foreach (Ffiber *fiber, fibers) {
        fiber->toView();
    }
}

void Fcable::setAddress(QString value)
{
    address->setPlainText(value);
}

void Fcable::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    bool right = 0;
    int  direction;

    switch (Counter) {

    case 0 :
        Old = event->pos().x();
        Counter++;
        break;

    // Waiting 40 events for smooth moving
    case 40 :
        direction = event->pos().x() - Old;
        right = (direction > 0) ? 1 : 0;
        qgraphicsitem_cast<Fdiagram *>(parentItem())->moveCable(this, right);
        Counter = 0;
        break;

    default :
        Counter++;
        break;
    }

    QGraphicsRectItem::mouseMoveEvent(event);
}
