#ifndef FWELD_H
#define FWELD_H

#include <QGraphicsLineItem>
class Fcable;
class Ffiber;

class Fweld : public QGraphicsLineItem
{
public:
    Fweld();
    Fcable *cable1;
    Fcable *cable2;
    Ffiber *fiber1;
    Ffiber *fiber2;
    enum { Type = UserType + 5 };
    int type() const
        {
            return Type;
        }
};

#endif // FWELD_H
