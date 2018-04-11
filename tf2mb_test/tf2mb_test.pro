
# Qt bits
#==============================
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tf2mb_test
TEMPLATE = app
CONFIG += static
CONFIG += threads
#CONFIG += object_parallel_to_source
CONFIG += c++17

# Link to sak subproject
#==========================================
# Looking in the other subproject's build location
CONFIG(release, debug|release): LIBRARY_DIR = $$OUT_PWD/../sak/release/
CONFIG(debug, debug|release): LIBRARY_DIR = $$OUT_PWD/../sak/debug/

LIBS += -L$${LIBRARY_DIR} -lsak

# Need one of these for each .lib made
LIBS += -lsak

DEPENDPATH += $${LIBRARY_DIR}

CONFIG(release, debug|release):DEPENDPATH += $$OUT_PWD/../tf2mb/release/
CONFIG(debug, debug|release):DEPENDPATH += $$OUT_PWD/../tf2mb/debug/


SOURCES += \
    main.cpp \
    test_project.cpp

HEADERS += \
    test_project.hpp


include($$PWD/../library_flamingo.pri)

INCLUDE_DIR = $${PWD}/..
INCLUDEPATH += $${INCLUDE_DIR}
