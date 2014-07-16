#-------------------------------------------------
#
# Project created by QtCreator 2013-11-02T19:42:31
#
#-------------------------------------------------

QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FMap
TEMPLATE = subdirs
CONFIG+=ordered

SUBDIRS = \
    src \
    app \
    tests
    
app.depends = src
tests.depends = src


