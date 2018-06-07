DIR_HOME=/home/pi/bims

TARGET = database
TEMPLATE = lib
DEFINES += NETWORK_LIBRARY
DESTDIR = $$DIR_HOME/lib
CONFIG += staticlib
CONFIG += debug
CONFIG += console
CONFIG += thread
QT -= gui
QT += core network sql
#QT += websockets 
MOC_DIR = ./.moc
OBJECTS_DIR = ./.obj
INCLUDEPATH += $$DIR_HOME/include

SOURCES += \
	  dbms.cpp 

HEADERS += \
    dbms.h 
    
headers.files  = $$HEADERS
headers.path   = $$DIR_HOME/include
INSTALLS += headers

