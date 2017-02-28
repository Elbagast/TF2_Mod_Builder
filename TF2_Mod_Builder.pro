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


SOURCES += \
	main.cpp \
    sak/project_window.cpp \
    sak/project_widget.cpp \
    sak/dialog/new_project_dialog.cpp \
    qtlib/validating_line_edit.cpp \
    qtlib/text_colour_state_changer.cpp \
    qtlib/directory_name_validator.cpp \
    qtlib/existing_directory_validator.cpp \
    sak/fixed_settings.cpp \
    sak/project.cpp \
    sak/exceptions/exception.cpp \
    sak/system_settings.cpp \
    generic/uintid.cpp \
    generic/uintid_manager.cpp \
    generic/uintid_traits.cpp \
    sak/name_utilities.cpp \
    sak/project_editor.cpp \
    generic/command_history.cpp \
    generic/command.cpp \
    sak/filepath.cpp \
    valve/asset_filepath.cpp \
    dclib/ct/testing/test_object.cpp \
    dclib/litype/testing/test_float.cpp \
    dclib/litype/testing/test_integer.cpp \
    dclib/litype/testing/test_string.cpp \
    dclib/rt/testing/test_object.cpp \
    sak/shared/command.cpp \
    sak/shared/interface.cpp \
    sak/shared/interface_traits.cpp \
    generic/string_conversion.cpp \
    qtlib/string_conversion.cpp \
    qtlib/outliner/abstract_item.cpp \
    qtlib/outliner/abstract_readonly_item.cpp \
    qtlib/outliner/abstract_root_item.cpp \
    qtlib/outliner/branch_item.cpp \
    qtlib/outliner/delegate.cpp \
    qtlib/outliner/leaf_item.cpp \
    qtlib/outliner/model.cpp \
    qtlib/outliner/multitrunk_item.cpp \
    qtlib/outliner/orphan_item.cpp \
    qtlib/outliner/parented_item.cpp \
    qtlib/outliner/root_trunk_item.cpp \
    qtlib/outliner/root_branch_item.cpp \
    qtlib/outliner/trunk_item.cpp \
    qtlib/outliner/treeview.cpp \
    sak/shared/outliner_item.cpp \
    sak/shared/object.cpp \
    sak/shared/manager.cpp \
    sak/shared/extended_manager.cpp \
    sak/shared/signalbox.cpp \
    sak/shared/widget.cpp \
    sak/outliner/root_item.cpp \
    sak/outliner/project_item.cpp \
    sak/outliner/widget.cpp \
    sak/shared/dispatch_signals.cpp
    

HEADERS  += \
    generic/fwd/uintid.hpp \
    generic/fwd/manager.hpp \
    generic/fwd/uintid_manager.hpp \
    generic/fwd/extended_manager.hpp \
    dclib/ct/fwd/member.hpp \
    dclib/ct/fwd/object.hpp \
    dclib/ct/testing/test_object.hpp \
    dclib/ct/v1/fwd/member.hpp \
    dclib/ct/v1/fwd/object.hpp \
    dclib/ct/v1/member.hpp \
    dclib/ct/v1/name_impl.hpp \
    dclib/ct/v1/object.hpp \
    dclib/ct/v1/template_string_impl.hpp \
    dclib/ct/v1/type_impl.hpp \
    dclib/ct/v1/value_impl.hpp \
    dclib/ct/member.hpp \
    dclib/ct/object.hpp \
    dclib/litype/fwd/floating_point.hpp \
    dclib/litype/fwd/integer.hpp \
    dclib/litype/fwd/string.hpp \
    dclib/litype/testing/test_float.hpp \
    dclib/litype/testing/test_integer.hpp \
    dclib/litype/testing/test_string.hpp \
    dclib/litype/v1/fwd/float_class.hpp \
    dclib/litype/v1/fwd/integer_class.hpp \
    dclib/litype/v1/fwd/string_class.hpp \
    dclib/litype/v1/fwd/string_macro.hpp \
    dclib/litype/v1/fwd/string_tools.hpp \
    dclib/litype/v1/float_class.hpp \
    dclib/litype/v1/float_macro.hpp \
    dclib/litype/v1/float_tools.hpp \
    dclib/litype/v1/integer_class.hpp \
    dclib/litype/v1/integer_macro.hpp \
    dclib/litype/v1/string_class.hpp \
    dclib/litype/v1/string_macro.hpp \
    dclib/litype/v1/string_tools.hpp \
    dclib/litype/floating_point.hpp \
    dclib/litype/integer.hpp \
    dclib/litype/string.hpp \
    dclib/meta/power.hpp \
    dclib/meta/typelist.hpp \
    dclib/rt/fwd/member.hpp \
    dclib/rt/fwd/object.hpp \
    dclib/rt/testing/test_object.hpp \
    dclib/rt/v1/fwd/member.hpp \
    dclib/rt/v1/fwd/object.hpp \
    dclib/rt/v1/member.hpp \
    dclib/rt/v1/object.hpp \
    dclib/rt/v1/polymorhpic_tuple.hpp \
    dclib/rt/member.hpp \
    dclib/rt/object.hpp \
    generic/uintid_traits.hpp \
    generic/uintid_manager.hpp \
    generic/uintid.hpp \
    generic/manager.hpp \
    generic/extended_manager.hpp \
    generic/command_history.hpp \
    generic/command.hpp \
    qtlib/directory_name_validator.hpp \
    qtlib/existing_directory_validator.hpp \
    qtlib/state_changer.hpp \
    qtlib/text_colour_state_changer.hpp \
    qtlib/validating_line_edit.hpp \
    sak/dialog/new_project_dialog.hpp \
    sak/exceptions/exception.hpp \
    sak/filepath.hpp \
    sak/fixed_settings.hpp \
    sak/name_utilities.hpp \
    sak/project.hpp \
    sak/project_editor.hpp \
    sak/project_signalbox.hpp \
    sak/project_widget.hpp \
    sak/system_settings.hpp \
    sak/project_window.hpp \
    valve/asset_filepath.hpp \
    sak/shared/fwd/command.hpp \
    sak/shared/fwd/extended_manager.hpp \
    sak/shared/fwd/interface.hpp \
    sak/shared/fwd/interface_traits.hpp \
    sak/shared/fwd/manager.hpp \
    sak/shared/command.hpp \
    sak/shared/extended_manager.hpp \
    sak/shared/interface.hpp \
    sak/shared/interface_traits.hpp \
    sak/shared/manager.hpp \
    sak/shared/fwd/object.hpp \
    sak/shared/object.hpp \
    sak/shared/fwd/signalbox.hpp \
    sak/shared/signalbox.hpp \
    sak/shared/fwd/widget.hpp \
    sak/shared/fwd/outliner_item.hpp \
    sak/shared/widget.hpp \
    qtlib/display_widget_traits.hpp \
    generic/string_conversion_formats.hpp \
    generic/string_conversion.hpp \
    qtlib/string_conversion.hpp \
    qtlib/display/widget_traits.hpp \
    qtlib/display/anon_widget_traits.hpp \
    qtlib/edit/widget_traits.hpp \
    qtlib/edit/anon_widget_traits.hpp \
    sak/shared/outliner_item.hpp \
    qtlib/outliner/abstract_item.hpp \
    qtlib/outliner/abstract_readonly_item.hpp \
    qtlib/outliner/abstract_root_item.hpp \
    qtlib/outliner/branch_item.hpp \
    qtlib/outliner/delegate.hpp \
    qtlib/outliner/leaf_item.hpp \
    qtlib/outliner/model.hpp \
    qtlib/outliner/multitrunk_item.hpp \
    qtlib/outliner/orphan_item.hpp \
    qtlib/outliner/parented_item.hpp \
    qtlib/outliner/root_trunk_item.hpp \
    qtlib/outliner/root_branch_item.hpp \
    qtlib/outliner/treeview.hpp \
    qtlib/outliner/trunk_item.hpp \
    sak/outliner/root_item.hpp \
    sak/outliner/project_item.hpp \
    sak/outliner/widget.hpp \
    sak/shared/dispatch_signals.hpp \
    sak/shared/fwd/dispatch_signals.hpp
    

FORMS

OTHER_FILES +=

DISTFILES += \
    README.md \
    project_layout.txt

FORMS += \
    sak/dialog/new_project_dialog.ui
