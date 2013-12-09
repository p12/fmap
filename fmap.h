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
    void createBox();
    void createCable();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    QPointF a;
    bool inCreateBox;

protected:
    void mousePressEvent(QMouseEvent *);
};

#endif // FMAP_H
