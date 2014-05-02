#include "ffiber.h"

#include <QBrush>
#include <QVector>

const QColor red("#ffa1a1"); 		// red
const QColor green("#caddac"); 		// green
const QColor blue("#9eb9ff"); 		// blue
const QColor yellow("#faebc3"); 	// yellow
const QColor brown("#dfa654"); 		// brown
const QColor black("#6f6b66"); 		// black
const QColor natural("#dfdedb"); 	// natural (gray)
const QColor white("#f2f2f1");		// white

QBrush brushes[] = {
    QBrush(red),
    QBrush(green),
    QBrush(blue),
    QBrush(yellow),
    QBrush(brown),
    QBrush(black),
    QBrush(natural),
    QBrush(white)
};

Ffiber::Ffiber()
{
    setRect(0, 0, 45, 5);
}

Ffiber::Ffiber(int x, int y, int color, QGraphicsItem *p) : QGraphicsRectItem(p)
{
    setRect(0, 0, 45, 5);
    setBrush(brushes[color]);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setPos(x, y);
}
