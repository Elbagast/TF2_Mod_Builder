
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
    abstract_observer.cpp \
    entity_definition.cpp \
    entity_id.cpp \
    entity_manager.cpp \
    signal.cpp \
    signal_entity.cpp \
    signal_entity_name_changed.cpp \
    signal_source.cpp \
    variant.cpp \
    internal/abstract_command.cpp \
    internal/abstract_entity_icon.cpp \
    internal/abstract_entity_maker.cpp \
    internal/abstract_entity_name.cpp \
    internal/abstract_entity_tooltip.cpp \
    internal/abstract_entity_type.cpp \
    internal/command_history.cpp \
    internal/entity.cpp \
    internal/entity_collection.cpp \
    internal/entity_commands.cpp \
    internal/entity_definition_maker.cpp \
    internal/entity_factory.cpp \
    internal/entity_handle.cpp \
    internal/entity_icon.cpp \
    internal/entity_name.cpp \
    internal/entity_tooltip.cpp \
    internal/observer_manager.cpp \
    internal/entity_type.cpp \
    internal/name_utilities.cpp

HEADERS  += \
    abstract_observer.hpp \
    abstract_observer_fwd.hpp \
    entity_definition.hpp \
    entity_definition_fwd.hpp \
    entity_id.hpp \
    entity_id_fwd.hpp \
    entity_manager.hpp \
    entity_manager_fwd.hpp \
    signal.hpp \
    signal_entity.hpp \
    signal_entity_fwd.hpp \
    signal_entity_name_changed.hpp \
    signal_entity_name_changed_fwd.hpp \
    signal_fwd.hpp \
    signal_source.hpp \
    signal_source_fwd.hpp \
    variant.hpp \
    variant_fwd.hpp \
    internal/abstract_command.hpp \
    internal/abstract_command_fwd.hpp \
    internal/abstract_entity_icon.hpp \
    internal/abstract_entity_icon_fwd.hpp \
    internal/abstract_entity_maker.hpp \
    internal/abstract_entity_maker_fwd.hpp \
    internal/abstract_entity_name.hpp \
    internal/abstract_entity_name_fwd.hpp \
    internal/abstract_entity_tooltip.hpp \
    internal/abstract_entity_tooltip_fwd.hpp \
    internal/abstract_entity_type.hpp \
    internal/abstract_entity_type_fwd.hpp \
    internal/command_history.hpp \
    internal/command_history_fwd.hpp \
    internal/entity.hpp \
    internal/entity_collection.hpp \
    internal/entity_collection_fwd.hpp \
    internal/entity_commands.hpp \
    internal/entity_commands_fwd.hpp \
    internal/entity_definition_maker.hpp \
    internal/entity_factory.hpp \
    internal/entity_factory_fwd.hpp \
    internal/entity_fwd.hpp \
    internal/entity_handle.hpp \
    internal/entity_handle_fwd.hpp \
    internal/entity_icon.hpp \
    internal/entity_icon_fwd.hpp \
    internal/entity_name.hpp \
    internal/entity_name_fwd.hpp \
    internal/observer_manager.hpp \
    internal/observer_manager_fwd.hpp \
    internal/entity_type.hpp \
    internal/entity_type_fwd.hpp \
    internal/name_utilities.hpp \
    internal/entity_definition_maker_fwd.hpp

FORMS += \

OTHER_FILES +=

DISTFILES += \ 
    readme.md \
    readme.md

SUBDIRS += \
    sak.pro

