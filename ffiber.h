#ifndef FFIBER_H
#define FFIBER_H

#include <QGraphicsRectItem>

class Ffiber : public QGraphicsRectItem
{
public:
    Ffiber();
    Ffiber(int x, int y, int color, QGraphicsItem *p);
    enum { Type = UserType + 3 };
    int type() const
        {
            return Type;
        }
};

#endif // FFIBER_H
