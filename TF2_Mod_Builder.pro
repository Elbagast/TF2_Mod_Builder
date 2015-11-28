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
    saklib/internal/constraint_boolean_type.cpp \
    saklib/internal/constraint_boolean_type__test.cpp \
    saklib/internal/constraint_integral_type__test.cpp \
    saklib/internal/constraint_integral_type.cpp \
    saklib/internal/constraint_floating_point_type.cpp \
    saklib/internal/type_string.cpp \
    saklib/internal/attribute.cpp \
    saklib/internal/attribute__test.cpp \
    saklib/internal/element.cpp \
    saklib/internal/element__test.cpp \
    saklib/internal/element_manager.cpp \
    saklib/internal/exceptions/bad_element_type.cpp \
    saklib/internal/exceptions/bad_attribute_type.cpp

HEADERS  += \
    saklib/zzz_refactoring.h \
    saklib/internal/handle.h \
    saklib/internal/null_handle.h \
    saklib/internal/handle_factory.h \
    saklib/internal/smart_handle.h \
    saklib/internal/smart_handle_manager.h \
    saklib/internal/test.h \
    saklib/internal/handle__inline.h \
    saklib/internal/handle__fwd.h \
    saklib/internal/null_handle__fwd.h \
    saklib/internal/handle_factory__inline.h \
    saklib/internal/null_handle__inline.h \
    saklib/internal/handle_factory__fwd.h \
    saklib/internal/reference_counted_storage__fwd.h \
    saklib/internal/reference_counted_storage.h \
    saklib/internal/reference_counted_storage__inline.h \
    saklib/internal/smart_handle_manager__fwd.h \
    saklib/internal/smart_handle_manager__inline.h \
    saklib/internal/smart_handle__fwd.h \
    saklib/internal/smart_handle__inline.h \
    saklib/internal/constraint_boolean_type.h \
    saklib/internal/constraint_boolean_type__fwd.h \
    saklib/internal/constraint_boolean_type__test.h \
    saklib/internal/constraint_integral_type.h \
    saklib/internal/constraint_integral_type__test.h \
    saklib/internal/constraint_integral_type__fwd.h \
    saklib/internal/constraint_floating_point_type.h \
    saklib/internal/constraint_floating_point_type__fwd.h \
    saklib/internal/all_constraint.h \
    saklib/internal/all_constraint__fwd.h \
    saklib/internal/type_string.h \
    saklib/internal/string.h \
    saklib/internal/type_string__fwd.h \
    saklib/internal/attribute.h \
    saklib/internal/attribute__fwd.h \
    saklib/internal/attribute__test.h \
    saklib/internal/element.h \
    saklib/internal/element__fwd.h \
    saklib/internal/element__test.h \
    saklib/internal/element_manager.h \
    saklib/internal/size_type.h \
    saklib/internal/exceptions/bad_element_type.h \
    saklib/internal/exceptions/bad_attribute_type.h \
    saklib/internal/reference_counter.h

FORMS

OTHER_FILES += \
    dev_notes.txt

DISTFILES += \
    readme.txt \
    README.md
