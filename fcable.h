#ifndef FCABLE_H
#define FCABLE_H

#include <QGraphicsRectItem>
class Ffiber;
class Fweld;
class Fmodule;
class QGraphicsTextItem;
class FlogicFiber;

class Fcable : public QGraphicsRectItem
{
public:
    Fcable(int mCount, QVector<FlogicFiber *> &indexes, QString str, QGraphicsItem *p);
    QVector<Fmodule *> modules;
    QVector<Ffiber *> fibers;
    enum { Type = UserType + 7 };
    int  type() const;
    void setAddress(QString value);
    QString getAddress() const;

private:
    QGraphicsTextItem *address;
    int  Old;
    int  Counter;
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // FCABLE_H
