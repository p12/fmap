#ifndef FMAP_H
#define FMAP_H

#include <QMainWindow>
#include <QVector>
#include <QPair>
class QGraphicsScene;
class QGraphicsView;
class Fbox;
class Fline;
class Ffiber;
class Fweld;
class FhomeWeld;


class FMap : public QMainWindow
{
    Q_OBJECT

public:
    FMap(QWidget* parent = 0);

public slots:
    void createBox();
    void createLine();
    void createHomeWeld();
    void save();
    void open();
    void del();
    void zoomIn();
    void zoomOut();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    bool inCreateBox;
    QVector<Fbox *> boxes;
    QVector<Fline *> lines;
    QVector<Fweld *> welds;
    void drawBox(QPointF point);
    void drawCable(Fbox *aBox, Fbox *bBox, int moduleCount, int fiberCount);
    void drawWeld(Ffiber *a, Ffiber *b);
    void drawHomeWeld(Ffiber *fiber);
    void delCable(Fline *l);
    void delWeld(Fweld *w);
    void delHomeWeld(FhomeWeld *homeWeld);

protected:
    void mousePressEvent(QMouseEvent *);
};

#endif // FMAP_H
