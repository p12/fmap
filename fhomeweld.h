#ifndef FHOMEWELD_H
#define FHOMEWELD_H

#include <QGraphicsPathItem>

class Ffiber;
class Fcable;

class FhomeWeld : public QGraphicsPathItem
{
public:
    FhomeWeld();
    enum { Type = UserType + 6 };
    int type() const
        {
            return Type;
        }
    Ffiber *fiber;
    Fcable *cable;
};

#endif // FHOMEWELD_H
