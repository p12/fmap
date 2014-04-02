#ifndef FLINE_H
#define FLINE_H

#include <QGraphicsLineItem>

class Fbox;
class Fcable;

class Fline : public QGraphicsLineItem
{
public:
    Fline();
    Fbox *b1;
    Fbox *b2;
    Fcable *c1;
    Fcable *c2;
    int mc, fc;     // count modules and fibers
    enum { Type = UserType + 2 };
    int type() const
        {
            return Type;
        }
};

#endif // FLINE_H
