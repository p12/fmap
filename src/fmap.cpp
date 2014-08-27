#include <QtGui>
#include <QtGlobal>
#include <QtSvg>
#include <QDebug>

#include "fmap.h"
#include "fdiagram.h"
#include "fbox.h"
#include "fline.h"
#include "ffiber.h"
#include "fweld.h"
#include "fhomeweld.h"
#include "fcable.h"
#include "fmodule.h"
#include "fscene.h"
#include "fdiagramstack.h"
#include "flogicfiber.h"
#include "fview.h"

FMap::FMap(QWidget *parent): QMainWindow(parent)
{
    inCreateBox = false;
    scene = new QGraphicsScene;
//    view = new QGraphicsView(scene);
    view = new Fview;
    view->setScene(scene);
    view->setRenderHints(QPainter::Antialiasing);
    view->show();
    
    importBackground();

    stack = new FdiagramStack;
    
    // Create menus
    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction("Save", this, SLOT(save()), QKeySequence("Ctrl+S"));
    file->addAction("Open", this, SLOT(open()), QKeySequence("Ctrl+O"));
    file->addAction("Print", this, SLOT(print()), QKeySequence("Ctrl+P"));
    file->addAction("Quit", this, SLOT(close()), QKeySequence("Ctrl+Q"));
    
    QMenu *add = menuBar()->addMenu(tr("&Items"));
    add->addAction("Add Box", this, SLOT(createBox()), QKeySequence("B"));
    add->addAction("Add Line", this, SLOT(createLine()), QKeySequence("L"));
    add->addAction("Add Weld", this, SLOT(createWeld()), QKeySequence("W"));
    add->addAction("Add Home weld", this, SLOT(createHomeWeld()), QKeySequence("H"));
    
    QMenu *edit = menuBar()->addMenu(tr("&Edit"));
    edit->addAction("Delete", this, SLOT(del()), QKeySequence("Del"));
    
//    QMenu *show = menuBar()->addMenu(tr("&View"));
//    show->addAction("Zoom in", this, SLOT(zoomIn()), QKeySequence("Ctrl+Up"));
//    show->addAction("Zoom out", this, SLOT(zoomOut()), QKeySequence("Ctrl+Z"));
    
    QMenu *tools = menuBar()->addMenu(tr("&Tools"));
    tools->addAction("Trace channel", this, SLOT(tracePath()), QKeySequence("T"));
    
    // Diagrams view setup
    diagramScene = new QGraphicsScene;
    
    diagramView = new QGraphicsView(diagramScene);
    diagramView->show();
    diagramView->setFixedWidth(500);
    diagramView->setRenderHints(QPainter::Antialiasing);
    
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(diagramView);
    hLayout->addWidget(view);
    hLayout->setMargin(0);
    hLayout->setSpacing(0);
    
    QWidget *widget = new QWidget;
    widget->setLayout(hLayout);
    setCentralWidget(widget);

}

void FMap::delLogicWeld(Fweld *w)
{
    // Del from logic channel
    int posA = -1;
    int posB = -1;
    int channel = -1;

    // search for fibers in all channels
    for (int i = 0; i < channels.size(); i++) {
        int pos = channels[i].indexOf(w->fiber1->getLogicFiber());
        if (pos >= 0){
            posA = pos;
            channel = i;
        }
        pos = channels[i].indexOf(w->fiber2->getLogicFiber());
        if (pos >= 0){
            posB = pos;
            break;
        }
    }

    if (channel == -1)
        return;

    // only 2 fibers
    if (channels[channel].size() == 2) {
        channels.remove(channel);
        // fiber A is at begin or end of channel
    } else if (posA == 0 || posA == channels[channel].size() - 1) {
        channels[channel].remove(posA);
        // fiber B is at begin or end
    } else if (posB == 0 || posB == channels[channel].size() - 1) {
        channels[channel].remove(posB);
        // both are at middle and A is first
    } else if (posA < posB) {
        channels << channels[channel].mid(posB);
        channels[channel].remove(posB, channels[channel].size() - posB);
        // or B is first
    } else if (posA > posB) {
        channels << channels[channel].mid(posA);
        channels[channel].remove(posA, channels[channel].size() - posA);
    } else
        qDebug() << "del Weld else overflow";
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
        bool ok;
        int m = QInputDialog::getInt(this, "Input modules count in cable.", "Modules:", 3, 1, 10, 1, &ok);
        if (!ok)
            return;
        
        int f = QInputDialog::getInt(this, "Input fibers count in module.", "Fibers:", 4, 1, 100, 1, &ok);
        if (!ok)
            return;
        QVector<FlogicFiber *> fibers;
        for (int i = 0; i < f * m; i++)
            fibers << new FlogicFiber;
        
        logicFibers << fibers;
        drawCable(box1, box2, m, fibers);
    }
}

void FMap::createWeld()
{
    QList<QGraphicsItem*> lst = diagramScene->selectedItems();
    if (lst.count() != 2)
        return;
    
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
    QList<QGraphicsItem*> lst = diagramScene->selectedItems();
    if (lst.count() != 1)
        return;
    
    Ffiber *fiber = qgraphicsitem_cast<Ffiber *>(lst[0]);
    if (fiber)
        drawHomeWeld(fiber);
}

void FMap::save()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select File", "/home");
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    
    // Saving
    // boxes
    out << boxes.size();
    foreach (Fbox *box, boxes) {
        out << box->pos()
            << box->getAddress()
            << box->getStreet()
            << box->getBuild();
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
        out << l->getPoints();
        out << l->getLength();
    }
    
    // cables order in boxes
    foreach (Fbox *box, boxes) {
        out << box->diagram->getOrder();
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
    statusBar()->showMessage("Saved.", 4000);
}

void FMap::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select File", "/home");
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    
    int a, b, m, f, c1, c2, f1, f2, count = 0;
    QPointF p;
    QString str, build, street;
    
    // Reading
    // boxes
    in >> count;
    for (int i = 0; i < count; i++)
    {
        in >> p >> str
           >> street >> build;
        drawBox(p);
        boxes.last()->setAddress(build, street);
    }
    
    // lines
    QVector<QPointF> points;
    uint length;
    in >> count;
    for (int i = 0; i < count; i++)
    {
        in >> a >> b
           >> m >> f;
        in >> points;
        in >> length;
        
        QVector<FlogicFiber *> indexes;
        for (int i = 0; i < m * f; i++)
            indexes << new FlogicFiber;
        
        logicFibers << indexes;
        drawCable(boxes[a], boxes[b], m, indexes);
        lines.last()->setPoints(points);
        lines.last()->setLength(length);
    }
    
    // cables order in diagrams
    QMap<QString, int> order;
    foreach (Fbox *box, boxes) {
        in >> order;
        box->diagram->setOrder(order);
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
    QList<QGraphicsItem*> lst;
    if (scene->hasFocus())
    {
        lst = scene->selectedItems();
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
                diagramScene->removeItem(box->diagram);
                delete box;
            }
            else if (Fline * l = qgraphicsitem_cast<Fline *>(it))
            {
                delCable(l);
            }
        }
    }
    else if (diagramScene->hasFocus())
    {
        lst = diagramScene->selectedItems();
        foreach (QGraphicsItem *item, lst) {
            if (Fweld * w = qgraphicsitem_cast<Fweld *>(item))
            {
                delWeld(w);
            }
            else if (FhomeWeld * home = qgraphicsitem_cast<FhomeWeld *>(item))
            {
                delHomeWeld(home);
            }
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

void FMap::tracePath()
{
    QList<QGraphicsItem*> list = diagramScene->selectedItems();
    if (list.size() != 1)
        return;
    Fweld *weld = qgraphicsitem_cast<Fweld *>(list[0]);
    if (!weld)
        return;
    
    stack->clear();
    
    foreach (QVector<FlogicFiber *> channel, channels) {
        int pos = channel.indexOf(weld->fiber1->getLogicFiber());
        if (pos >= 0)
            foreach (FlogicFiber *logicFiber, channel) {
                foreach (Fbox *box, logicFiber->boxes)
                    box->setSelected(1);
                foreach (Ffiber *fiber, logicFiber->fibers)
                    fiber->setSelected(1);
            }
    }
}

void FMap::print()
{
    // setup diagrams for printing
    foreach (Fdiagram *diagram, stack->getDiagrams()) {
        diagram->toPrint();
    }

    QPrinter printer;
    if (QPrintDialog(&printer).exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        painter.setRenderHint(QPainter::Antialiasing);
        diagramView->render(&painter);
    }
    // undo printing setup
    foreach (Fdiagram *diagram, stack->getDiagrams()) {
        diagram->toView();
    }
}

void FMap::importBackground()
{
    QFile file("/home/pak/tmp/map.osm.xml");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QXmlStreamReader xml(&file);
    QString id, lat, lon;
    QVector<QString> ids;
    qreal x, y;
    QMap<QString, QPointF> nodes;
    QMap<QString, QVector<QPointF> > ways;

    while(!xml.atEnd() && !xml.hasError()){
        QString errstr;
        QXmlStreamReader::TokenType token;
        token = xml.readNext();
        errstr = xml.errorString();

        /*If token is StartElement trying to read it*/
        if(token == QXmlStreamReader::StartElement){
            if (xml.name() == "node")
            {
                QXmlStreamAttributes attributes = xml.attributes();
                if(attributes.hasAttribute("id"))
                    id = attributes.value("id").toString();
                if(attributes.hasAttribute("lat"))
                    lat = attributes.value("lat").toString();
                if(attributes.hasAttribute("lon"))
                    lon = attributes.value("lon").toString();
                // convert to cartesian projection
                QProcess proc(this);
                proc.start("/home/pak/bin/Proj " + lon + " " + lat);
                proc.waitForFinished();
                QByteArray result = proc.readAll();
                QTextStream text(result);
                text >> x >> y;
                nodes.insert(id, QPointF(x * 5, y * -5));
            }
            if (xml.name() == "way")
            {
                QXmlStreamAttributes attributes = xml.attributes();
                QString wid = attributes.value("id").toString();
                token = xml.readNext();
                QVector<QPointF> points;
                QString number;
                while (xml.name() != "way") {
                    if (token == QXmlStreamReader::StartElement) {
                        if (xml.name() == "nd") {
                            QXmlStreamAttributes attributes = xml.attributes();
                            id = attributes.value("ref").toString();
                            points << nodes.value(id);
                        }
                        else if (xml.name() == "tag") {
                            QXmlStreamAttributes attributes = xml.attributes();
                            QString tag = attributes.value("k").toString();
                            QString val = attributes.value("v").toString();
                            if (tag == "addr:housenumber") {
                                number = val;
                            }
                            else if (tag == "building") {
                                QPainterPath path(points[0]);
                                foreach (QPointF p, points) {
                                    path.lineTo(p);
                                }
                                QPen pen("#666666");
                                QBrush br("#bca9a9");
                                scene->addPath(path, pen, br);
                                QFont f("Verdana", 14);
                                f.setBold(1);
                                QGraphicsTextItem *txt = new QGraphicsTextItem(number);
                                txt->setFont(f);
                                txt->setPos(path.boundingRect().center() - txt->boundingRect().center());
                                scene->addItem(txt);
                            }
                            else if (tag == "highway") {
                                QPainterPath path(points[0]);
                                foreach (QPointF p, points) {
                                    path.lineTo(p);
                                }
                                qreal width = 1;
                                if (val == "track")
                                    width = 1.33;
                                else if (val == "pedestrian")
                                    width = 5.5;
                                else if (val == "service")
                                    width = 4.33;
                                else if (val == "residential")
                                    width = 12;
                                else if (val == "unclassified")
                                    width = 12;
                                else if (val == "tertiary")
                                    width = 11.33;
                                else if (val == "secondary")
                                    width = 11.33;
                                else if (val == "primary")
                                    width = 11.33;
                                else if (val == "primary_link")
                                    width = 11.33;
                                else if (val == "access_destination" || val == "access_private")
                                    width = 3.33;
                                else
                                    break;
                                QPen pen(QBrush("#aaaaaa"), width * 4);
                                scene->addPath(path, pen);
                            }
                        }
                    }
                    token = xml.readNext();
                }
            }
        }
    }
}

void FMap::drawBox(QPointF point)
{
    Fbox *box = new Fbox;
    box->setStack(stack);
    scene->addItem(box);
    box->setPos(point);
    boxes << box;
    
    diagramScene->addItem(box->diagram);
    box->diagram->setMap(this);
}

void FMap::drawCable(Fbox *box1, Fbox *box2, int moduleCount, QVector<FlogicFiber *> &fibers)
{
    Fline *line = new Fline(box1->pos(), box2->pos());
    scene->addItem(line);
    lines << line;
    
    // ptrs to box1 and box2 in line
    line->box1 = box1;
    line->box2 = box2;
    // ptrs to line in box1 and box2
    box1->lines << line;
    box2->lines << line;
    
    foreach (FlogicFiber *logicFiber, fibers)
        logicFiber->boxes << box1 << box2;
    
    box1->diagram->addCable(moduleCount, fibers, box2->getAddress());
    box2->diagram->addCable(moduleCount, fibers, box1->getAddress());
    
    // ptrs to dgrmA and dgrmB cables in line
    line->cable1 = box1->diagram->cables.last();
    line->cable2 = box2->diagram->cables.last();
    line->moduleCount = moduleCount;
    line->fiberCount = fibers.size() / moduleCount;
}

void FMap::drawWeld(Ffiber *a, Ffiber *b)
{
    if (a->isWelded() || b->isWelded())
        return;
    
    Fdiagram *dgram = qgraphicsitem_cast<Fdiagram *>(a->parentItem()->parentItem());
    if (!dgram)
        return;

    // both Ffibers from one Fdiagram
    if (a->parentItem()->parentItem() != b->parentItem()->parentItem())
        return;

    dgram->addWeld(a, b);
    a->setWelded(1);
    b->setWelded(1);

    // Work with logic channels (for tracing)
    int posA = -1;
    int posB = -1;
    int channelA, channelB;
    
    // search for fibers in all channels
    for (int i = 0; i < channels.size (); i++) {
        int pos = channels[i].indexOf(a->getLogicFiber());
        if (pos >= 0){
            posA = pos;
            channelA = i;
        }
        pos = channels[i].indexOf (b->getLogicFiber ());
        if (pos >= 0){
            posB = pos;
            channelB = i;
        }
    }
    
    // if A and B fibers not found
    if (posB == -1 && posA == -1) {
        QVector<FlogicFiber *> channel;
        channel << a->getLogicFiber() << b->getLogicFiber();
        channels << channel;
        
        // if only A found
    } else if (posB == -1 && posA >= 0) {
        if (posA == 0)
            channels[channelA].prepend(b->getLogicFiber());
        else if (posA == channels[channelA].size() - 1)
            channels[channelA].append(b->getLogicFiber());
        else
            qDebug() << posA;
        
        // if only B found
    } else if (posA == -1 && posB >= 0) {
        if (posB == 0)
            channels[channelB].prepend(a->getLogicFiber());
        else if (posB == channels[channelB].size() - 1)
            channels[channelB].append(a->getLogicFiber());
        else
            qDebug() << posB;
        
        // if both found
    } else if (posA == 0 && posB == channels[channelB].size() - 1) {
        channels[channelB] << channels[channelA];
        channels.remove (channelA);
    } else if (posB == 0 && posA == channels[channelA].size() - 1) {
        channels[channelA] << channels[channelB];
        channels.remove(channelB);
    } else if (posB == 0 && posA == 0) {
        for (int i = 0; i < channels[channelA].size(); i++)
            channels[channelB].prepend(channels[channelA][i]);
        channels.remove(channelA);
    } else if (posB == channels[channelB].size() - 1 &&
               posA == channels[channelA].size() - 1) {
        for (int i = channels[channelA].size() - 1; i >= 0; i--)
            channels[channelB].prepend(channels[channelA][i]);
        channels.remove(channelA);
    } else
        qDebug() << "drawWeld if both found" << posB << posA;
}

void FMap::drawHomeWeld(Ffiber *fiber)
{
    if (fiber->isWelded())
        return;
    
    fiber->setWelded(1);
    Fdiagram *dgram  = qgraphicsitem_cast<Fdiagram *>(fiber->parentItem()->parentItem());
    if (dgram)
        dgram->addHomeWeld(fiber);
}

void FMap::delCable(Fline *line)
{
    int pos = lines.indexOf(line);
    if (pos < 0)
        return;
    lines.remove(pos);
    scene->removeItem(line);
    
    line->box1->deleteLine(line);
    line->box2->deleteLine(line);
    line->box1->diagram->delCable(line->cable1);
    line->box2->diagram->delCable(line->cable2);
    
    delete line;
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

