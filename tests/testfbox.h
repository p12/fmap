#ifndef TESTFBOX_H
#define TESTFBOX_H

#include <QTest>
#include <QObject>
#include "fbox.h"

class TestFbox : public QObject
{
    Q_OBJECT
public:
    explicit    TestFbox(QObject *parent = 0);
    
private slots:
    void        getAddress();
    void        getBuild();
    void        getStreet();
    void        getStack();
private:
    Fbox        box;
};

#endif // TESTFBOX_H
