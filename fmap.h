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
class FlogicFiber;


class FMap : public QMainWindow
{
    Q_OBJECT

public:
    FMap(QWidget* parent = 0);
    void delLogicWeld(Fweld *w);

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
    void tracePath();

private:
//    Fscene *scene;
    QGraphicsScene *diagramScene, *scene;
    FdiagramStack *stack;
    QGraphicsView *view, *diagramView;
    bool inCreateBox;
    QVector<Fbox *> boxes;
    QVector<Fline *> lines;
    QVector<FlogicFiber *> logicFibers;
    QVector<QVector<FlogicFiber *> > channels;
    void drawBox(QPointF point);
    void drawCable(Fbox *box1, Fbox *box2, int moduleCount, QVector<FlogicFiber *> &fibers);
    void drawWeld(Ffiber *a, Ffiber *b);
    void drawHomeWeld(Ffiber *fiber);
    void delCable(Fline *line);
    void delWeld(Fweld *w);
    void delHomeWeld(FhomeWeld *homeWeld);

protected:
    void mousePressEvent(QMouseEvent *);
};

#endif // FMAP_H
