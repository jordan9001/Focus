#-------------------------------------------------
#
# Project created by QtCreator 2014-12-13T22:02:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Productivity
TEMPLATE = app
ICON = icon.icns


SOURCES += main.cpp\
        widget.cpp \
    settingsscreen.cpp \
    completedetails.cpp \
    break.cpp

HEADERS  += widget.h \
    settingsscreen.h \
    completedetails.h \
    break.h

FORMS    += widget.ui \
    settingsscreen.ui \
    completedetails.ui \
    break.ui

DISTFILES +=
