#ifndef FDIAGRAM_H
#define FDIAGRAM_H

#include <QGraphicsRectItem>

class Fdiagram : public QGraphicsRectItem
{
public:
    Fdiagram();
protected:
    virtual bool sceneEventFilter(QGraphicsItem *watched, QEvent *event);
};

#endif // FDIAGRAM_H
