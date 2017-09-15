#-------------------------------------------------
#
# Project created by QtCreator 2015-12-21T21:02:57
#
#-------------------------------------------------

QT       += core gui
QT+=sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = weday1
TEMPLATE = app


SOURCES += main.cpp\
    table.cpp \
    newtable.cpp \
    newclass.cpp \
    newtutor.cpp \
    newpro.cpp \
    tutor.cpp \
    assist.cpp \
    problem.cpp \
    classtable.cpp \
    Semail.cpp

HEADERS  += \
    table.h \
    connection.h \
    newtable.h \
    newclass.h \
    newtutor.h \
    newpro.h \
    tutor.h \
    assist.h \
    problem.h \
    classtable.h \
    Semail.h

FORMS    += \
    newtable.ui \
    newclass.ui \
    newtutor.ui \
    newpro.ui \
    classtable.ui

DISTFILES += \
    test.db \
    t.db
