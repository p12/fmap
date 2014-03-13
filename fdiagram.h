#ifndef FDIAGRAM_H
#define FDIAGRAM_H

#include <QGraphicsRectItem>
#include <QVector>
class QLineEdit;

class Fdiagram : public QGraphicsRectItem
{
public:
    Fdiagram();
    QLineEdit * addr;
    QVector<QGraphicsRectItem *> cVec; //cables vector
    void addCable(QString s);
protected:
    virtual bool sceneEventFilter(QGraphicsItem *watched, QEvent *event);
};

#endif // FDIAGRAM_H
