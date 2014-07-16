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
    int getId() const;

private:
    static int nextId;
    int id;
};

#endif // FLOGICFIBER_H
