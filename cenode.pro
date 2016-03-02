#-------------------------------------------------
#
# Project created by QtCreator 2016-02-26T12:05:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cenode
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

DEFINES+= STATIC
QMAKE_CXXFLAGS_RELEASE += -std=c++11 -g0 -s -flto -Os
win32: CONFIG += static
win32: LIBS += -liconv
win32: LIBS += -L/usr/i686-w64-mingw32/lib/qt/plugins/platforms/ -lqwindows
