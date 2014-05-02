#include <QtGui>
#include <QtGlobal>
#include <QtSvg>

#include "fmap.h"
#include "fdiagram.h"
#include "fbox.h"
#include "fline.h"
#include "ffiber.h"
#include "fweld.h"
#include "fhomeweld.h"
#include "fcable.h"
#include "fmodule.h"


FMap::FMap(QWidget *parent): QMainWindow(parent)
{
    inCreateBox = false;
    scene = new QGraphicsScene;
    QGraphicsSvgItem *map = new QGraphicsSvgItem("/home/pak/projects/FMap/map.svg");
    scene->addItem(map);

    view = new QGraphicsView(scene);
    view->setRenderHints(QPainter::Antialiasing);
    //   view->setDragMode(QGraphicsView::ScrollHandDrag);
    view->show();

    // Create menus
    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction("Save", this, SLOT(save()), QKeySequence("Ctrl+S"));
    file->addAction("Open", this, SLOT(open()), QKeySequence("Ctrl+O"));
    file->addAction("Quit", this, SLOT(close()), QKeySequence("Ctrl+Q"));

    QMenu *add = menuBar()->addMenu(tr("&Items"));
    add->addAction("Add Box", this, SLOT(createBox()), QKeySequence("B"));
    add->addAction("Add Line", this, SLOT(createLine()), QKeySequence("L"));
    add->addAction("Add Home weld", this, SLOT(createHomeWeld()), QKeySequence("H"));

    QMenu *edit = menuBar()->addMenu(tr("&Edit"));
    edit->addAction("Delete", this, SLOT(del()), QKeySequence("Del"));

    QMenu *show = menuBar()->addMenu(tr("&View"));
    show->addAction("Zoom in", this, SLOT(zoomIn()), QKeySequence(QKeySequence("Z")));
    show->addAction("Zoom out", this, SLOT(zoomOut()), QKeySequence(QKeySequence("Ctrl+Z")));

    setCentralWidget(view);
}

void FMap::createBox()
{
    setCursor(Qt::CrossCursor);
    inCreateBox = true;
}

void FMap::createLine()
{
    QList<QGraphicsItem*> lst = scene->selectedItems();
    if (lst.count() != 2)
        return;

    Fbox *box1 = qgraphicsitem_cast<Fbox *>(lst[0]);
    Fbox *box2 = qgraphicsitem_cast<Fbox *>(lst[1]);

    if (box1 && box2)
    {
        // TODO: cancel button handle
        int m = QInputDialog::getInt(this, "Input modules", "Modules:", 3, 1, 4);
        int f = QInputDialog::getInt(this, "Input fibers", "Fibers:", 4, 1, 100);
        drawCable(box1, box2, m, f);
        return;
    }

    Ffiber *fiber1 = qgraphicsitem_cast<Ffiber *>(lst[0]);
    Ffiber *fiber2 = qgraphicsitem_cast<Ffiber *>(lst[1]);

    if (fiber1 && fiber2)
    {
        drawWeld(fiber1, fiber2);
        return;
    }

    // connecting all fibers on cables
    Fcable *cable1 = qgraphicsitem_cast<Fcable *>(lst[0]);
    Fcable *cable2 = qgraphicsitem_cast<Fcable *>(lst[1]);

    if (cable1 && cable2)
    {
        int size = qMin (cable1->fibers.size(), cable2->fibers.size());
        for (int i = 0; i < size; i++)
            drawWeld(cable1->fibers[i], cable2->fibers[i]);
        return;
    }

    // also all in modules
    Fmodule *module1 = qgraphicsitem_cast<Fmodule *>(lst[0]);
    Fmodule *module2 = qgraphicsitem_cast<Fmodule *>(lst[1]);

    if (module1 && module2)
    {
        Fcable *cable1 = qgraphicsitem_cast<Fcable *>(module1->parentItem());
        Fcable *cable2 = qgraphicsitem_cast<Fcable *>(module2->parentItem());

        int count = qMin (cable1->fibers.size() / cable1->modules.size(),
                          cable2->fibers.size() / cable2->modules.size() );
        int pos1  = cable1->modules.indexOf(module1) * count;
        int pos2  = cable2->modules.indexOf(module2) * count;
        for (int i = 0; i < count; i++)
            drawWeld(cable1->fibers[pos1 + i], cable2->fibers[pos2 + i]);
    }
}

void FMap::createHomeWeld()
{
    QList<QGraphicsItem*> lst = scene->selectedItems();
    if (lst.count() != 1)
        return;

    Ffiber *fiber = qgraphicsitem_cast<Ffiber *>(lst[0]);
    if (fiber)
        drawHomeWeld(fiber);
}

void FMap::save()
{
    QFile file("map-file.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);

    // Saving
    // boxes
    out << boxes.size();
    foreach (Fbox *b, boxes) {
        out << b->pos()
            << b->diagram->addr->toPlainText();
    }

    // lines
    out << lines.size();
    foreach (Fline *l, lines) {
        int a = boxes.indexOf(l->box1);
        int b = boxes.indexOf(l->box2);
        if (a >= 0)
            if (b >= 0)
                out << a << b;
        out << l->moduleCount << l->fiberCount;
    }

    foreach (Fbox *b, boxes) {
        //welds
        out << b->diagram->welds.size();
        foreach (Fweld *w, b->diagram->welds) {
            int c1 = b->diagram->cables.indexOf(w->cable1);
            int c2 = b->diagram->cables.indexOf(w->cable2);
            if (c1 >= 0 && c2 >= 0)
            {
                int f1 = b->diagram->cables[c1]->fibers.indexOf(w->fiber1);
                int f2 = b->diagram->cables[c2]->fibers.indexOf(w->fiber2);
                if (f1 >= 0 && f2 >= 0)
                    out << c1 << c2 << f1 << f2;
            }
        }
        // homeWelds
        out << b->diagram->homeWelds.size();
        foreach (FhomeWeld *homeWeld, b->diagram->homeWelds) {
            int cablePos = b->diagram->cables.indexOf(homeWeld->cable);
            if (cablePos >= 0)
            {
                int fiberPos = b->diagram->cables[cablePos]->fibers.indexOf(homeWeld->fiber);
                if (fiberPos >= 0)
                    out << cablePos << fiberPos;
            }
        }
    }
}

void FMap::open()
{
    QFile file("map-file.dat");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);

    int a, b, m, f, c1, c2, f1, f2, count = 0;
    QPointF p;
    QString str;

    // Reading
    // boxes
    in >> count;
    for (int i = 0; i < count; i++)
    {
        in >> p >> str;
        drawBox(p);
        boxes.last()->diagram->addr->setPlainText(str);
    }

    // lines
    in >> count;
    for (int i = 0; i < count; i++)
    {
        in >> a >> b >> m >> f;
        drawCable(boxes[a], boxes[b], m, f);
    }

    foreach (Fbox *b, boxes) {
        // welds
        in >> count;
        for (int j = 0; j < count; j++)
        {
            in >> c1 >> c2 >> f1 >> f2;
            drawWeld(b->diagram->cables[c1]->fibers[f1], b->diagram->cables[c2]->fibers[f2]);
        }
        // homewelds
        in >> count;
        for (int j = 0; j < count; j++)
        {
            in >> c1 >> f1;
            drawHomeWeld(b->diagram->cables[c1]->fibers[f1]);
        }
    }

}

void FMap::del()
{
    QList<QGraphicsItem*> lst = scene->selectedItems();
    foreach (QGraphicsItem *it, lst) {
        if (Fbox *box = qgraphicsitem_cast<Fbox *>(it) )
        {
            int i = boxes.indexOf(box);
            if (i < 0)
                return;
            foreach (Fline *line, box->lines)
                delCable(line);
            boxes.remove(i);
            scene->removeItem(box);
            delete box;
        }
        else if (Fline * l = qgraphicsitem_cast<Fline *>(it))
        {
            delCable(l);
        }
        else if (Fweld * w = qgraphicsitem_cast<Fweld *>(it))
        {
            delWeld(w);
        }
        else if (FhomeWeld * home = qgraphicsitem_cast<FhomeWeld *>(it))
        {
            delHomeWeld(home);
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

void FMap::drawBox(QPointF point)
{
    Fbox *box = new Fbox();
    scene->addItem(box);
    box->setPos(point);
    boxes << box;
    box->setupFilter();
}

void FMap::drawCable(Fbox *aBox, Fbox *bBox, int moduleCount, int fiberCount)
{
    Fline *line = new Fline;
    line->setLine(QLineF(aBox->pos(), bBox->pos()));
    scene->addItem(line);
    lines << line;

    // ptrs to box1 and box2 in line
    line->box1 = aBox;
    line->box2 = bBox;
    // ptrs to line in box1 and box2
    aBox->lines << line;
    bBox->lines << line;

    aBox->diagram->addCable(moduleCount, fiberCount, bBox->diagram->addr->toPlainText());
    bBox->diagram->addCable(moduleCount, fiberCount, aBox->diagram->addr->toPlainText());

    // ptrs to dgrmA and dgrmB cables in line
    line->cable1 = aBox->diagram->cables.last();
    line->cable2 = bBox->diagram->cables.last();
    line->moduleCount = moduleCount;
    line->fiberCount = fiberCount;
}

void FMap::drawWeld(Ffiber *a, Ffiber *b)
{
    Fdiagram *dgram = qgraphicsitem_cast<Fdiagram *>(a->parentItem()->parentItem());
    if (dgram)
        // both Ffibers from one Fdiagram
        if (a->parentItem()->parentItem() == b->parentItem()->parentItem())
            dgram->addWeld(a, b);
}

void FMap::drawHomeWeld(Ffiber *fiber)
{
    Fdiagram *dgram  = qgraphicsitem_cast<Fdiagram *>(fiber->parentItem()->parentItem());
    if (dgram)
        dgram->addHomeWeld(fiber);
}

void FMap::delCable(Fline *l)
{
    int k = lines.indexOf(l);
    if (k < 0)
        return;
    lines.remove(k);
    scene->removeItem(l);

    l->box1->diagram->delCable(l->cable1);
    l->box2->diagram->delCable(l->cable2);

    delete l;
}

void FMap::delWeld(Fweld *w)
{
    Fdiagram *d = qgraphicsitem_cast<Fdiagram *>(w->parentItem());
    d->delWeld(w);
}

void FMap::delHomeWeld(FhomeWeld *homeWeld)
{
    Fdiagram *diagram = qgraphicsitem_cast<Fdiagram *>(homeWeld->parentItem());
    diagram->delHomeWeld(homeWeld);
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

