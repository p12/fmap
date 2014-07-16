#ifndef FBOX_H
#define FBOX_H

#include <QGraphicsEllipseItem>
#include <QObject>
class Fdiagram;
class Fline;
class FdiagramStack;
class QGraphicsTextItem;

class Fbox : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
                    Fbox();
    Fdiagram*       diagram;
    QVector<Fline*> lines;

    enum            { Type = UserType + 1 };
    QString         getAddress() const;
    QString         getBuild() const;
    QVector<Fline*> getLines() const;
    QString         getStreet() const;
    FdiagramStack*  getStack() const;
    void            addLine(Fline *line);
    void            deleteLine(Fline *line);
    void            setAddress(QString b, QString s);
    void            setStack(FdiagramStack *value);
    int             type() const;

public slots:
    void            updateAddress(QString s);

protected:
    QVariant        itemChange(GraphicsItemChange change, const QVariant &value);

private:
    FdiagramStack*  stack;
    QGraphicsTextItem* address;
    static int      nextColor;
};

#endif // FBOX_H
