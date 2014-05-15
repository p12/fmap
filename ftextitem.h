#ifndef FTEXTITEM_H
#define FTEXTITEM_H

#include <QGraphicsTextItem>

class Fbox;

class FtextItem : public QGraphicsTextItem
{
public:
    FtextItem(Fbox *value);
    Fbox *getBox() const;
    void setBox(Fbox *value);

protected:
    void focusOutEvent(QFocusEvent *event);
private:
    Fbox *box;
};

#endif // FTEXTITEM_H
