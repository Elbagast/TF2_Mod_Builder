
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

mingw {
    QMAKE_CXXFLAGS += -std=gnu++14
}

TEMPLATE = app
TARGET = testing
#CONFIG += console
#CONFIG -= app_bundle
CONFIG += static
CONFIG += threads
#CONFIG += object_parallel_to_source

SOURCES += \
    main.cpp

HEADERS += \


#include($$PWD/../Library_Name.pri)

INCLUDE_DIR = $${PWD}/..
INCLUDEPATH += $${INCLUDE_DIR}
# Link to sak subproject

#==========================================
# Looking in the other subproject's build location
CONFIG(release, debug|release): LIBRARY_DIR = $$OUT_PWD/../sak/release/
CONFIG(debug, debug|release): LIBRARY_DIR = $$OUT_PWD/../sak/debug/

LIBS += -L$${LIBRARY_DIR} -lsak

# Need one of these for each .lib made
LIBS += -lsak

DEPENDPATH += $${LIBRARY_DIR}



DEPENDPATH += $${LIBRARY_DIR}
