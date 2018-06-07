#-------------------------------------------------
#
# Project created by QtCreator 2018-03-27T21:47:15
#
#-------------------------------------------------
DIR_HOME=/home/pi/bims

TEMPLATE = lib
TARGET = common
DEFINES += NETWORK_LIBRARY
DESTDIR = $$DIR_HOME/lib
QT -= gui
QT += core network sql
#QT += websockets 
CONFIG += staticlib
CONFIG += debug
CONFIG += console
CONFIG += thread
MOC_DIR = ./.moc
OBJECTS_DIR = ./.obj
INCLUDEPATH += $$DIR_HOME/include

SOURCES += \
				common.cpp \
				global.cpp \
				utimer.cpp


HEADERS += \
				common.h \
				global.h \
				utimer.h

headers.files  = $$HEADERS
headers.path   = $$DIR_HOME/include
INSTALLS += headers

