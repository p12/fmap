#ifndef FMAP_H
#define FMAP_H

#include <QMainWindow>
class QGraphicsScene;
class QGraphicsView;
class GetPoint;

class FMap : public QMainWindow
{
    Q_OBJECT

public:
    FMap(QWidget* parent = 0);

public slots:
    void addCable();
    void setPoint();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    GetPoint *getPoint;
    QPoint a;
    bool inAddCable;

protected:
    void mousePressEvent(QMouseEvent *);
};

#endif // FMAP_H
