TEMPLATE = app
TARGET = NYSSE

QT += core gui widgets network multimedia

CONFIG += c++14

SOURCES += \
    actors/player.cpp \
    actors/helicopter.cpp \
    actors/scooter.cpp \
    actors/taxi.cpp \
    actors/walk.cpp \
    city.cpp \
    creategame.cpp \
    game_engine.cpp \
    main.cc \
    mainwindow.cpp \
    playerturndialog.cpp \
    settingsdialog.cpp \
    statistics.cpp \ \
    stops/atm.cpp \
    stops/bar.cpp

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/ -lCourseLib

INCLUDEPATH += \
    $$PWD/../Course/CourseLib

DEPENDPATH += \
    $$PWD/../Course/CourseLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/libCourseLib.a

HEADERS += \
    actors/player.hh \
    actors/helicopter.hh \
    actors/scooter.hh \
    actors/taxi.hh \
    actors/walk.hh \
    city.hh \
    game_engine.h \
    mainwindow.h \
    playerturndialog.hh \
    settingsdialog.hh \
    statistics.hh\ \
    stops/atm.hh \
    stops/bar.hh

FORMS += \
    playerturndialog.ui \
    mainwindow.ui \
    settingsdialog.ui

RESOURCES += \
    graphics/
