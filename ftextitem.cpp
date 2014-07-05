#include "ftextitem.h"
#include <QKeyEvent>
#include <QPainter>

FtextItem::FtextItem(QGraphicsItem *parent)
{
    setParentItem(parent);
}

void FtextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *o, QWidget *w)
{
    painter->setBrush(Qt::white);
    painter->drawRect(boundingRect());
    QGraphicsTextItem::paint(painter, o, w);
}

void FtextItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setTextInteractionFlags(Qt::TextEditorInteraction);
}

void FtextItem::focusOutEvent(QFocusEvent *event)
{
    setTextInteractionFlags(Qt::NoTextInteraction);
    emit textChanged();
    QGraphicsTextItem::focusOutEvent(event);
}

void FtextItem::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
    {
        event->accept();
        setEnabled(0);
        setEnabled(1);
        emit textChanged();
    }
    else
        QGraphicsTextItem::keyPressEvent(event);
}

QVariant FtextItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemVisibleChange){
        setEnabled(0);
        setEnabled(1);
        emit textChanged();
    }
    return QGraphicsItem::itemChange(change, value);
}
