#ifndef FDIAGRAM_H
#define FDIAGRAM_H

#include <QGraphicsRectItem>
#include <QVector>
#include <QObject>

class QGraphicsTextItem;
class Fline;
class Fcable;
class Ffiber;
class Fweld;
class FhomeWeld;
class FlogicFiber;
class FMap;
class QComboBox;
class QGraphicsProxyWidget;

class Fdiagram : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Fdiagram();
    QVector<Fcable *>    cables;
    QVector<Fweld *>     welds;
    QVector<FhomeWeld *> homeWelds;
    void addCable(int m, QVector<FlogicFiber *> &fibers, QString s);
    void delCable(Fcable *c);
    void moveCable(Fcable *cable, bool right);
    void addWeld(Ffiber *a, Ffiber *b);
    void addHomeWeld(Ffiber* fiber);
    void delWeld(Fweld *w);
    void delHomeWeld(FhomeWeld *homeWeld);
    enum { Type = UserType + 4 };
    void setAddress(QString s, QString b);
    QMap<QString, int> getOrder() const;
    FMap *getMap() const;
    QString getStreet() const;
    QString getBuild() const;
    void setBuild(QString s);
    void setStreet(QString s);
    void setOrder(QMap<QString, int> &orderMap);
    void setMap(FMap *value);
    void toPrint();
    void toView();
    int  type() const;
signals:
    void addressChanged(QString s);
public slots:
    void prepareAddressChange(int i);

protected:
    void resize();
    void drawWeld(Fweld *weld);
    void drawHomeWeld(FhomeWeld* homeWeld);

private:
    QGraphicsTextItem *address;
    QPointF oldPos;
    FMap    *map;
    QComboBox*      streetCombo;
    QComboBox*      buildCombo;
    QGraphicsProxyWidget* addressProxy;
};

#endif // FDIAGRAM_H
