#include <QtGui>
#include <QtSvg>
#include "fmap.h"
#include "fdiagram.h"


FMap::FMap(QWidget *parent): QMainWindow(parent)
{
    inCreateBox = false;
    scene = new QGraphicsScene;
    //    scene->addText("Hello, world!");
    QGraphicsSvgItem *map = new QGraphicsSvgItem("/home/pak/projects/FMap/map.svg");
    scene->addItem(map);

    view = new QGraphicsView(scene);
    view->show();

    // Create menus
    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction("Save", this, SLOT(save()), QKeySequence("Ctrl+S"));
    file->addAction("Open", this, SLOT(open()), QKeySequence("Ctrl+O"));
    file->addAction("Quit", this, SLOT(close()), QKeySequence("Ctrl+Q"));

    QMenu *add = menuBar()->addMenu(tr("&Items"));
    add->addAction("Add Box", this, SLOT(createBox()), QKeySequence("B"));
    add->addAction("Add Cable", this, SLOT(createCable()), QKeySequence("C"));

    QMenu *edit = menuBar()->addMenu(tr("&Edit"));
    edit->addAction("Delete", this, SLOT(del()), QKeySequence("Del"));

    QMenu *show = menuBar()->addMenu(tr("&View"));
    show->addAction("Zoom in", this, SLOT(zoomIn()), QKeySequence(QKeySequence::ZoomIn));
    show->addAction("Zoom out", this, SLOT(zoomOut()), QKeySequence(QKeySequence::ZoomOut));

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
                cblVec << scene->addLine(l);
                cblVec.last()->setFlags(QGraphicsItem::ItemIsSelectable);
            }
    }
}

void FMap::save()
{
    QFile file("map-file.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);

    // Saving boxes
    out << boxVec.count();
    foreach (QGraphicsEllipseItem *el, boxVec)
        out << el->pos();

    // Saving cables
    out << cblVec.count();
    foreach (QGraphicsLineItem *l, cblVec)
    {
        out << l->line().p1();
        out << l->line().p2();
    }
}

void FMap::open()
{
    QFile file("map-file.dat");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    int count = 0;
    QPointF p, k;

    // Reading boxes
    in >> count;
    while (count--)
    {
        in >> p;
        drawBox(p);
    }

    // Reading cables
    in >> count;
    while (count--)
    {
        in >> p >> k;
        cblVec << scene->addLine(QLineF(p, k));
    }
}

void FMap::del()
{
    QList<QGraphicsItem*> lst = scene->selectedItems();
    foreach (QGraphicsItem *i, lst) {
        if (QGraphicsEllipseItem * e = qgraphicsitem_cast<QGraphicsEllipseItem *>(i) )
        {
            int i = boxVec.indexOf(e);
            boxVec.remove(i, 1);
            scene->removeItem(e);
            scene->removeItem(dgrmVec[i]);
            dgrmVec.remove(i, 1);
        }
        else if (QGraphicsLineItem * l = qgraphicsitem_cast<QGraphicsLineItem *>(i))
        {
            cblVec.remove(cblVec.indexOf(l), 1);
            scene->removeItem(l);
        }
    }
}

void FMap::zoomIn()
{
    view->scale(1.25, 1.25);
}

void FMap::zoomOut()
{
    view->scale(0.75, 0.75);
}

void FMap::drawBox(QPointF p)
{
    QGraphicsEllipseItem *ell = new QGraphicsEllipseItem(0, 0, 30, 30);
    ell->setFlags(QGraphicsItem::ItemIsSelectable);
    scene->addItem(ell);
    ell->setPos(p);
    boxVec << ell;

    Fdiagram *dgrm = new Fdiagram;
    scene->addItem(dgrm);
    dgrm->setRect(0, 0, 250, 250);
    dgrm->setPos(p + QPoint(50, 50));
    ell->installSceneEventFilter(dgrm);
    dgrmVec << dgrm;
}

void FMap::mousePressEvent(QMouseEvent *e)
{
    if (inCreateBox)
    {
        QPoint t = view->mapFromGlobal(e->pos());
        QPointF p = view->mapToScene(t);
        drawBox(p);

        // Clear data
        inCreateBox = false;
        setCursor(Qt::ArrowCursor);
    }
}
