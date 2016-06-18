#-------------------------------------------------
#
# Project created by QtCreator 2016-03-25T16:51:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MX28_tutorial
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
        mx28.cpp

LIBS += /usr/lib/libdxl.a

HEADERS  += dialog.h \
           mx28.h

FORMS    += dialog.ui
