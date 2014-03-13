#include <QtGui>
#include <QtSvg>
#include "fmap.h"
#include "fdiagram.h"


FMap::FMap(QWidget *parent): QMainWindow(parent)
{
    inCreateBox = false;
    scene = new QGraphicsScene;
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
        QGraphicsEllipseItem *a, *b;
        if (a = qgraphicsitem_cast<QGraphicsEllipseItem *>(lst[0]) )
            if (b = qgraphicsitem_cast<QGraphicsEllipseItem *>(lst[1]) )
            {
                int i = boxVec.indexOf(a);
                int k = boxVec.indexOf(b);
                cb2bx << QPair<int, int>(i, k);
                drawCable(i, k);
            }
    }
}

void FMap::save()
{
    QFile file("map-file.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);

    // Saving
    // boxes and diagrams
    out << boxVec.size();
    for (int i = 0; i < boxVec.size(); i++)
        out << boxVec[i]->pos()
            << dgrmVec[i]->addr->text();

    // links
    out << cb2bx;
}

void FMap::open()
{
    QFile file("map-file.dat");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);

    int sz = 0;
    QPointF p;
    QString str;

    // Reading
    // boxes and diagrams
    in >> sz;
    for (int i = 0; i < sz; i++)
    {
        in >> p >> str;
        drawBox(p);
        drawDgrm(p +  QPoint(50, 0));
        dgrmVec[i]->addr->setText(str);
    }

    // links
    in >> cb2bx;

    // cables
    QPair<int,int> d;
    foreach (d, cb2bx)
        drawCable(d.first, d.second);
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
}

void FMap::drawDgrm(QPointF p)
{
    Fdiagram *dgrm = new Fdiagram;
    scene->addItem(dgrm);
    dgrm->setPos(p);
    boxVec.last()->installSceneEventFilter(dgrm);
    dgrmVec << dgrm;
}

void FMap::drawCable(int a, int b)
{
    cblVec << scene->addLine(QLineF(boxVec[a]->pos(), boxVec[b]->pos()));
    cblVec.last()->setFlags(QGraphicsItem::ItemIsSelectable);
    QPen pen;
    pen.setWidth(2);
    cblVec.last()->setPen(pen);

    dgrmVec[a]->addCable("XXX");
    dgrmVec[b]->addCable("XXX");
}

void FMap::mousePressEvent(QMouseEvent *e)
{
    if (inCreateBox)
    {
        QPoint t = view->mapFromGlobal(e->pos());
        QPointF p = view->mapToScene(t);
        drawBox(p);
        drawDgrm(p + QPoint(50, 0));

        // Clear data
        inCreateBox = false;
        setCursor(Qt::ArrowCursor);
    }
}

