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
    ("#ffa1a1"),  // red
    ("#ffd6a1"),  // green
    ("#faebc3"),  // blue
    ("#fff3a1"),  // yellow
    ("#dfffa1"),  // brown
    ("#caddac"),  // gray
    ("#acffa1"),  // lightblue
    ("#a1ffc2"),  // redblue
    ("#a1ffea"),  // darkyellow
    ("#a1e1ff"),  // darkbrown
    ("#9eb9ff"),  // lightred
    ("#a1aaff"),  // red
    ("#b5a1ff"),  // green
    ("#e1a1ff"),  // blue
    ("#ffa1ee"),  // yellow
    ("#ddacac"),  // brown
    ("#b2ddac"),  // gray
    ("#acddd4"),  // lightblue
    ("#cfacdd"),  // redblue

    ("#ffa1a1"),  // red
    ("#ffd6a1"),  // green
    ("#faebc3"),  // blue
    ("#fff3a1"),  // yellow
    ("#dfffa1"),  // brown
    ("#caddac"),  // gray
    ("#acffa1"),  // lightblue
    ("#a1ffc2"),  // redblue
    ("#a1ffea"),  // darkyellow
    ("#a1e1ff"),  // darkbrown
    ("#9eb9ff"),  // lightred
    ("#a1aaff"),  // red
    ("#b5a1ff"),  // green
    ("#e1a1ff"),  // blue
    ("#ffa1ee"),  // yellow
    ("#ddacac"),  // brown
    ("#b2ddac"),  // gray
    ("#acddd4"),  // lightblue
    ("#cfacdd"),  // redblue

    ("#ffa1a1"),  // red
    ("#ffd6a1"),  // green
    ("#faebc3"),  // blue
    ("#fff3a1"),  // yellow
    ("#dfffa1"),  // brown
    ("#caddac"),  // gray
    ("#acffa1"),  // lightblue
    ("#a1ffc2"),  // redblue
    ("#a1ffea"),  // darkyellow
    ("#a1e1ff"),  // darkbrown
    ("#9eb9ff"),  // lightred
    ("#a1aaff"),  // red
    ("#b5a1ff"),  // green
    ("#e1a1ff"),  // blue
    ("#ffa1ee"),  // yellow
    ("#ddacac"),  // brown
    ("#b2ddac"),  // gray
    ("#acddd4"),  // lightblue
    ("#cfacdd"),  // redblue

};

int Fbox::nextColor = 0;

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

