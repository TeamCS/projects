#-------------------------------------------------
#
# Project created by QtCreator 2014-02-23T13:13:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI_Calculator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    fraction.h \
    include.h \
    mixed.h \
    myQueue.h \
    myStack.h \
    node.h \
    Parsing.h \
    voidQueue.h \
    voidStack.h

FORMS    += mainwindow.ui
