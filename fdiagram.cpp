#include "fdiagram.h"
#include <QtGui>

Fdiagram::Fdiagram()
{
    setVisible(0);
}

bool Fdiagram::sceneEventFilter(QGraphicsItem *watched, QEvent *event)
{

    if (event->type() == QEvent::GraphicsSceneMousePress)
        if(isVisible())
            setVisible(0);
        else
            setVisible(1);

    //    qDebug() << "in fiter event" << event->type();
    return false;
}
