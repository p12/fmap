#ifndef FCABLE_H
#define FCABLE_H

#include <QGraphicsRectItem>

class Fcable : public QGraphicsRectItem
{
public:
    Fcable(int mCount, int fCount, QString str, QGraphicsItem *p);
    QVector<QGraphicsRectItem *> modV;
    QVector<QGraphicsRectItem *> fibV;
};

#endif // FCABLE_H
