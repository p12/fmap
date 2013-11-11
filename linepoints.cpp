#include <QtGui>
#include "linepoints.h"

bool LinePoints::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *keyEvent = static_cast<QMouseEvent *>(event);
        hasPoint(keyEvent->pos());

        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}

