QT += core gui opengl widgets
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

SOURCES += main.cpp \
    grid.cpp \
    creature.cpp \
    display.cpp \
    coord.cpp \
    prey.cpp \
    hunter.cpp \
    random.cpp \
    nukes.cpp \
    tanks.cpp \
    graph.cpp

HEADERS += \
    grid.h \
    creature.h \
    display.h \
    Constant.h \
    coord.h \
    prey.h \
    hunter.h \
    random.h \
    nukes.h \
    tanks.h \
    graph.h

