#include <QApplication>
#include "fmap.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FMap    map;
    map.show();

    return a.exec();
}
