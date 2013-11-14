#include <QtGui>
#include <QtSvg>
#include "fmap.h"
#include "linepoints.h"


FMap::FMap(QWidget *parent): QMainWindow(parent)
{
    scene = new QGraphicsScene(this);
    scene->addText("Hello, world!");
    QGraphicsSvgItem *map = new QGraphicsSvgItem("/home/pak/projects/FMap/map.svg");
    scene->addItem(map);

    view = new QGraphicsView(scene, this);
    view->show();

    // Create actions
    QAction * cableAdd = new QAction("AddCable", this);
    connect(cableAdd, SIGNAL(triggered()), this, SLOT(addCable()));

    // Create menus
    QMenu *add = menuBar()->addMenu(tr("&Add"));
    add->addAction(cableAdd);

    setCentralWidget(view);
    getPoint = new GetPoint;
}

void FMap::setPoint(QPoint p)
{
    if (a.isNull())
        a = mapTo(view, p);

    else {
        QLine l(a, p);
        scene->addLine(l);

        // Clear data
        a = QPoint(0, 0);
        disconnect(getPoint, SIGNAL(hasPoint(QPoint)), 0, 0);
        removeEventFilter(getPoint);
        setCursor(Qt::ArrowCursor);
    }
}

void FMap::addCable()
{
    setCursor(Qt::CrossCursor);
    connect(getPoint, SIGNAL(hasPoint(QPoint)), SLOT(setPoint(QPoint)));
    installEventFilter(getPoint);
}
