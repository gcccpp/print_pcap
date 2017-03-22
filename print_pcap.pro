QT += core
QT -= gui

TARGET = print_pcap
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    parser.cpp \
    filter.cpp

HEADERS += \
    parser.h \
    filter.h

LIBS += -lpcap

