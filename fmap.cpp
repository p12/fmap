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

    setCentralWidget(view);

//    QHBoxLayout *layout = new QHBoxLayout;
//    layout->addWidget(&view);

//    QWidget *widget = new QWidget;
//    widget->setLayout(layout);
//    setCentralWidget(widget);
//    widget->show();

    QAction * cableAdd = new QAction("AddCable");
    QMenu *add = menuBar()->addMenu("Add");
    add->addAction(cableAdd);
        // Menus
//    addAction(cableAdd);
    // Actions

}

FMap::addCable()
{
    setCursor(Qt::CrossCursor);
}
