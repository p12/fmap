#ifndef FCABLE_H
#define FCABLE_H

#include <QGraphicsRectItem>
class Ffiber;
class Fweld;
class Fmodule;
class QGraphicsTextItem;

class Fcable : public QGraphicsRectItem
{
public:
    Fcable(int mCount, int fCount, QString str, QGraphicsItem *p);
    QVector<Fmodule *> modules;
    QVector<Ffiber *> fibers;
    enum { Type = UserType + 7 };
    int  type() const;
    void setAddress(QString value);
private:
    QGraphicsTextItem *address;
    int  m_Old;
    int  m_Counter;
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // FCABLE_H
