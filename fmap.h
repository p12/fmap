#ifndef FMAP_H
#define FMAP_H

#include <QMainWindow>
#include <QVector>
#include <QPair>
class QGraphicsScene;
class QGraphicsView;
class Fbox;
class Fdiagram;
class Fline;
class Ffiber;
class Fweld;
class FhomeWeld;
class Fscene;
class FdiagramStack;


class FMap : public QMainWindow
{
    Q_OBJECT

public:
    FMap(QWidget* parent = 0);

public slots:
    void createBox();
    void createLine();
    void createWeld();
    void createHomeWeld();
    void save();
    void open();
    void del();
    void zoomIn();
    void zoomOut();

private:
    QGraphicsScene *scene;
//    Fscene *scene;
    QGraphicsScene *diagramScene;
    FdiagramStack *stack;
    QGraphicsView *view, *diagramView;
    bool inCreateBox;
    QVector<Fbox *> boxes;
    QVector<Fdiagram *> diagrams;
    QVector<Fline *> lines;
    QVector<Fweld *> welds;
    void drawBox(QPointF point);
    void drawCable(Fbox *aBox, Fbox *bBox, int moduleCount, int fiberCount);
    void drawWeld(Ffiber *a, Ffiber *b);
    void drawHomeWeld(Ffiber *fiber);
    void delCable(Fline *line);
    void delWeld(Fweld *w);
    void delHomeWeld(FhomeWeld *homeWeld);

protected:
    void mousePressEvent(QMouseEvent *);
};

#endif // FMAP_H
