#include "flogicfiber.h"

int FlogicFiber::nextId = 0;

FlogicFiber::FlogicFiber()
{
    id = nextId++;
}
int FlogicFiber::getId() const
{
    return id;
}
