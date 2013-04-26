The file .pro to build and run the project must contain at least : 

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FenClientHttp
TEMPLATE = app


SOURCES += main.cpp\
    ClientHttp.cpp

HEADERS  += ClientHttp.h
