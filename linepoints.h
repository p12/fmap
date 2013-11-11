#ifndef LINEPOINTS_H
#define LINEPOINTS_H

#include <QObject>
#include <QPoint>

class LinePoints : public QObject
{
    Q_OBJECT
    
signals:
    void hasPoint(QPoint p);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

public:
    QPoint a;
};

#endif // LINEPOINTS_H
