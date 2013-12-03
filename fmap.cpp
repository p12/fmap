#include <QtGui>
#include <QtSvg>
#include "fmap.h"


FMap::FMap(QWidget *parent): QMainWindow(parent)
{
    scene = new QGraphicsScene;
//    scene->addText("Hello, world!");
    QGraphicsSvgItem *map = new QGraphicsSvgItem("/home/pak/projects/FMap/map.svg");
    scene->addItem(map);

    view = new QGraphicsView(scene);
    view->show();

    // Create actions
    QAction * cableAdd = new QAction("AddCable", this);
    connect(cableAdd, SIGNAL(triggered()), this, SLOT(addCable()));

    // Create menus
    QMenu *add = menuBar()->addMenu(tr("&Add"));
    add->addAction(cableAdd);

    setCentralWidget(view);

    // Dock view for box diagram
    dockScene = new QGraphicsScene;
    dockScene->addText("Dock widget");
    dockView = new QGraphicsView(dockScene);
    dockView->setMinimumWidth(250);
    dockView->show();
    QDockWidget *dockWidget = new QDockWidget;
    dockWidget->setWidget(dockView);
    addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
}

void FMap::addCable()
{
    setCursor(Qt::CrossCursor);
    inAddCable = true;
}

void FMap::drawBox()
{

}

void FMap::mousePressEvent(QMouseEvent *e)
{
    if (inAddCable)
    {
        QPoint p = mapTo(this, e->globalPos());
        if (a.isNull())
            a = p;
        else {
            QLine l(a, p);
            scene->addLine(l);
            scene->addEllipse(QRectF(a.x(), a.y(), 10, 10));

            QGraphicsEllipseItem *ell = new QGraphicsEllipseItem(p.x(), p.y(), 10, 10);
            ell->setFlags(QGraphicsItem::ItemIsSelectable);
            connect(ell, SIGNAL(isSelected()), this, SLOT(drawBox()));
            scene->addItem(ell);

            // Clear data
            a = QPoint(0, 0);
            inAddCable = false;
            setCursor(Qt::ArrowCursor);
        }
    }
}
