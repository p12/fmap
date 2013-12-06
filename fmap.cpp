#include <QtGui>
#include <QtSvg>
#include "fmap.h"
#include "fdiagram.h"


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
        QPointF p = view->mapToScene(e->pos());
        if (a.isNull())
            a = p;
        else {
            QLineF l(a, p);
            scene->addLine(l);
            scene->addEllipse(QRectF(a.x(), a.y(), 10, 10));

            QGraphicsEllipseItem *ell = new QGraphicsEllipseItem(p.x(), p.y(), 10, 10);
            ell->setFlags(QGraphicsItem::ItemIsSelectable);
            scene->addItem(ell);

            Fdiagram *dgrm = new Fdiagram;
            scene->addItem(dgrm);
            dgrm->setRect(0, 0, 250, 250);
            dgrm->setPos(500, 500);
            ell->installSceneEventFilter(dgrm);


            // Clear data
            a = QPoint(0, 0);
            inAddCable = false;
            setCursor(Qt::ArrowCursor);
        }
    }
}
