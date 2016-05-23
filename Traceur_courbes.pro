#-------------------------------------------------
#
# Project created by QtCreator 2016-05-23T12:34:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Traceur_courbes
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    renderarea.cpp

HEADERS  += mainwindow.h \
    renderarea.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11
