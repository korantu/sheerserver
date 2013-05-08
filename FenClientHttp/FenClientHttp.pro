#-------------------------------------------------
#
# Project created by QtCreator 2013-04-23T18:33:47
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FenClientHttp
TEMPLATE = app

INCLUDEPATH += C:/Users/sheerServer/Projets/Qt/FileHash
#DEPENDPATH += C:/Users/sheerServer/Projets/Qt/FileHash-build-Desktop_Qt_5_0_1_MSVC2010_32bit-Debug/debug
LIBS+=  -LC:/Users/sheerServer/Projets/Qt/FileHash-build-Desktop_Qt_5_0_1_MSVC2010_32bit-Debug/debug -lFileHash


SOURCES += main.cpp\
        FenClientHttp.cpp \
    ClientHttp.cpp \
    sheer_cloud.cpp


HEADERS  += FenClientHttp.h \
    ClientHttp.h \
    sheer_cloud.h

FORMS += \
    form.ui
