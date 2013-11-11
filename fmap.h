#ifndef FMAP_H
#define FMAP_H

#include <QMainWindow>
class QGraphicsScene;
class LinePoints;

class FMap : public QMainWindow
{
    Q_OBJECT

public:
    FMap(QWidget* parent = 0);

public slots:
    void addCable();
    void setPoint(QPoint p);

private:
    QGraphicsScene *scene;
    LinePoints *getPoint;
    QPoint a;
};

#endif // FMAP_H
