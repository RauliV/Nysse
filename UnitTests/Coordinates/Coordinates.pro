QT += testlib
QT += gui core widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_cvalues.cpp \
            ../../Game/setboard.cpp \
            ../../Game/city.cpp \
            ../../Game/actors/taxi.cpp \
            ../../Game/actors/player.cpp \
            ../../Game/stops/bar.cpp \
            ../../Game/stops/atm.cpp \
            ../../Game/actors/scooter.cpp \
            ../../Game/locationitem.cpp\
            ../../Game/mainwindow.cpp \
            ../../Game/gameengine.cpp \
            ../../Game/settingsdialog.cpp \
            ../../Game/actoritem.cpp \
            ../../Game/staticitem.cpp \
            ../../Course/CourseLib/errors/gameerror.cc \
            ../../Course/CourseLib/graphics/simpleactoritem.cpp \
            ../../Course/CourseLib/actors/nysse.cc \
            ../../Course/CourseLib/actors/stop.cc \
            ../../Course/CourseLib/actors/passenger.cc \
            ../../Course/CourseLib/core/location.cc

HEADERS +=  \
            ../../Game/settingsdialog.hh \
            ../../Game/actoritem.hh \
            ../../Game/setboard.hh \
            ../../Game/gameengine.hh \
            ../../Game/city.hh \
            ../../Game/actors/taxi.hh \
            ../../Game/actors/scooter.hh \
            ../../Game/actors/player.hh \
            ../../Game/stops/bar.hh \
            ../../Game/stops/atm.hh \
            ../../Game/locationitem.hh\
            ../../Game/mainwindow.h \
            ../../Course/CourseLib/actors/passenger.hh \
            ../../Course/CourseLib/actors/nysse.hh \
            ../../Course/CourseLib/core/location.hh

FORMS += \
            ../../Game/mainwindow.ui \
            ../../Game/settingsdialog.ui

INCLUDEPATH += \
                ../../Game \
                ../../Course/CourseLib
