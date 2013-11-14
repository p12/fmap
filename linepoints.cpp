#include <QtGui>
#include "linepoints.h"


bool GetPoint::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *keyEvent = static_cast<QMouseEvent *>(event);
        QPoint p = keyEvent->pos();
        hasPoint(p);

        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}

