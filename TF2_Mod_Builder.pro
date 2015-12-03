#-------------------------------------------------
#
# Project created by QtCreator 2014-11-13T12:23:38
#
#-------------------------------------------------

# Qt bits
#==============================
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TF2_Mod_Builder
TEMPLATE = app

CONFIG += static
CONFIG += threads

# Compiler Flags
#==============================
# Getting MinGW to use C++14 features like std::make_unique
mingw {
    QMAKE_CXXFLAGS += -std=gnu++14
}



# Boost
#==============================
# If we use this instead of LIBS it compiles but doesn't work
#QMAKE_LIBDIR += D:/Programming/C++/Boost/boost_1_57_0/stage/lib

# Define custom variables to stitch together, these probably need to be edited for other systems
BOOST_INCLUDE_DIR = D:/Programming/C++/Boost/boost_1_57_0
BOOST_LIBRARY_DIR = $${BOOST_INCLUDE_DIR}/stage/lib
BOOST_LIBRARIES += boost_filesystem
BOOST_LIBRARIES += boost_any
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

# Included Files
#==============================


SOURCES += main.cpp\
    saklib/internal/test.cpp \
    saklib/internal/null_handle.cpp \
    saklib/internal/type_string.cpp \
    saklib/internal/exceptions/bad_attribute_data_type.cpp \
    saklib/internal/attribute_data.cpp \
    saklib/internal/exceptions/bad_element_data_type.cpp \
    saklib/internal/attribute_data__test.cpp \
    saklib/internal/element_data.cpp \
    saklib/internal/element_data__test.cpp \
    saklib/internal/element_data_manager__test.cpp \
    saklib/internal/element_data_manager.cpp \
    saklib/internal/undoable_element_data_manager.cpp \
    saklib/element.cpp \
    saklib/internal/exceptions/bad_data_handle.cpp \
    saklib/internal/element_data_definition_manager.cpp \
    saklib/internal/command_history.cpp \
    saklib/internal/command.cpp \
    saklib/internal/attribute_data_handle.cpp \
    saklib/internal/element_data_handle.cpp \
    saklib/internal/attribute_data_boolean_type.cpp \
    saklib/internal/attribute_data_boolean_type__test.cpp \
    saklib/internal/attribute_data_floating_point_type.cpp \
    saklib/internal/attribute_data_integral_type.cpp \
    saklib/internal/attribute_data_integral_type__test.cpp \
    saklib/internal/attribute_data_handle_bool.cpp \
    saklib/internal/attribute_data_handle_int.cpp \
    saklib/internal/undoable_element_data_handle.cpp \
    saklib/internal/undoable_attribute_data_handle.cpp \
    saklib/internal/undoable_attribute_data_handle_bool.cpp \
    saklib/internal/undoable_attribute_data_handle_int.cpp \
    saklib/internal/undoable_element_data_manager__test.cpp

HEADERS  += \
    saklib/zzz_refactoring.h \
    saklib/internal/handle.h \
    saklib/internal/null_handle.h \
    saklib/internal/handle_factory.h \
    saklib/internal/test.h \
    saklib/internal/handle__inline.h \
    saklib/internal/handle__fwd.h \
    saklib/internal/null_handle__fwd.h \
    saklib/internal/handle_factory__inline.h \
    saklib/internal/null_handle__inline.h \
    saklib/internal/handle_factory__fwd.h \
    saklib/internal/type_string.h \
    saklib/internal/type_string__fwd.h \
    saklib/internal/reference_counter.h \
    saklib/internal/exceptions/bad_attribute_data_type.h \
    saklib/internal/attribute_data.h \
    saklib/internal/attribute_data__fwd.h \
    saklib/internal/attribute_data__test.h \
    saklib/internal/element_data.h \
    saklib/internal/element_data__fwd.h \
    saklib/internal/element_data__test.h \
    saklib/internal/element_data_manager.h \
    saklib/internal/element_data_manager__fwd.h \
    saklib/internal/element_data_manager__test.h \
    saklib/internal/exceptions/bad_element_data_type.h \
    saklib/internal/undoable_element_data_manager.h \
    saklib/internal/undoable_element_data_manager__fwd.h \
    saklib/internal/reference_counter__fwd.h \
    saklib/internal/reference_counter__inline.h \
    saklib/element.h \
    saklib/element__fwd.h \
    saklib/internal/storage_traits.h \
    saklib/internal/storage_traits__fwd.h \
    saklib/internal/storage_traits__inline.h \
    saklib/internal/exceptions/bad_data_handle.h \
    saklib/internal/element_data_definition_manager.h \
    saklib/internal/element_data_definition_manager__fwd.h \
    saklib/internal/reference_counted_storage__inline.h \
    saklib/internal/reference_counted_storage.h \
    saklib/internal/reference_counted_storage__fwd.h \
    saklib/internal/command.h \
    saklib/internal/command_history.h \
    saklib/internal/command__fwd.h \
    saklib/internal/command_history__fwd.h \
    saklib/internal/attribute_data_handle.h \
    saklib/internal/attribute_data_handle__fwd.h \
    saklib/internal/element_data_handle.h \
    saklib/internal/attribute_data_boolean_type.h \
    saklib/internal/attribute_data_boolean_type__fwd.h \
    saklib/internal/attribute_data_boolean_type__test.h \
    saklib/internal/attribute_data_floating_point_type.h \
    saklib/internal/attribute_data_floating_point_type__fwd.h \
    saklib/internal/attribute_data_integral_type.h \
    saklib/internal/attribute_data_integral_type__fwd.h \
    saklib/internal/attribute_data_integral_type__test.h \
    saklib/internal/all_attribute_data_.h \
    saklib/internal/all_attribute_data__fwd.h \
    saklib/internal/attribute_data_handle_bool.h \
    saklib/internal/attribute_data_handle_bool__fwd.h \
    saklib/internal/attribute_data_handle_int.h \
    saklib/internal/attribute_data_handle_int__fwd.h \
    saklib/internal/all_attribute_data_handle__fwd.h \
    saklib/internal/all_attribute_data_handle.h \
    saklib/internal/element_data_handle__fwd.h \
    saklib/internal/undoable_element_data_handle.h \
    saklib/internal/undoable_element_data_handle__fwd.h \
    saklib/internal/undoable_attribute_data_handle.h \
    saklib/internal/undoable_attribute_data_handle__fwd.h \
    saklib/internal/undoable_attribute_data_handle_bool.h \
    saklib/internal/undoable_attribute_data_handle_bool__fwd.h \
    saklib/internal/undoable_attribute_data_handle_int.h \
    saklib/internal/undoable_attribute_data_handle_int__fwd.h \
    saklib/internal/undoable_element_data_manager__test.h \
    saklib/internal/all_undoable_attribute_data_handle.h \
    saklib/internal/all_undoable_attribute_data_handle__fwd.h

FORMS

OTHER_FILES += \
    dev_notes.txt

DISTFILES += \
    readme.txt \
    README.md
