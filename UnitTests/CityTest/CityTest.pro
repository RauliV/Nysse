QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

TARGET = tst_setclock

SOURCES +=  tst_setclock.cpp \



HEADERS += \
            city.hh


INCLUDEPATH += \
            ../../Game

DEPENDPATH  += ../../Game
