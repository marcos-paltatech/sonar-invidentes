#-------------------------------------------------
#
# Project created by QtCreator 2012-02-26T15:01:49
#
#-------------------------------------------------

QT       += core
QT       -= gui

TARGET = flashmem
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DESTDIR = bin
OBJECTS_DIR = obj
MOC_DIR = obj
QMAKE_CXXFLAGS_RELEASE = -march=native -O3 -fomit-frame-pointer -fPIC

INCLUDEPATH += ./qserialdevice/src
QMAKE_LIBDIR += ./qserialdevice/src/build/release
LIBS += -lqserialdevice
QMAKE_LFLAGS += -Wl,-R,\'../qserialdevice/src/build/release\'

SOURCES += main.cpp
