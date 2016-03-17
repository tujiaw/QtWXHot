#-------------------------------------------------
#
# Project created by QtCreator 2016-03-14T13:25:27
#
#-------------------------------------------------

QT       += core gui network webkitwidgets
TRANSLATIONS = chinese.ts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WXHot
TEMPLATE = app

INCLUDEPATH += main \
        model \
        util \
        view

SOURCES += view/articleitemwidget.cpp \
    view/dropwidget.cpp \
    view/httpimagelabel.cpp \
    view/settingwidget.cpp \
    main/dialog.cpp \
    main/main.cpp \
    main/systemtray.cpp \
    model/article.cpp \
    util/json.cpp

HEADERS  += view/articleitemwidget.h \
    view/dropwidget.h \
    view/httpimagelabel.h \
    view/settingwidget.h \
    main/dialog.h \
    main/systemtray.h \
    model/article.h \
    util/json.h

FORMS    += main/dialog.ui \
    view/settingwidget.ui

RESOURCES += \
    res.qrc
