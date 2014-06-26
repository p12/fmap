#ifndef FLOGICFIBER_H
#define FLOGICFIBER_H

#include <QVector>
class Ffiber;
class Fbox;

class FlogicFiber
{
public:
    FlogicFiber();
    QVector<Ffiber *> fibers;
    QVector<Fbox *>   boxes;
};

#endif // FLOGICFIBER_H
