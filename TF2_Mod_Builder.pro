#-------------------------------------------------
#
# Project created by QtCreator 2014-11-13T12:23:38
#
#-------------------------------------------------

QT       += core gui

#CONFIG += c++11
#QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -std=gnu++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TF2_Mod_Builder
TEMPLATE = app

# Boost includes
# Remember to use 32bit compiler...
CONFIG += static
CONFIG += threads
LIBS += -L"D:/Programming/C++/Boost/boost_1_57_0/stage/lib"
INCLUDEPATH += "D:/Programming/C++/Boost/boost_1_57_0"
DEPENDPATH += "D:/Programming/C++/Boost/boost_1_57_0/stage/lib"

# enable print to console
CONFIG += console
CONFIG += debug

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
