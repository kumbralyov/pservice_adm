#-------------------------------------------------
#
# Project created by QtCreator 2017-03-05T17:02:41
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pservice_adm
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    adm_form.cpp \
    conf_form.cpp \
    login_form.cpp

HEADERS  += mainwindow.h \
    adm_form.h \
    conf_form.h \
    login_form.h
