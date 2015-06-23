TEMPLATE = app
CONFIG += console
CONFIG -= qt

INCLUDEPATH += $$_PRO_FILE_PWD_/shapelib-1.3.0/shapefil.h
LIBS += $$_PRO_FILE_PWD_/shapelib-1.3.0/libshp.a

SOURCES += main.cpp

