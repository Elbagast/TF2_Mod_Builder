
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
    gui/line_edit.cpp \
    abstract_member_edit_widget.cpp \
    name_utilities.cpp \
    command_history.cpp \
    abstract_command.cpp \
    entity_id.cpp \
    project.cpp \
    variant.cpp \
    entity_manager.cpp \
    entity_handle.cpp \
    entity.cpp \
    entity_factory.cpp \
    abstract_signal.cpp \
    abstract_entity_maker.cpp \
    observer_manager.cpp \
    abstract_observer.cpp \
    project_commands.cpp \
    entity_added_signal.cpp \
    abstract_entity_signal.cpp \
    entity_removed_signal.cpp \
    entity_outliner_request_signal.cpp \
    entity_editor_request_signal.cpp \
    entity_name_changed_signal.cpp

HEADERS  += \
    gui/line_edit.hpp \
    abstract_member_edit_widget.hpp \
    abstract_member_edit_widget_fwd.hpp \
    name_utilities.hpp \
    command_history.hpp \
    command_history_fwd.hpp \
    abstract_command.hpp \
    abstract_command_fwd.hpp \
    entity_id.hpp \
    entity_id_fwd.hpp \
    project.hpp \
    project_fwd.hpp \
    variant.hpp \
    variant_fwd.hpp \
    entity_manager.hpp \
    entity_handle.hpp \
    entity_handle_fwd.hpp \
    entity.hpp \
    entity_fwd.hpp \
    entity_manager_fwd.hpp \
    entity_factory.hpp \
    abstract_signal.hpp \
    abstract_signal_fwd.hpp \
    entity_factory_fwd.hpp \
    abstract_entity_maker.hpp \
    abstract_entity_maker_fwd.hpp \
    abstract_observer.hpp \
    abstract_observer_fwd.hpp \
    observer_manager.hpp \
    observer_manager_fwd.hpp \
    project_commands.hpp \
    project_commands_fwd.hpp \
    entity_added_signal.hpp \
    abstract_entity_signal.hpp \
    abstract_entity_signal_fwd.hpp \
    entity_removed_signal.hpp \
    entity_outliner_request_signal.hpp \
    entity_editor_request_signal.hpp \
    entity_name_changed_signal.hpp

FORMS += \

OTHER_FILES +=

DISTFILES += 

