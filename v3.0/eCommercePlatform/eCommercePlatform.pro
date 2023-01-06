#-------------------------------------------------
#
# Project created by QtCreator 2021-04-14T20:22:20
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = eCommercePlatform
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    widgetregister.cpp \
    widgetmenu.cpp \
    user.cpp \
    additems.cpp \
    changepassword.cpp \
    edititem.cpp \
    items_book.cpp \
    items_clothes.cpp \
    items_elect.cpp \
    seller.cpp \
    send_info.cpp

HEADERS  += widget.h \
    widgetregister.h \
    widgetmenu.h \
    user.h \
    additems.h \
    changepassword.h \
    edititem.h \
    user_virtual.h \
    items_virtual.h \
    items_book.h \
    items_clothes.h \
    items_elect.h \
    seller.h \
    send_info.h

FORMS    += widget.ui \
    widgetregister.ui \
    widgetmenu.ui \
    additems.ui \
    changepassword.ui \
    edititem.ui

CONFIG +=C++11
