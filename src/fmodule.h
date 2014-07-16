#ifndef FMODULE_H
#define FMODULE_H

#include <QGraphicsRectItem>
#include <QBrush>

class Fmodule : public QGraphicsRectItem
{
public:
    Fmodule(int pos);
    enum { Type = UserType + 8 };
    int type() const;
    void toPrint();
    void toView();
private:
    QBrush oldBrush;
    QGraphicsTextItem *colorText;
};

#endif // FMODULE_H
