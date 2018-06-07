#-------------------------------------------------
#
# Project created by QtCreator 2018-03-27T21:47:15
#
#-------------------------------------------------
DIR_HOME=/home/pi/bims/

TEMPLATE = app
TARGET = gpiocontrol
DEFINES += QT_MESSAGELOGCONTEXT
DESTDIR = /home/pi/apts/bin
QT += gui
QT += core network sql
#QT += websockets
CONFIG += debug
CONFIG += console
CONFIG += thread
MOC_DIR = ./.moc
OBJECTS_DIR = ./.obj
INCLUDEPATH += $$DIR_HOME/include
LIBS += -L$$DIR_HOME/lib -lwiringPi

SOURCES += \
    main.cpp \
    gpiocontrol.cpp

HEADERS += 
		gpiocontrol.h\
    

