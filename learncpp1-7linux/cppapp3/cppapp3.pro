TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    person.cpp \
    rectangle.cpp

HEADERS += \
    person.h \
    rectangle.h \
    funptr.hpp
