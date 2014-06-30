#include "fdiagramstack.h"
#include "fdiagram.h"


void FdiagramStack::push(Fdiagram *diagram)
{
  diagrams << diagram;
  diagram->show();
  diagram->setPos(current);

  current.ry() += diagram->rect().height() + 25;
}

void FdiagramStack::pop(Fdiagram *diagram)
{
  int pos = diagrams.indexOf(diagram);
  if (pos < 0)
      return;
  current = diagrams[pos]->pos();
  diagrams[pos]->hide();
  diagrams.remove(pos);

  for (int i = pos; i < diagrams.size(); i++) {
      diagrams[i]->setPos(current);
      current.ry() += diagrams[i]->rect().height() + 25;
  }
}

void FdiagramStack::clear()
{
    foreach (Fdiagram *diagram, diagrams) {
        diagram->hide();
    }
    diagrams.clear();
    current = QPointF(0, 0);
}

