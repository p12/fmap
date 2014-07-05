#ifndef FBOX_H
#define FBOX_H

#include <QGraphicsEllipseItem>
#include <QObject>
class Fdiagram;
class Fline;
class FdiagramStack;
class FtextItem;

class Fbox : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
                    Fbox();
    Fdiagram*       diagram;
    QVector<Fline*> lines;

    enum            { Type = UserType + 1 };
    QString         getAddress() const;
    FdiagramStack*  getStack() const;
    void            deleteLine(Fline *line);
    void            setAddress(QString value);
    void            setStack(FdiagramStack *value);
    int             type() const;

public slots:
    void            updateAddress();

protected:
    QVariant        itemChange(GraphicsItemChange change, const QVariant &value);

private:
    FdiagramStack*  stack;
    FtextItem*      address;
    static int      nextColor;
};

#endif // FBOX_H
