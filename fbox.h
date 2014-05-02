#ifndef FBOX_H
#define FBOX_H

#include <QGraphicsEllipseItem>
class Fdiagram;
class Fline;

class Fbox : public QGraphicsEllipseItem
{
public:
    Fbox();
    void setupFilter();
    Fdiagram *diagram;
    QVector<Fline *> lines;
    enum { Type = UserType + 1 };
    int type() const
        {
            return Type;
        }
};

#endif // FBOX_H
