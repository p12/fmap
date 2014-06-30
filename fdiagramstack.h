#ifndef FDIAGRAMSTACK_H
#define FDIAGRAMSTACK_H

#include <QVector>
#include <QPointF>

class QGraphicsScene;
class Fdiagram;

class FdiagramStack
{
public:
  void push(Fdiagram *diagram);
  void pop (Fdiagram *diagram);
  void clear();

private:
  QVector<Fdiagram *> diagrams;
  QPointF current;

};

#endif // FDIAGRAMSTACK_H
