
# Qt bits
#==============================
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sak
TEMPLATE = lib
CONFIG += staticlib
CONFIG += static
CONFIG += threads
#CONFIG += object_parallel_to_source

# Compiler Flags
#==============================
# Getting MinGW to use C++14 features like std::make_unique
mingw {
    QMAKE_CXXFLAGS += -std=gnu++14
}

# the fuck is going on
# Need this for a subproject to find the QT includes
#INCLUDEPATH += $${PWD}/..

# Boost
#==============================
# If we use this instead of LIBS it compiles but doesn't work
#QMAKE_LIBDIR += D:/Programming/C++/Boost/boost_1_57_0/stage/lib

# Define custom variables to stitch together, these probably need to be edited for other systems
BOOST_INCLUDE_DIR = D:/Programming/C++/Boost/boost_1_57_0
BOOST_LIBRARY_DIR = $${BOOST_INCLUDE_DIR}/stage/lib
BOOST_LIBRARIES += boost_filesystem
BOOST_LIBRARIES += boost_any
BOOST_LIBRARIES += boost_variant
BOOST_LIBRARIES += boost_bind
BOOST_LIBRARIES += boost_signals2

BOOST_COMPILER = -mgw49
BOOST_VERSION = -1_57
BOOST_THREADS = -mt
BOOST_DEBUG = -d

# Must specify the library for MinGW, if the filename is libfoobar-a-b-blah.a then this is -lfoobar-a-b-blah
#LIBS += -LD:/Programming/C++/Boost/boost_1_57_0/stage/lib
LIBS += -L$${BOOST_LIBRARY_DIR}
# debug versions
mingw:debug {

    # Simple way, do per library:
    #LIBS += -lboost_filesystem-mgw49-mt-d-1_57
    # Automated way:
    for(library, BOOST_LIBRARIES) {
        LIBS += -l$${library}$${BOOST_COMPILER}$${BOOST_THREADS}$${BOOST_DEBUG}$${BOOST_VERSION}
    }
}
# release versions
mingw:!debug {
    # Simple way, do per library:
    #LIBS += -lboost_filesystem-mgw49-mt-1_57
    # Automated way:
    for(library, BOOST_LIBRARIES) {
        LIBS += -l$${library}$${BOOST_COMPILER}$${BOOST_THREADS}$${BOOST_VERSION}
    }
}
# msvc doesn't need this, it can find the right .lib files on its own

INCLUDEPATH += $${BOOST_INCLUDE_DIR}
#INCLUDEPATH += "D:/Programming/C++/Boost/boost_1_57_0"
DEPENDPATH += $${BOOST_LIBRARY_DIR}
#DEPENDPATH += "D:/Programming/C++/Boost/boost_1_57_0/stage/lib"


include($$PWD/../library_flamingo.pri)

# Included Files
#==============================

SOURCES += \
    class_definitions.cpp \
    data.cpp \
    data_definitions.cpp \
    gui/line_edit.cpp \
    abstract_member_edit_widget.cpp \
    handle.cpp \
    handle_factory.cpp \
    project_data.cpp \
    tag.cpp \
    abstract_project_signalbox.cpp \
    name_utilities.cpp

HEADERS  += \
    class_definitions.hpp \
    class_definitions_fwd.hpp \
    data.hpp \
    data_definitions.hpp \
    data_definitions_fwd.hpp \
    data_fwd.hpp \
    gui/line_edit.hpp \
    abstract_member_edit_widget.hpp \
    abstract_member_edit_widget_fwd.hpp \
    handle.hpp \
    handle_factory.hpp \
    handle_factory_fwd.hpp \
    handle_fwd.hpp \
    project_data.hpp \
    project_data_fwd.hpp \
    tag.hpp \
    tag_fwd.hpp \
    abstract_project_signalbox.hpp \
    abstract_project_signalbox_fwd.hpp \
    name_utilities.hpp

FORMS += \

OTHER_FILES +=

DISTFILES += 

