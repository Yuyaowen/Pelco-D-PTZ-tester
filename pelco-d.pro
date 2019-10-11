#-------------------------------------------------
#
# Project created by QtCreator 2019-10-08T10:54:48
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pelco-d
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    protocol.cpp

HEADERS  += mainwindow.h \
    protocol.h

FORMS    += mainwindow.ui
