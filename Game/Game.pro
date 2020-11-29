TEMPLATE = app
TARGET = NYSSE

QT += core gui widgets network multimedia

CONFIG += c++14

SOURCES += \
    city.cpp \
    creategame.cpp \
    game_engine.cpp \
    helicopter.cpp \
    main.cc \
    mainwindow.cpp \
    player.cpp \
    playerturndialog.cpp \
    scooter.cpp \
    settingsdialog.cpp \
    statistics.cpp \
    taxi.cpp \
    walk.cpp

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
    city.hh \
    game_engine.h \
    helicopter.hh \
    mainwindow.h \
    player.hh \
    playerturndialog.hh \
    scooter.hh \
    settingsdialog.hh \
    statistics.hh\
    taxi.hh \
    walk.hh

FORMS += \
    playerturndialog.ui \
    mainwindow.ui \
    settingsdialog.ui

RESOURCES += \
    graphics/
