#ifndef FLINE_H
#define FLINE_H

#include <QGraphicsLineItem>

class Fbox;
class Fcable;

class Fline : public QGraphicsLineItem
{
public:
    Fline();
    Fbox *box1;
    Fbox *box2;
    Fcable *cable1;
    Fcable *cable2;
    int moduleCount, fiberCount;     // count modules and fibers
    enum { Type = UserType + 2 };
    int type() const
        {
            return Type;
        }
};

#endif // FLINE_H
