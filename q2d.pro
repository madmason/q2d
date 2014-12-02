#-------------------------------------------------
#
# Project created by QtCreator 2014-12-02T16:41:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = q2d
TEMPLATE = app


SOURCES +=\
        MainWindow.cpp \
    model/ModelElement.cpp \
    patterns/Observable.cpp \
    model/Node.cpp \
    model/Conductor.cpp \
    model/Component.cpp \
    model/Model.cpp \
    Document.cpp \
    view/Schematic.cpp \
    Project.cpp \
    ApplicationContext.cpp \
    Application.cpp \
    Main.cpp

HEADERS  += MainWindow.h \
    model/ModelElement.h \
    patterns/Observable.h \
    patterns/Observer.h \
    model/Node.h \
    model/Conductor.h \
    model/PortDirection.h \
    model/Component.h \
    model/Model.h \
    Document.h \
    view/Schematic.h \
    Project.h \
    ApplicationContext.h \
    Application.h

FORMS    += MainWindow.ui
