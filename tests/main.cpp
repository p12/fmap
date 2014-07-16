#include <QTest>
#include <QApplication>
#include "testfbox.h"

 int main(int argc, char** argv)
 {
     QApplication a(argc, argv);
    int status = 0;
    {
       TestFbox testBox;
       status |= QTest::qExec(&testBox, argc, argv);
    }
    return status;
 }
