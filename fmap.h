#ifndef FMAP_H
#define FMAP_H

#include <QMainWindow>
class QGraphicsScene;
class QGraphicsView;

class FMap : public QMainWindow
{
    Q_OBJECT

public:
    FMap(QWidget* parent = 0);

public slots:
    void addCable();
    void drawBox();

private:
    QGraphicsScene *scene,
                   *dockScene;
    QGraphicsView *view,
                  *dockView;
    QPointF a;
    bool inAddCable;

protected:
    void mousePressEvent(QMouseEvent *);
};

#endif // FMAP_H
