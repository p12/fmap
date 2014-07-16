#include "testfbox.h"
#include "fdiagramstack.h"
#include "fline.h"
#include <QtGui>

TestFbox::TestFbox(QObject *parent) :
    QObject(parent)
{
    box.setAddress("121", "Street");
}

void TestFbox::getAddress()
{
    QCOMPARE(box.getAddress(), QString("Street 121"));
}

void TestFbox::getBuild()
{
    QCOMPARE(box.getBuild(), QString("121"));
}

void TestFbox::getStreet()
{
    QCOMPARE(box.getStreet(), QString("Street"));
}

void TestFbox::getStack()
{
    FdiagramStack* stack = new FdiagramStack;
    box.setStack(stack);
    QCOMPARE(box.getStack(), stack);
}
