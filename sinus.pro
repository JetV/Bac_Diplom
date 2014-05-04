#-------------------------------------------------
#
# Project created by QtCreator 2014-04-14T16:17:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sinus
TEMPLATE = app

#LIBS        += -LE:\include\my_dll -ldll_test
SOURCES += main.cpp\
        mainwindow.cpp \
    ctworker.cpp

HEADERS  += mainwindow.h \
    ctworker.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    readme.txt
