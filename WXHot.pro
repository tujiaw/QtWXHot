#-------------------------------------------------
#
# Project created by QtCreator 2016-03-14T13:25:27
#
#-------------------------------------------------

QT       += core gui network webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WXHot
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    article.cpp \
    json.cpp \
    articleitemwidget.cpp \
    httpimagelabel.cpp \
    dropwidget.cpp \
    systemtray.cpp

HEADERS  += dialog.h \
    article.h \
    json.h \
    articleitemwidget.h \
    httpimagelabel.h \
    dropwidget.h \
    systemtray.h

FORMS    += dialog.ui

RESOURCES += \
    res.qrc
