#ifndef FMAP_H
#define FMAP_H

#include <QMainWindow>
#include <QVector>
class QGraphicsScene;
class QGraphicsView;
class QGraphicsEllipseItem;
class QGraphicsLineItem;

class FMap : public QMainWindow
{
    Q_OBJECT

public:
    FMap(QWidget* parent = 0);

public slots:
    void createBox();
    void createCable();
    void save();
    void open();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    QPointF a;
    bool inCreateBox;
    QVector<QGraphicsEllipseItem *> boxVec;
    QVector<QGraphicsLineItem *> cblVec;

    void drawBox(QPointF p);

protected:
    void mousePressEvent(QMouseEvent *);
};

#endif // FMAP_H
