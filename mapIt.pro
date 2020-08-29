#-------------------------------------------------
#
# Project created by QtCreator 2018-06-05T18:30:40
#
#-------------------------------------------------

QT       += core gui webenginewidgets webchannel

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mapIt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    graph.cpp

HEADERS += \
        mainwindow.h \
    data.h \
    graph.h

FORMS += \
        mainwindow.ui

#mac {
#  Resources.files += "map.html"
# you can put more of these as you need, and it can even copy folders
# Resources.files += what you need
#  Resources.path = Contents/MacOS
#  QMAKE_BUNDLE_DATA += Resources
#}
