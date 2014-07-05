#ifndef FCOLORS_H
#define FCOLORS_H

#include <QBrush>

static const QColor red    ("#ffa1a1");
static const QColor green  ("#caddac");
static const QColor blue   ("#9eb9ff");
static const QColor yellow ("#faebc3");
static const QColor brown  ("#dfa654");
static const QColor black  ("#6f6b66");
static const QColor natural("#dfdedb");
static const QColor white  ("#f2f2f1");

static QBrush brushes[] = {
    QBrush(red),
    QBrush(green),
    QBrush(blue),
    QBrush(yellow),
    QBrush(brown),
    QBrush(black),
    QBrush(natural),
    QBrush(white)
};

static QString textColors[] = {
    QString("red"),
    QString("green"),
    QString("blue"),
    QString("yellow"),
    QString("brown"),
    QString("black"),
    QString("natural"),
    QString("white")
};


#endif // FCOLORS_H
