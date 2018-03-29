
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
    main.cpp \
    test_entity_id.cpp \
    dummy_signal.cpp \
    dummy_observer.cpp \
    test_observer_manager.cpp \
    test_project.cpp \
    dummy_entity_maker.cpp \
    test_entity_maker.cpp \
    dummy_entity.cpp

HEADERS += \
    test_entity_id.hpp \
    dummy_signal.hpp \
    dummy_observer.hpp \
    test_observer_manager.hpp \
    test_project.hpp \
    dummy_entity_maker.hpp \
    test_entity_maker.hpp \
    dummy_entity.hpp


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

