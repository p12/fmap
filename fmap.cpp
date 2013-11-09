#include <QtGui>
#include <QtSvg>
#include "fmap.h"


FMap::FMap(QWidget *parent): QMainWindow(parent)
{
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addText("Hello, world!");
    QGraphicsSvgItem *map = new QGraphicsSvgItem("/home/pak/projects/FMap/map.svg");
    scene->addItem(map);

    QGraphicsView *view = new QGraphicsView(scene);

    view->setMinimumSize(700, 700);
    view->show();


//    QHBoxLayout *layout = new QHBoxLayout;
//    layout->addWidget(&view);

//    QWidget *widget = new QWidget;
//    widget->setLayout(layout);
//    setCentralWidget(widget);
//    widget->show();

    QAction * cableAdd = new QAction("AddCable", this);
    QMenu *add = menuBar()->addMenu(tr("&Add"));
    add->addAction(cableAdd);
    connect(cableAdd, SIGNAL(triggered()), this, SLOT(addCable()));

    setCentralWidget(view);

}

void FMap::addCable()
{
    setCursor(Qt::CrossCursor);
}
