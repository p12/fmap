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
    
    FlogicFiber *getLogicFiber() const;
    bool isWelded() const;
    void setLogicFiber(FlogicFiber *value);
    void setWelded(bool value);
    int  type() const { return Type; }

private:
    FlogicFiber *logicFiber;
    bool        isWelded;
};

#endif // FFIBER_H
