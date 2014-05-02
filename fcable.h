#ifndef FCABLE_H
#define FCABLE_H

#include <QGraphicsRectItem>
class Ffiber;
class Fweld;
class Fmodule;

class Fcable : public QGraphicsRectItem
{
public:
    Fcable(int mCount, int fCount, QString str, QGraphicsItem *p);
    QVector<Fmodule *> modules;
    QVector<Ffiber *> fibers;
    enum { Type = UserType + 7 };
    int type() const
        {
            return Type;
        }
};

#endif // FCABLE_H
