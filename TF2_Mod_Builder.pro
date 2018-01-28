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
CONFIG += object_parallel_to_source

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
	main.cpp \
    sak/dialog/new_project_dialog.cpp \
    qtlib/validating_line_edit.cpp \
    qtlib/text_colour_state_changer.cpp \
    qtlib/directory_name_validator.cpp \
    qtlib/existing_directory_validator.cpp \
    sak/fixed_settings.cpp \
    sak/exceptions/exception.cpp \
    sak/system_settings.cpp \
    sak/name_utilities.cpp \
    valve/asset_filepath.cpp \
    generic/string_conversion.cpp \
    qtlib/string_conversion.cpp \
    sak/abstract_command.cpp \
    sak/command_history.cpp \
    sak/project_main_window.cpp \
    sak/project_main_widget.cpp \
    sak/project_editor_widget.cpp \
    sak/abstract_project_signalbox.cpp \
    sak/project_data.cpp \
    sak/project_outliner_widget.cpp \
    sak/project_outliner_items.cpp \
    sak/section_data.cpp \
    sak/section_handle.cpp \
    sak/abstract_section_signalbox.cpp \
    sak/section_data_manager.cpp \
    sak/abstract_member_edit_widget.cpp \
    sak/section_command.cpp \
    sak/section_interface.cpp \
    sak/section_outliner_items.cpp \
    sak/section_widget.cpp \
    sak/valve_attributes.cpp \
    sak/shared_attributes.cpp \
    sak/xml_traits.cpp \
    sak/typestring_qstring.cpp \
    sak/outliner_model.cpp \
    sak/abstract_outliner_item.cpp \
    sak/outliner_delegate.cpp \
    sak/outliner_view_widget.cpp \
    sak/abstract_outliner_parented_item.cpp \
    sak/abstract_outliner_trunk_item.cpp \
    sak/abstract_outliner_branch_item.cpp \
    sak/abstract_outliner_multitrunk_item.cpp \
    sak/abstract_outliner_leaf_item.cpp \
    sak/exception.cpp \
    sak/exception_dialogs.cpp \
    sak/project_interface.cpp
    

HEADERS  += \
    qtlib/directory_name_validator.hpp \
    qtlib/existing_directory_validator.hpp \
    qtlib/state_changer.hpp \
    qtlib/text_colour_state_changer.hpp \
    qtlib/validating_line_edit.hpp \
    sak/dialog/new_project_dialog.hpp \
    sak/exceptions/exception.hpp \
    sak/fixed_settings.hpp \
    sak/name_utilities.hpp \
    sak/system_settings.hpp \
    valve/asset_filepath.hpp \
    qtlib/display_widget_traits.hpp \
    generic/string_conversion_formats.hpp \
    generic/string_conversion.hpp \
    qtlib/string_conversion.hpp \
    sak/abstract_command.hpp \
    sak/abstract_command_fwd.hpp \
    sak/command_history.hpp \
    sak/command_history_fwd.hpp \
    sak/project_main_window.hpp \
    sak/project_main_window_fwd.hpp \
    sak/project_main_widget.hpp \
    sak/project_main_widget_fwd.hpp \
    sak/project_editor_widget.hpp \
    sak/project_editor_widget_fwd.hpp \
    sak/abstract_project_signalbox.hpp \
    sak/abstract_project_signalbox_fwd.hpp \
    sak/project_data.hpp \
    sak/project_data_fwd.hpp \
    sak/project_outliner_widget.hpp \
    sak/project_outliner_widget_fwd.hpp \
    sak/project_outliner_items_fwd.hpp \
    sak/project_outliner_items.hpp \
    sak/section_data.hpp \
    sak/section_data_fwd.hpp \
    sak/section_handle.hpp \
    sak/section_handle_fwd.hpp \
    sak/abstract_section_signalbox_fwd.hpp \
    sak/section_data_manager.hpp \
    sak/section_data_manager_fwd.hpp \
    sak/abstract_section_signalbox.hpp \
    sak/abstract_member_edit_widget.hpp \
    sak/abstract_member_edit_widget_fwd.hpp \
    sak/section_command_fwd.hpp \
    sak/section_command.hpp \
    sak/section_interface.hpp \
    sak/section_interface_fwd.hpp \
    sak/section_outliner_items.hpp \
    sak/section_outliner_items_fwd.hpp \
    sak/section_widget.hpp \
    sak/section_widget_fwd.hpp \
    sak/member_types_fwd.hpp \
    sak/valve_attributes_fwd.hpp \
    sak/valve_attributes.hpp \
    sak/shared_attributes.hpp \
    sak/xml_traits.hpp \
    sak/xml_traits_fwd.hpp \
    sak/typestring_qstring.hpp \
    sak/typestring_qstring_fwd.hpp \
    sak/outliner_model.hpp \
    sak/outliner_model_fwd.hpp \
    sak/abstract_outliner_item.hpp \
    sak/abstract_outliner_item_fwd.hpp \
    sak/outliner_delegate.hpp \
    sak/outliner_delegate_fwd.hpp \
    sak/outliner_view_widget.hpp \
    sak/outliner_view_widget_fwd.hpp \
    sak/abstract_outliner_parented_item.hpp \
    sak/abstract_outliner_parented_item_fwd.hpp \
    sak/abstract_outliner_trunk_item.hpp \
    sak/abstract_outliner_trunk_item_fwd.hpp \
    sak/abstract_outliner_branch_item.hpp \
    sak/abstract_outliner_branch_item_fwd.hpp \
    sak/abstract_outliner_multitrunk_item.hpp \
    sak/abstract_outliner_multitrunk_item_fwd.hpp \
    sak/abstract_outliner_leaf_item.hpp \
    sak/abstract_outliner_leaf_item_fwd.hpp \
    sak/exception_fwd.hpp \
    sak/exception.hpp \
    sak/exception_dialogs.hpp \
    sak/project_interface.hpp \
    sak/project_interface_fwd.hpp
    

FORMS

OTHER_FILES +=

DISTFILES += \
    README.md \
    project_layout.txt

FORMS += \
    sak/dialog/new_project_dialog.ui
