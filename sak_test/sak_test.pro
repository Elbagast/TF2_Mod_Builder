
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

mingw {
    QMAKE_CXXFLAGS += -std=gnu++14
}

TEMPLATE = app
TARGET = sak_test
#CONFIG += console
#CONFIG -= app_bundle
CONFIG += static
CONFIG += threads
#CONFIG += object_parallel_to_source
CONFIG += c++17

SOURCES += \
    main.cpp \
    test_entity_id.cpp \
    dummy_observer.cpp \
    test_observer_manager.cpp \
    dummy_entity_maker.cpp \
    test_entity_maker.cpp \
    test_io.cpp \
    test_entity_manager.cpp

HEADERS += \
    test_entity_id.hpp \
    dummy_observer.hpp \
    test_observer_manager.hpp \
    dummy_entity_maker.hpp \
    test_entity_maker.hpp \
    test_io.hpp \
    test_entity_manager.hpp


include($$PWD/../library_boost.pri)
include($$PWD/../library_flamingo.pri)

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

