include(../defaults.pri)

CONFIG   += qtestlib

TEMPLATE = app

CONFIG   += console
CONFIG   -= app_bundle

SOURCES += main.cpp \
    testfbox.cpp

LIBS += -L../src -lFMap

HEADERS += \
    testfbox.h
