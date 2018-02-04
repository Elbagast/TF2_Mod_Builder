
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


# Flamingo
#==============================
FLAMINGO_INCLUDE_DIR = "D:/Programming/Qt Projects/flamingo/"
FLAMINGO_LIBRARY_DIR = "D:/Programming/Qt Projects/flamingo/lib/"

CONFIG(release, debug|release): FLAMINGO_LIBRARY_DIR = $${FLAMINGO_LIBRARY_DIR}release/
CONFIG(debug, debug|release): FLAMINGO_LIBRARY_DIR = $${FLAMINGO_LIBRARY_DIR}debug/

LIBS += -L$${FLAMINGO_LIBRARY_DIR}
LIBS += -lflamingo

INCLUDEPATH += $${FLAMINGO_INCLUDE_DIR}
DEPENDPATH += $${FLAMINGO_LIBRARY_DIR}

# Included Files
#==============================


SOURCES += \
    dialog/new_project_dialog.cpp \
    abstract_command.cpp \
    abstract_member_edit_widget.cpp \
    abstract_outliner_branch_item.cpp \
    abstract_outliner_item.cpp \
    abstract_outliner_leaf_item.cpp \
    abstract_outliner_multitrunk_item.cpp \
    abstract_outliner_parented_item.cpp \
    abstract_outliner_trunk_item.cpp \
    abstract_project_interface.cpp \
    abstract_project_signalbox.cpp \
    abstract_section_signalbox.cpp \
    command_history.cpp \
    exception.cpp \
    fixed_settings.cpp \
    handle.cpp \
    handle_factory.cpp \
    name_utilities.cpp \
    outliner_delegate.cpp \
    outliner_model.cpp \
    outliner_view_widget.cpp \
    project_data.cpp \
    project_editor_widget.cpp \
    project_holder.cpp \
    project_interface.cpp \
    project_main_widget.cpp \
    project_main_window.cpp \
    project_outliner_items.cpp \
    project_outliner_widget.cpp \
    section_command.cpp \
    section_data.cpp \
    section_data_manager.cpp \
    section_interface.cpp \
    section_outliner_items.cpp \
    section_widget.cpp \
    shared_attributes.cpp \
    system_settings.cpp \
    tag.cpp \
    typestring_qstring.cpp \
    valve_attributes.cpp \
    xml_traits.cpp \
    dialog/new_project_dialog.cpp \
    generic/string_conversion.cpp \
    gui/directory_name_validator.cpp \
    gui/existing_directory_validator.cpp \
    gui/line_edit.cpp \
    gui/text_colour_state_changer.cpp \
    gui/validating_line_edit.cpp \
    abstract_command.cpp \
    abstract_member_edit_widget.cpp \
    abstract_outliner_branch_item.cpp \
    abstract_outliner_item.cpp \
    abstract_outliner_leaf_item.cpp \
    abstract_outliner_multitrunk_item.cpp \
    abstract_outliner_parented_item.cpp \
    abstract_outliner_trunk_item.cpp \
    abstract_project_interface.cpp \
    abstract_project_signalbox.cpp \
    abstract_section_signalbox.cpp \
    command_history.cpp \
    exception.cpp \
    fixed_settings.cpp \
    handle.cpp \
    handle_factory.cpp \
    name_utilities.cpp \
    outliner_delegate.cpp \
    outliner_model.cpp \
    outliner_view_widget.cpp \
    project_data.cpp \
    project_editor_widget.cpp \
    project_holder.cpp \
    project_interface.cpp \
    project_main_widget.cpp \
    project_main_window.cpp \
    project_outliner_items.cpp \
    project_outliner_widget.cpp \
    section_command.cpp \
    section_data.cpp \
    section_data_manager.cpp \
    section_interface.cpp \
    section_outliner_items.cpp \
    section_widget.cpp \
    shared_attributes.cpp \
    system_settings.cpp \
    tag.cpp \
    typestring_qstring.cpp \
    valve_attributes.cpp \
    xml_traits.cpp \
    gui/qstring_conversion.cpp
    

HEADERS  += \
    dialog/new_project_dialog.hpp \
    abstract_command.hpp \
    abstract_command_fwd.hpp \
    abstract_member_edit_widget.hpp \
    abstract_member_edit_widget_fwd.hpp \
    abstract_outliner_branch_item.hpp \
    abstract_outliner_branch_item_fwd.hpp \
    abstract_outliner_item.hpp \
    abstract_outliner_item_fwd.hpp \
    abstract_outliner_leaf_item.hpp \
    abstract_outliner_leaf_item_fwd.hpp \
    abstract_outliner_multitrunk_item.hpp \
    abstract_outliner_multitrunk_item_fwd.hpp \
    abstract_outliner_parented_item.hpp \
    abstract_outliner_parented_item_fwd.hpp \
    abstract_outliner_trunk_item.hpp \
    abstract_outliner_trunk_item_fwd.hpp \
    abstract_project_interface.hpp \
    abstract_project_interface_fwd.hpp \
    abstract_project_signalbox.hpp \
    abstract_project_signalbox_fwd.hpp \
    abstract_section_signalbox.hpp \
    abstract_section_signalbox_fwd.hpp \
    command_history.hpp \
    command_history_fwd.hpp \
    exception.hpp \
    exception_fwd.hpp \
    fixed_settings.hpp \
    handle.hpp \
    handle_factory.hpp \
    handle_factory_fwd.hpp \
    handle_fwd.hpp \
    member_types_fwd.hpp \
    name_utilities.hpp \
    outliner_delegate.hpp \
    outliner_delegate_fwd.hpp \
    outliner_model.hpp \
    outliner_model_fwd.hpp \
    outliner_view_widget.hpp \
    outliner_view_widget_fwd.hpp \
    project_data.hpp \
    project_data_fwd.hpp \
    project_editor_widget.hpp \
    project_editor_widget_fwd.hpp \
    project_holder.hpp \
    project_interface.hpp \
    project_interface_fwd.hpp \
    project_main_widget.hpp \
    project_main_widget_fwd.hpp \
    project_main_window.hpp \
    project_main_window_fwd.hpp \
    project_outliner_items.hpp \
    project_outliner_items_fwd.hpp \
    project_outliner_widget.hpp \
    project_outliner_widget_fwd.hpp \
    section_command.hpp \
    section_command_fwd.hpp \
    section_data.hpp \
    section_data_fwd.hpp \
    section_data_manager.hpp \
    section_data_manager_fwd.hpp \
    section_interface.hpp \
    section_interface_fwd.hpp \
    section_outliner_items.hpp \
    section_outliner_items_fwd.hpp \
    section_widget.hpp \
    section_widget_fwd.hpp \
    shared_attributes.hpp \
    system_settings.hpp \
    tag.hpp \
    tag_fwd.hpp \
    typestring_qstring.hpp \
    typestring_qstring_fwd.hpp \
    valve_attributes.hpp \
    valve_attributes_fwd.hpp \
    xml_traits.hpp \
    xml_traits_fwd.hpp \
    dialog/new_project_dialog.hpp \
    generic/string_conversion.hpp \
    generic/string_conversion_formats.hpp \
    gui/directory_name_validator.hpp \
    gui/existing_directory_validator.hpp \
    gui/line_edit.hpp \
    gui/text_colour_state_changer.hpp \
    gui/validating_line_edit.hpp \
    abstract_command.hpp \
    abstract_command_fwd.hpp \
    abstract_member_edit_widget.hpp \
    abstract_member_edit_widget_fwd.hpp \
    abstract_outliner_branch_item.hpp \
    abstract_outliner_branch_item_fwd.hpp \
    abstract_outliner_item.hpp \
    abstract_outliner_item_fwd.hpp \
    abstract_outliner_leaf_item.hpp \
    abstract_outliner_leaf_item_fwd.hpp \
    abstract_outliner_multitrunk_item.hpp \
    abstract_outliner_multitrunk_item_fwd.hpp \
    abstract_outliner_parented_item.hpp \
    abstract_outliner_parented_item_fwd.hpp \
    abstract_outliner_trunk_item.hpp \
    abstract_outliner_trunk_item_fwd.hpp \
    abstract_project_interface.hpp \
    abstract_project_interface_fwd.hpp \
    abstract_project_signalbox.hpp \
    abstract_project_signalbox_fwd.hpp \
    abstract_section_signalbox.hpp \
    abstract_section_signalbox_fwd.hpp \
    command_history.hpp \
    command_history_fwd.hpp \
    exception.hpp \
    exception_fwd.hpp \
    fixed_settings.hpp \
    handle.hpp \
    handle_factory.hpp \
    handle_factory_fwd.hpp \
    handle_fwd.hpp \
    member_types_fwd.hpp \
    name_utilities.hpp \
    outliner_delegate.hpp \
    outliner_delegate_fwd.hpp \
    outliner_model.hpp \
    outliner_model_fwd.hpp \
    outliner_view_widget.hpp \
    outliner_view_widget_fwd.hpp \
    project_data.hpp \
    project_data_fwd.hpp \
    project_editor_widget.hpp \
    project_editor_widget_fwd.hpp \
    project_holder.hpp \
    project_interface.hpp \
    project_interface_fwd.hpp \
    project_main_widget.hpp \
    project_main_widget_fwd.hpp \
    project_main_window.hpp \
    project_main_window_fwd.hpp \
    project_outliner_items.hpp \
    project_outliner_items_fwd.hpp \
    project_outliner_widget.hpp \
    project_outliner_widget_fwd.hpp \
    section_command.hpp \
    section_command_fwd.hpp \
    section_data.hpp \
    section_data_fwd.hpp \
    section_data_manager.hpp \
    section_data_manager_fwd.hpp \
    section_interface.hpp \
    section_interface_fwd.hpp \
    section_outliner_items.hpp \
    section_outliner_items_fwd.hpp \
    section_widget.hpp \
    section_widget_fwd.hpp \
    shared_attributes.hpp \
    system_settings.hpp \
    tag.hpp \
    tag_fwd.hpp \
    typestring_qstring.hpp \
    typestring_qstring_fwd.hpp \
    valve_attributes.hpp \
    valve_attributes_fwd.hpp \
    xml_traits.hpp \
    xml_traits_fwd.hpp \
    gui/abstract_state_changer.hpp \
    gui/qstring_conversion.hpp
    

FORMS

OTHER_FILES +=

DISTFILES += 

FORMS += \
    dialog/new_project_dialog.ui
