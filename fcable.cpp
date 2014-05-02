#include "fcable.h"
#include "ffiber.h"
#include "fweld.h"
#include "fmodule.h"

#include <QBrush>

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
    QGraphicsTextItem *t = new QGraphicsTextItem(str, this);
    t->setPos(0, -30);
    t->setTextInteractionFlags(Qt::TextEditorInteraction);
    t->setDefaultTextColor(Qt::darkGray);

    int cHeight = VERT_MOD_MARG + (mHeight + VERT_MOD_MARG) * mCount;
    int w1 = mWidth + HORIZ_MOD_MARG * 2;
    int w2 = t->boundingRect().width();
    int cWidth = (w1 > w2) ? w1 : w2;

    setRect(0, 0, cWidth, cHeight);
    setFlag(QGraphicsItem::ItemIsSelectable);
}
