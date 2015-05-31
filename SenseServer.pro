#-------------------------------------------------
#
# Project created by QtCreator 2014-12-21T17:38:42
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SenseServer
#QTPLUGIN += QSQLMYSQL
TEMPLATE = app

CONFIG += thread
CONFIG += c++11
CONFIG += static release

QMAKE_LFLAGS += -std=c++11
QMAKE_LFLAGS += -static -static-libgcc
LIBS += -static-libgcc
#INCLUDEPATH+="C:\progra~1\mysql\MySQL Server 5.6\include"
#LIBS+="C:\progra~1\mysql\MySQL Server 5.6\lib\libmysql.lib"

SOURCES += main.cpp\
        mainwindow.cpp \
    server.cpp \
    console.cpp \
    CRC/CRC16.cpp \
    config.cpp \
    help.cpp \
    client.cpp

HEADERS  += mainwindow.h \
    console.h \
    CRC/CRC16.h \
    server.h \
    config.h \
    help.h \
    client.h \
    view.h

FORMS += \
    mainwindow.ui \
    help.ui

RESOURCES += \
    icon.qrc
