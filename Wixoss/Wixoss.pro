#-------------------------------------------------
#
# Project created by QtCreator 2015-04-05T21:27:05
#
#-------------------------------------------------

QT       += core gui sql
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Wixoss
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    card.cpp \
    databaseaccessor.cpp

HEADERS  += mainwindow.h \
    card.h \
    databaseaccessor.h

FORMS    += mainwindow.ui
