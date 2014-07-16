#ifndef FTEXTITEM_H
#define FTEXTITEM_H

#include <QGraphicsTextItem>

class FtextItem : public QGraphicsTextItem
{
    Q_OBJECT
public:
    FtextItem(QGraphicsItem *parent);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *o, QWidget *w);
signals:
    void textChanged();

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void keyPressEvent(QKeyEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

#endif // FTEXTITEM_H
