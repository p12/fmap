#ifndef LINEPOINTS_H
#define LINEPOINTS_H

#include <QObject>
#include <QPoint>

class GetPoint : public QObject
{
    Q_OBJECT
    
signals:
    void hasPoint(QPoint p);

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // LINEPOINTS_H
