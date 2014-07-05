#ifndef FFIBER_H
#define FFIBER_H

#include <QGraphicsRectItem>
#include <QBrush>
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
    void toPrint();
    void toView();

private:
    FlogicFiber *logicFiber;
    bool        welded;
    QBrush      oldBrush;
    QGraphicsTextItem *colorText;
};

#endif // FFIBER_H
