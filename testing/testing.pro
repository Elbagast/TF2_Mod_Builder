
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
    test_data.cpp \
    test_class_definitions.cpp \
    test_handle.cpp \
    test_handle_factory.cpp \
    test_abstract_project_interface.cpp \
    test_project_signalbox_data.cpp \
    test_project_handle_factory.cpp \
    test_project_handle_data.cpp \
    test_id.cpp \
    test_abstract_project_signalbox.cpp \
    test_project_interface.cpp \
    dummy_project_signalbox.cpp \
    dummy_project_interface.cpp

HEADERS += \
    test_data.hpp \
    test_class_definitions.hpp \
    test_handle.hpp \
    test_handle_factory.hpp \
    test_abstract_project_interface.hpp \
    test_project_signalbox_data.hpp \
    test_project_handle_factory.hpp \
    test_project_handle_data.hpp \
    test_id.hpp \
    test_abstract_project_signalbox.hpp \
    test_project_interface.hpp \
    dummy_project_signalbox.hpp \
    dummy_project_interface.hpp


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

