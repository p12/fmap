#include "fview.h"
#include <QWheelEvent>
#include <QMouseEvent>

Fview::Fview()
{
}

void Fview::wheelEvent(QWheelEvent *event)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

        // Scale the view / do the zoom
        double scaleFactor = 1.15;
        if(event->delta() > 0) {
            // Zoom in
            scale(scaleFactor, scaleFactor);
        } else {
            // Zooming out
            scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        }
}

void Fview::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        mLast = event->posF();
    QGraphicsView::mousePressEvent(event);
}

void Fview::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton) {
        QPointF delta = event->posF() - mLast;
        translate(delta.x(), delta.y());
    }
    QGraphicsView::mouseMoveEvent(event);
}
