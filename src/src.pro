include(../defaults.pri)
QT      += svg xml
TARGET = FMap
TEMPLATE = lib

SOURCES += fmap.cpp \
    fdiagram.cpp \
    fbox.cpp \
    fline.cpp \
    fcable.cpp \
    ffiber.cpp \
    fweld.cpp \
    fhomeweld.cpp \
    fmodule.cpp \
    fscene.cpp \
    fdiagramstack.cpp \
    ftextitem.cpp \
    flogicfiber.cpp \
    fview.cpp

HEADERS  += fmap.h \
    fdiagram.h \
    fbox.h \
    fline.h \
    fcable.h \
    ffiber.h \
    fweld.h \
    fhomeweld.h \
    fmodule.h \
    fscene.h \
    fdiagramstack.h \
    ftextitem.h \
    flogicfiber.h \
    fcolors.h \
    fview.h
