#ifndef FDIAGRAM_H
#define FDIAGRAM_H

#include <QGraphicsRectItem>
#include <QVector>

class QGraphicsTextItem;
class Fline;
class Fcable;
class Ffiber;
class Fweld;
class FhomeWeld;
class FlogicFiber;
class FMap;

class Fdiagram : public QGraphicsRectItem
{
public:
    Fdiagram();

    QVector<Fcable *> cables; //cables vector
    QVector<Fweld *> welds;
    QVector<FhomeWeld* > homeWelds;
    void addCable(int m, QVector<FlogicFiber *> &fibers, QString s);
    void delCable(Fcable *c);
    void moveCable(Fcable *cable, bool right);
    void addWeld(Ffiber *a, Ffiber *b);
    void addHomeWeld(Ffiber* fiber);
    void delWeld(Fweld *w);
    void delHomeWeld(FhomeWeld *homeWeld);
    enum { Type = UserType + 4 };
    int type() const;
    QString getAddress() const;
    void setAddress(QString value);
    QMap<QString, int> getOrder() const;
    void setOrder(QMap<QString, int> &orderMap);
    FMap *getMap() const;
    void setMap(FMap *value);

protected:
    void resize();
    void drawWeld(Fweld *weld);
    void drawHomeWeld(FhomeWeld* homeWeld);

private:
    QGraphicsTextItem *address;
    QPointF oldPos;
    FMap    *map;
};

#endif // FDIAGRAM_H
