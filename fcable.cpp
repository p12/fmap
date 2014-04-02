#include "fcable.h"

const int VERT_MOD_MARG = 4;      // vert and horiz module margin
const int HORIZ_MOD_MARG = 5;
const int VERT_FIB_MARG = 2;      // vert and horiz fiber margin
const int HORIZ_FIB_MARG = 3;

const int FIB_WIDTH = 45;
const int FIB_HEIGHT = 5;

Fcable::Fcable(int mCount, int fCount, QString str, QGraphicsItem *p) : QGraphicsRectItem(p)
{
    int mWidth = FIB_WIDTH + HORIZ_FIB_MARG * 2;
    int mHeight = (FIB_HEIGHT + VERT_FIB_MARG) * fCount;

    for (int i = 0; i < mCount; i++)       // module create
    {
        int x = HORIZ_MOD_MARG;
        int y = VERT_MOD_MARG + (mHeight + VERT_MOD_MARG) * i;
        
        modV << new QGraphicsRectItem(x, y, mWidth, mHeight, this);
        
        for (int j = 0; j < fCount; j++ )  // fiber create
        {
            int xx = x + HORIZ_FIB_MARG;
            int yy = y + VERT_FIB_MARG + (FIB_HEIGHT + VERT_FIB_MARG) * j;
            fibV << new QGraphicsRectItem(xx, yy, FIB_WIDTH, FIB_HEIGHT, this);
        }
    }
    QGraphicsTextItem *t = new QGraphicsTextItem(str, this);        // Set title cable name
    t->setPos(0, -30);

    int cHeight = VERT_MOD_MARG + (mHeight + VERT_MOD_MARG) * mCount;
    int w1 = mWidth + HORIZ_MOD_MARG * 2;
    int w2 = t->boundingRect().width();
    int cWidth = (w1 > w2) ? w1 : w2;

    setRect(0, 0, cWidth, cHeight);
}
