#include "fdiagram.h"
#include <QtGui>

Fdiagram::Fdiagram()
{
    setVisible(0);
}

bool Fdiagram::sceneEventFilter(QGraphicsItem *watched, QEvent *event)
{
    if (event->type() == QEvent::GraphicsSceneMousePress)
        if(!watched->isSelected())
            setVisible(1);
        else
            setVisible(0);

    //    qDebug() << "in fiter event" << event->type();
    return false;
}
