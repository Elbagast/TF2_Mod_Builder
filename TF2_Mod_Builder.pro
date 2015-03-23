#-------------------------------------------------
#
# Project created by QtCreator 2014-11-13T12:23:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TF2_Mod_Builder
TEMPLATE = app

# Boost includes
# Remember to use 32bit compiler...
CONFIG += static
CONFIG += threads
win32:LIBS += -L"D:/Programming/C++/Boost/boost_1_57_0/stage/lib"
win32:INCLUDEPATH += "D:/Programming/C++/Boost/boost_1_57_0"
win32:DEPENDPATH += "D:/Programming/C++/Boost/boost_1_57_0/stage/lib"

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
    saklib/qtlib/project_widget.cpp \
    saklib/qtlib/outliner/outliner_treeview.cpp \
    saklib/qtlib/outliner/outliner_delegate.cpp \
    saklib/qtlib/editor_bool.cpp \
    saklib/qtlib/element_widget_manager.cpp \
    saklib/qtlib/project_manager.cpp \
    saklib/proxyid.cpp \
    saklib/qtlib/outliner/outliner_model.cpp \
    saklib/interal_element_definitions.cpp

HEADERS  += \
    saklib/all_attributes.h \
    saklib/all_element.h \
    saklib/all_type_traits.h \
    saklib/attribute.h \
    saklib/attribute_definition.h \
    saklib/attribute_definition_type.h \
    saklib/attribute_type.h \
    saklib/attributeid.h \
    saklib/attributeid_type.h \
    saklib/command.h \
    saklib/command_attribute.h \
    saklib/command_attribute_vector.h \
    saklib/command_history.h \
    saklib/element.h \
    saklib/element_definition.h \
    saklib/element_editor.h \
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
    saklib/qtlib/project_widget.h \
    saklib/qtlib/project_main_window.h \
    saklib/qtlib/outliner/outliner_treeview.h \
    saklib/qtlib/outliner/outliner_delegate.h \
    saklib/qtlib/qstring_operations.h \
    saklib/qtlib/qvariant_operations.h \
    saklib/type_traits_path.h \
    saklib/qtlib/editor_bool.h \
    saklib/qtlib/element_widget_manager.h \
    saklib/qtlib/project_manager.h \
    saklib/qtlib/attribute_editor.h \
    saklib/proxyid.h \
    saklib/qtlib/outliner/outliner_model.h \
    saklib/interal_element_definitions.h

FORMS    += \
    saklib/qtlib/consoledialog.ui \
    saklib/qtlib/project_main_window.ui

OTHER_FILES += \
    dev_notes.txt

DISTFILES += \
    readme.txt
