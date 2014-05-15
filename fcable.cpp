#include "fcable.h"
#include "ffiber.h"
#include "fweld.h"
#include "fmodule.h"
#include "fdiagram.h"

#include <QBrush>
#include <QtGlobal>
#include <QGraphicsSceneMouseEvent>

// from ffiber.h
extern QBrush brushes[];

// vert and horiz module margin
const int VERT_MOD_MARG = 4;
const int HORIZ_MOD_MARG = 2;

// vert and horiz fiber margin
const int VERT_FIB_MARG = 2;
const int HORIZ_FIB_MARG = 1;

const int FIB_WIDTH =  Ffiber().rect().width();
const int FIB_HEIGHT = Ffiber().rect().height();

Fcable::Fcable(int mCount, int fCount, QString str, QGraphicsItem *p) : QGraphicsRectItem(p)
{
    m_Counter = 0;
    int mWidth = FIB_WIDTH + HORIZ_FIB_MARG * 2 + 10;
    int mHeight = (FIB_HEIGHT + VERT_FIB_MARG) * fCount;

    // module create
    for (int i = 0; i < mCount; i++)
    {
        int x = HORIZ_MOD_MARG;
        int y = VERT_MOD_MARG + (mHeight + VERT_MOD_MARG) * i;
        
        Fmodule *module = new Fmodule;
        modules << module;
        module->setRect(x, y, mWidth, mHeight);
        module->setParentItem(this);
        module->setBrush(brushes[i]);
        
        // fiber create
        for (int j = 0; j < fCount; j++ )
        {
            int xx = x + HORIZ_FIB_MARG;
            int yy = y + VERT_FIB_MARG + (FIB_HEIGHT + VERT_FIB_MARG) * j;
            fibers << new Ffiber(xx, yy, j, this);
        }
    }

    // Set title cable name
    address = new QGraphicsTextItem(str, this);
    address->setPos(0, -30);
    address->setDefaultTextColor(Qt::darkGray);

    int cHeight = VERT_MOD_MARG + (mHeight + VERT_MOD_MARG) * mCount;
    int w1 = mWidth + HORIZ_MOD_MARG * 2;
    int w2 = address->boundingRect().width();
    int cWidth = qMax(w1, w2);

    setRect(0, 0, cWidth, cHeight);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

int Fcable::type() const
{
    return Type;
}

void Fcable::setAddress(QString value)
{
    address->setPlainText(value);
}

void Fcable::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    bool right = 0;
    int  direction;

    switch (m_Counter) {

    case 0 :
        m_Old = event->pos().x();
        m_Counter++;
        break;

    // Waiting 40 events for smooth moving
    case 40 :
        direction = event->pos().x() - m_Old;
        right = (direction > 0) ? 1 : 0;
        qgraphicsitem_cast<Fdiagram *>(parentItem())->moveCable(this, right);
        m_Counter = 0;
        break;

    default :
        m_Counter++;
        break;
    }

    QGraphicsRectItem::mouseMoveEvent(event);
}
