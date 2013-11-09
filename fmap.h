#ifndef FMAP_H
#define FMAP_H

#include <QMainWindow>

class FMap : public QMainWindow
{
    Q_OBJECT

public:
    FMap(QWidget* parent = 0);

public slots:
    void    addCable();

};

#endif // FMAP_H
