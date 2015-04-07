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
    saklib/attribute.cpp \
    saklib/attribute_definition.cpp \
    saklib/command_history.cpp \
    saklib/element.cpp \
    saklib/element_iostream.cpp \
    saklib/element_manager.cpp \
    saklib/elementid.cpp \
    saklib/elementid_iostream.cpp \
    saklib/qtlib/element_widget.cpp \
    saklib/qtlib/windowtitle.cpp \
    saklib/all_attributes.cpp \
    saklib/qtlib/project_main_window.cpp \
    saklib/qtlib/outliner/outliner_treeview.cpp \
    saklib/qtlib/outliner/outliner_delegate.cpp \
    saklib/proxyid.cpp \
    saklib/qtlib/outliner/outliner_model.cpp \
    saklib/qtlib/quptr.cpp \
    saklib/qtlib/attribute_editor_bool.cpp \
    saklib/qtlib/attribute_editor.cpp \
    saklib/qtlib/attribute_editor_int.cpp \
    saklib/qtlib/temp_disconnect.cpp \
    saklib/qtlib/attribute_editor_double.cpp \
    saklib/qtlib/attribute_editor_string.cpp \
    saklib/command_element.cpp \
    saklib/qtlib/attribute_editor_elementid.cpp \
    saklib/qtlib/select_element_type_dialog.cpp \
    saklib/qtlib/attribute_editor_vector_elementid.cpp \
    saklib/qtlib/attribute_editor_vector.cpp \
    saklib/project_observer.cpp \
    saklib/project_manager_declaration.cpp \
    saklib/qtlib/project_widget.cpp \
    saklib/internal_element_definitions.cpp \
    saklib/element_definition_manager.cpp \
    saklib/element_definition.cpp \
    saklib/attribute_constraint_type.cpp

HEADERS  += \
    saklib/all_attributes.h \
    saklib/all_element.h \
    saklib/all_type_traits.h \
    saklib/attribute.h \
    saklib/attribute_definition.h \
    saklib/attribute_definition_type.h \
    saklib/attribute_type.h \
    saklib/attributeid.h \
    saklib/command.h \
    saklib/command_attribute.h \
    saklib/command_attribute_vector.h \
    saklib/command_history.h \
    saklib/element.h \
    saklib/element_definition.h \
    saklib/element_iostream.h \
    saklib/element_manager.h \
    saklib/elementid.h \
    saklib/elementid_iostream.h \
    saklib/fwd_attribute_type.h \
    saklib/type_traits.h \
    saklib/type_traits_bool.h \
    saklib/type_traits_double.h \
    saklib/type_traits_elementid.h \
    saklib/type_traits_int.h \
    saklib/type_traits_string.h \
    saklib/types.h \
    saklib/qtlib/element_widget.h \
    saklib/qtlib/windowtitle.h \
    saklib/qtlib/project_main_window.h \
    saklib/qtlib/outliner/outliner_treeview.h \
    saklib/qtlib/outliner/outliner_delegate.h \
    saklib/qtlib/qstring_operations.h \
    saklib/qtlib/qvariant_operations.h \
    saklib/type_traits_path.h \
    saklib/qtlib/attribute_editor.h \
    saklib/proxyid.h \
    saklib/qtlib/outliner/outliner_model.h \
    saklib/qtlib/quptr.h \
    saklib/qtlib/attribute_editor_bool.h \
    saklib/qtlib/attribute_editor_int.h \
    saklib/qtlib/temp_disconnect.h \
    saklib/qtlib/attribute_editor_double.h \
    saklib/qtlib/attribute_editor_string.h \
    saklib/command_element.h \
    saklib/qtlib/attribute_editor_elementid.h \
    saklib/qtlib/select_element_type_dialog.h \
    saklib/qtlib/attribute_editor_vector_elementid.h \
    saklib/qtlib/attribute_editor_vector.h \
    saklib/qtlib/attribute_editor_vector_type.h \
    saklib/project_observer.h \
    saklib/project_manager_declaration.h \
    saklib/project_manager.h \
    saklib/project_manager_commands.h \
    saklib/project_manager_templates.h \
    saklib/qtlib/project_widget.h \
    saklib/internal_element_definitions.h \
    saklib/element_definition_manager.h \
    saklib/attribute_constraint_type.h \
    saklib/qtlib/attribute_editor_type.h \
    saklib/qtlib/qwidget_operations.h

FORMS    += \
    saklib/qtlib/consoledialog.ui \
    saklib/qtlib/project_main_window.ui \
    saklib/qtlib/select_element_type_dialog.ui

OTHER_FILES += \
    dev_notes.txt

DISTFILES += \
    readme.txt
