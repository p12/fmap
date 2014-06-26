#ifndef FFIBER_H
#define FFIBER_H

#include <QGraphicsRectItem>
class FlogicFiber;

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

    FlogicFiber *getLogicFiber() const;
    void setLogicFiber(FlogicFiber *value);

private:
    FlogicFiber *logicFiber;
};

#endif // FFIBER_H
