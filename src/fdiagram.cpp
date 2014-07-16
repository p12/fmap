#include "fdiagram.h"
#include "fcable.h"
#include "ffiber.h"
#include "fweld.h"
#include "fhomeweld.h"
#include "fmap.h"

#include <QtGui>

const int MRGN = 25;
const int WMIN = 150;

Fdiagram::Fdiagram()
{
    setVisible(0);
    setRect(0, 0, WMIN, 250);
    setBrush(Qt::white);

    // Address of box
    QWidget *w = new QWidget;
    QHBoxLayout *l = new QHBoxLayout;
    l->setContentsMargins(0, 0, 0, 0);

    streetCombo = new QComboBox;

    streetCombo->addItem(QObject::trUtf8("Московская"));
    streetCombo->addItem(QObject::trUtf8("Социалистическая"));
    streetCombo->addItem(QObject::trUtf8("Калинина"));
    streetCombo->addItem(QObject::trUtf8("Пионерская"));
    streetCombo->addItem(QObject::trUtf8("Чичерина"));
    streetCombo->addItem(QObject::trUtf8("Чичерина пер."));
    streetCombo->addItem(QObject::trUtf8("Кооперативная"));
    streetCombo->addItem(QObject::trUtf8("Тельмана"));
    connect(streetCombo, SIGNAL(currentIndexChanged(int)), SLOT(prepareAddressChange(int)));

    buildCombo = new QComboBox;
    buildCombo->addItem("1");
    buildCombo->addItem("2");
    buildCombo->addItem("9");
    buildCombo->addItem("12");
    buildCombo->addItem("12/1");
    buildCombo->addItem("18/1");
    connect(buildCombo, SIGNAL(currentIndexChanged(int)), SLOT(prepareAddressChange(int)));

    l->addWidget(streetCombo);
    l->addWidget(buildCombo);
    w->setLayout(l);

    addressProxy = new QGraphicsProxyWidget(this);
    addressProxy->setWidget(w);
    addressProxy->setPos(MRGN, 40);
    addressProxy->setZValue(10);
}

void Fdiagram::addCable(int m, QVector<FlogicFiber *> &fibers, QString s)
{
    cables << new Fcable(m, fibers, s, this);
    resize();
}

void Fdiagram::delCable(Fcable *c)
{
    int i = cables.indexOf(c);
    if (i < 0)
        return;

    // remove welds connected to this cable
    foreach (Fweld *w, welds) {
        if (w->cable1 == c || w->cable2 == c)
            delWeld(w);
    }

    // remove homeWelds also
    foreach (FhomeWeld *homeWeld, homeWelds) {
        if (homeWeld->cable == c)
            delHomeWeld(homeWeld);
    }

    delete cables[i];
    cables.remove(i);
    resize();
}

void Fdiagram::moveCable(Fcable *cable, bool right)
{
    int p = cables.indexOf(cable);
    if (right > 0)
    {
        // Moving cable right
        int q = p + 1;
        if ( p >= 0 && q < cables.size() )
        {
            Fcable *tmp = cables[p];
            cables[p] = cables[q];
            cables[q] = tmp;
        }
    }
    else
    {
        // Moving left
        int q = p - 1;
        if ( q >= 0 && p < cables.size() )
        {
            Fcable *tmp = cables[p];
            cables[p] = cables[q];
            cables[q] = tmp;
        }
    }
    resize();
}

void Fdiagram::addWeld(Ffiber *a, Ffiber *b)
{
    Fweld *weld = new Fweld;
    weld->fiber1 = a;
    weld->fiber2 = b;
    weld->cable1 = qgraphicsitem_cast<Fcable *>(a->parentItem());
    weld->cable2 = qgraphicsitem_cast<Fcable *>(b->parentItem());

    drawWeld(weld);

    weld->setParentItem(this);
    welds << weld;
}

void Fdiagram::addHomeWeld(Ffiber *fiber)
{
    FhomeWeld *homeWeld = new FhomeWeld;
    homeWeld->fiber = fiber;
    homeWeld->cable = qgraphicsitem_cast<Fcable *>(fiber->parentItem());

    drawHomeWeld(homeWeld);

    homeWeld->setParentItem(this);
    homeWelds << homeWeld;
}

void Fdiagram::delWeld(Fweld *w)
{
    w->fiber1->setWelded(0);
    w->fiber2->setWelded(0);
    map->delLogicWeld(w);

    int i = welds.indexOf(w);
    if (i >= 0)
        welds.remove(i);
    delete w;
}

void Fdiagram::delHomeWeld(FhomeWeld *homeWeld)
{
    homeWeld->fiber->setWelded(0);
    int pos = homeWelds.indexOf(homeWeld);
    if (pos >= 0)
        homeWelds.remove(pos);
    delete homeWeld;
}

int Fdiagram::type() const
{
    return Type;
}

void Fdiagram::prepareAddressChange(int /*i*/)
{
    emit addressChanged(streetCombo->currentText() + " " + 
                        buildCombo->currentText());
}

void Fdiagram::resize()
{
    // set position per cable count
    int x, y = rect().height() / 3;
    QPointF first(MRGN, y);

    switch (cables.size())
    {
    case 1 :
        // set pos 0
        cables[0]->setPos(first);
        break;
    case 2 :
        // set pos 0 1
        cables[0]->setPos(first);
        x = cables[0]->rect().right() + MRGN * 2;
        cables[1]->setPos(x, y);
        break;
    case 3 :
        // set pos 0 1 2
        cables[0]->setPos(first);
        x = cables[0]->rect().right() + MRGN * 2;
        cables[1]->setPos(x, y);
        x = cables[1]->x() + cables[1]->rect().width() + MRGN;
        cables[2]->setPos(x, y);
        break;
    case 4 :
        // set pos 0 1 2/3
        cables[0]->setPos(first);
        x = cables[0]->rect().right() + MRGN * 2;
        cables[1]->setPos(x, y);
        x = cables[1]->x() + cables[1]->rect().width() + MRGN;
        cables[2]->setPos(x, y);
        y += cables[2]->rect().height() + MRGN;
        cables[3]->setPos(x, y);
        break;
    }

    foreach (Fweld *weld, welds)
        drawWeld(weld);
    foreach (FhomeWeld *homeWeld, homeWelds)
        drawHomeWeld(homeWeld);

    // check Fdiagram size
    qreal width = addressProxy->rect().width() + MRGN * 2;
    qreal height = 150.0;

    foreach (Fcable *cable, cables) {
        width  = qMax(width,  cable->x() + cable->rect().width());
        height = qMax(height, cable->y() + cable->rect().height());
    }

    setRect(0, 0, width + MRGN, height + MRGN);
}

void Fdiagram::drawWeld(Fweld *weld)
{
    QPointF pointA = mapFromScene(weld->fiber1->scenePos());
    QPointF pointB = mapFromScene(weld->fiber2->scenePos());

    // find right corner of left item
    if (pointB.x() > pointA.x())
        pointA.rx() += weld->fiber1->rect().width();
    else
        pointB.rx() += weld->fiber2->rect().width();

    // find center of height
    pointA.ry() += weld->fiber1->rect().height() / 2;
    pointB.ry() += weld->fiber2->rect().height() / 2;

    weld->setLine(QLineF(pointA, pointB));
}

void Fdiagram::drawHomeWeld(FhomeWeld *homeWeld)
{
    QPointF point = mapFromScene(homeWeld->fiber->scenePos());

    point.rx() += homeWeld->fiber->rect().width();
    point.ry() += homeWeld->fiber->rect().height() / 2;

    homeWeld->setPos(point);
}
FMap *Fdiagram::getMap() const
{
    return map;
}

QString Fdiagram::getStreet() const
{
    return streetCombo->currentText();
}

QString Fdiagram::getBuild() const
{
    return buildCombo->currentText();
}

void Fdiagram::setBuild(QString s)
{
    int pos = buildCombo->findText(s);
    if (pos >= 0)
        buildCombo->setCurrentIndex(pos);
}

void Fdiagram::setStreet(QString s)
{
    int pos = streetCombo->findText(s);
    if (pos >= 0)
        streetCombo->setCurrentIndex(pos);
}

void Fdiagram::setMap(FMap *value)
{
    map = value;
}

void Fdiagram::toPrint()
{
    foreach (Fcable *cable, cables) {
        cable->toPrint();
    }
}

void Fdiagram::toView()
{
    foreach (Fcable *cable, cables) {
        cable->toView();
    }
}

void Fdiagram::setAddress(QString s, QString b)
{
    int pos = streetCombo->findText(s);
    if (pos >= 0)
        streetCombo->setCurrentIndex(pos);
    else {
        streetCombo->addItem(s);
        streetCombo->setCurrentIndex(streetCombo->count() - 1);
    }

    pos = buildCombo->findText(b);
    if (pos >= 0)
        buildCombo->setCurrentIndex(pos);
    else {
        buildCombo->addItem(b);
        buildCombo->setCurrentIndex(buildCombo->count() - 1);
    }
}

QMap<QString, int> Fdiagram::getOrder() const
{
    QMap<QString, int> order;
    int i = 0;
    foreach (Fcable *cable, cables) {
        order.insert(cable->getAddress(), i++);
    }
    return order;
}

void Fdiagram::setOrder(QMap<QString, int> &orderMap)
{
    QVector<Fcable *> newOrder(cables.size());
    foreach (Fcable *cable, cables) {
        int i = orderMap.value(cable->getAddress());
        newOrder[i] = cable;
    }
    cables = newOrder;
    resize();
}

