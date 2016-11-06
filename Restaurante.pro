#-------------------------------------------------
#
# Project created by QtCreator 2016-10-28T18:24:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Restaurante
TEMPLATE = app


SOURCES += main.cpp\
    arraylist.cpp \
    controladora.cpp \
    dijkstra.cpp \
    floyd.cpp \
    kruskal.cpp \
    matriz.cpp \
    prim.cpp \
    boton.cpp \
    warshall.cpp

HEADERS  += \
    arraylist.h \
    controladora.h \
    dijkstra.h \
    floyd.h \
    kruskal.h \
    matriz.h \
    prim.h \
    boton.h \
    warshall.h

FORMS    +=

RESOURCES += \
    imagenes.qrc

DISTFILES += \
    Imagenes/piso cocina-01.jpg
