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

    // Create menus
    QMenu *add = menuBar()->addMenu(tr("&Add"));
    add->addAction("Add Box", this, SLOT(createBox()), QKeySequence("B"));
    add->addAction("Add Cable", this, SLOT(createCable()), QKeySequence("C"));
    add->addAction("Quit", this, SLOT(close()), QKeySequence("Ctrl+Q"));

    setCentralWidget(view);
}

void FMap::createBox()
{
    setCursor(Qt::CrossCursor);
    inCreateBox = true;
}

void FMap::createCable()
{
    QList<QGraphicsItem*> lst = scene->selectedItems();
    if (lst.count() == 2)
    {
        if (qgraphicsitem_cast<QGraphicsEllipseItem *>(lst[0]) )
            if (qgraphicsitem_cast<QGraphicsEllipseItem *>(lst[1]) )
            {
                QLineF l(lst[0]->pos(), lst[1]->pos());
                scene->addLine(l);
            }
    }
}

void FMap::mousePressEvent(QMouseEvent *e)
{
    if (inCreateBox)
    {
        QPoint t = view->mapFromGlobal(e->pos());
        QPointF p = view->mapToScene(t);

        QGraphicsEllipseItem *ell = new QGraphicsEllipseItem(0, 0, 30, 30);
        ell->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        scene->addItem(ell);
        ell->setPos(p);

        Fdiagram *dgrm = new Fdiagram;
        scene->addItem(dgrm);
        dgrm->setRect(0, 0, 250, 250);
        dgrm->setPos(p + QPoint(50, 50));
        ell->installSceneEventFilter(dgrm);


        // Clear data
        a = QPoint(0, 0);
        inCreateBox = false;
        setCursor(Qt::ArrowCursor);
    }
}
