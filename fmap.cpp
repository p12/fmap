#include <QtGui>
#include <QtSvg>
#include "fmap.h"
#include "linepoints.h"


FMap::FMap(QWidget *parent): QMainWindow(parent)
{
    scene = new QGraphicsScene;
    scene->addText("Hello, world!");
    QGraphicsSvgItem *map = new QGraphicsSvgItem("/home/pak/projects/FMap/map.svg");
    scene->addItem(map);

    QGraphicsView *view = new QGraphicsView(scene);

    view->setMinimumSize(700, 700);
    view->show();

    // Create actions
    QAction * cableAdd = new QAction("AddCable", this);
    connect(cableAdd, SIGNAL(triggered()), this, SLOT(addCable()));

    // Create menus
    QMenu *add = menuBar()->addMenu(tr("&Add"));
    add->addAction(cableAdd);

    setCentralWidget(view);


    getPoint = new LinePoints;
}

void FMap::setPoint(QPoint p)
{
    if (a.isNull())
        a = p;
    else {
        QLineF l(a, p);
        scene->addLine(l);
        a = QPoint(0, 0);
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
