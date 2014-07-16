#include "fbox.h"
#include "fdiagram.h"
#include "fdiagramstack.h"
#include "ftextitem.h"
#include "fline.h"
#include "fcable.h"
#include "fcolors.h"

#include <QtGui>

int Fbox::nextColor = 0;

Fbox::Fbox()
{
    setFlags(QGraphicsItem::ItemIsSelectable);
    setBrush(Qt::white);
    setZValue(10);
    setRect(-15, -15, 30, 30);
    diagram = new Fdiagram;
    connect(diagram, SIGNAL(addressChanged(QString)), SLOT(updateAddress(QString)));
    address = new QGraphicsTextItem("Street 11", this);
    address->setY(35);
}

int Fbox::type() const
{
    return Type;
}

void Fbox::updateAddress(QString s)
{
    address->setPlainText(s);
    foreach (Fline *line, lines) {
        if (line->box1 == this)
            line->cable2->setAddress(s);
        else if (line->box2 == this) {
            line->cable1->setAddress(s);
        }
    }
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
            foreach (Fline *line, lines) {
                pen.setColor(colors[nextColor]);
                line->setPen(pen);
                line->cable1->setBrush(colors[nextColor]);
                line->cable2->setBrush(colors[nextColor++]);
            }
            if (nextColor >= 40)
                nextColor = 0;
        }
        else
        {
            stack->pop(diagram);
            foreach (Fline* l, lines)
                l->setPen(pen);
            if (scene()->selectedItems().size() == 0)
                nextColor = 0;
        }
    }

    return QGraphicsItem::itemChange(change, value);
}

QString Fbox::getAddress() const
{
    return address->toPlainText();
}

QString Fbox::getBuild() const
{
    return diagram->getBuild();
}

QString Fbox::getStreet() const
{
    return diagram->getStreet();
}

void Fbox::setAddress(QString b, QString s)
{
    diagram->setAddress(s, b);
}

FdiagramStack *Fbox::getStack() const
{
    return stack;
}

void Fbox::addLine(Fline *line)
{

}

void Fbox::deleteLine(Fline *line)
{
    int pos = lines.indexOf(line);
    if (pos >= 0)
        lines.remove(pos);
}

void Fbox::setStack(FdiagramStack *value)
{
    stack = value;
}

