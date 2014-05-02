#ifndef FMODULE_H
#define FMODULE_H

#include <QGraphicsRectItem>

class Fmodule : public QGraphicsRectItem
{
public:
    Fmodule();
    enum { Type = UserType + 8 };
    int type() const
        {
            return Type;
        }
};

#endif // FMODULE_H
