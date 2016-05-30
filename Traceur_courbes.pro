#-------------------------------------------------
#
# Project created by QtCreator 2016-05-23T12:34:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Traceur_courbes
TEMPLATE = app


SOURCES += main.cpp \
        mainwindow.cpp \
    renderarea.cpp \
    function.cpp \
    rpn_utility.cpp

HEADERS  += mainwindow.h \
    renderarea.h \
    function.h \
    rpn_utility.h

FORMS    +=

QMAKE_CXXFLAGS += -std=c++1y

DISTFILES += \
    README.md
