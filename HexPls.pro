TEMPLATE = app
CONFIG += console c++11
QMAKE_CXXFLAGS += -std=c++11
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += main.cpp \
    board.cpp \
    quickfindunionfind.cpp \
    quickunionunionfind.cpp

HEADERS += \
    board.h \
    quickfindunionfind.h \
    quickunionunionfind.h
