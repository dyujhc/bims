#-------------------------------------------------
#
# Project created by QtCreator 2018-03-27T21:47:15
#
#-------------------------------------------------
DIR_HOME=/home/pi/bims/

TEMPLATE = app
TARGET = getlicense
DEFINES += QT_MESSAGELOGCONTEXT
DESTDIR = /home/pi/apts/bin
QT += core network
#QT += websockets
CONFIG += debug
CONFIG += console
CONFIG += thread
CONFIG -= app_bundle
MOC_DIR = ./.moc
OBJECTS_DIR = ./.obj
INCLUDEPATH += $$DIR_HOME/include

SOURCES += \
    getlicense.cpp \
    main.cpp 
    

HEADERS += \
		getlicense.h
		
		
    

