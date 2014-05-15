#include "ftextitem.h"
#include "fbox.h"

FtextItem::FtextItem(Fbox *value)
{
    box = value;
    setParentItem(value);
    setPlainText("Street 11");
    setTextInteractionFlags(Qt::TextEditorInteraction);
    setY(35);
}

void FtextItem::focusOutEvent(QFocusEvent *event)
{
    box->setAddress(toPlainText());
    QGraphicsTextItem::focusOutEvent(event);
}

Fbox *FtextItem::getBox() const
{
    return box;
}

void FtextItem::setBox(Fbox *value)
{
    box = value;
}

