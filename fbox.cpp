#include "fbox.h"
#include "fdiagram.h"
#include "fdiagramstack.h"
#include "ftextitem.h"
#include "fline.h"
#include "fcable.h"

#include <QEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtGlobal>

const QColor colors[] = {
("#ffa1a1"),
("#caddac"),
("#9eb9ff"),
("#faebc3"),
("#dfa654"),
("#6f6b66"),
("#dfdedb"),
("#f2f2f1"),
};

Fbox::Fbox()
{
    setFlags(QGraphicsItem::ItemIsSelectable);
    setRect(-15, -15, 30, 30);
    diagram = new Fdiagram;
    address = new FtextItem(this);
}

int Fbox::type() const
{
    return Type;
}

QVariant Fbox::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemSelectedChange)
    {
        QPen pen(Qt::gray);
        pen.setWidth(2);
        bool selected = value.toBool();
        if (selected)
        {
            stack->push(diagram);
            pen.setWidth(4);
            for (int i = 0; i < lines.size(); i++)
            {
                pen.setColor(colors[i]);
                lines[i]->setPen(pen);
                diagram->cables[i]->setBrush(colors[i]);
            }
        }
        else
        {
            stack->pop(diagram);
            foreach (Fline* l, lines)
                l->setPen(pen);
        }
    }

    return QGraphicsItem::itemChange(change, value);
}

QString Fbox::getAddress() const
{
    return address->toPlainText();
}

void Fbox::setAddress(QString value)
{
    address->setPlainText(value);
    diagram->setAddress(value);
    foreach (Fline *line, lines) {
        if (line->box1 == this)
            line->cable2->setAddress(value);
        else if (line->box2 == this) {
            line->cable1->setAddress(value);
        }
    }
}

FdiagramStack *Fbox::getStack() const
{
    return stack;
}

void Fbox::setStack(FdiagramStack *value)
{
    stack = value;
}

