#-------------------------------------------------
#
# Project created by QtCreator 2013-04-23T10:28:08
#
#-------------------------------------------------

QT       -= gui

TARGET = FileHash
TEMPLATE = lib

DEFINES += FILEHASH_LIBRARY

SOURCES += FileHash.cpp

HEADERS += FileHash.h\
        FileHash_global.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
