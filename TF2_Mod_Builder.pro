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
    qtlib/outliner/outliner_delegate.cpp \
    qtlib/outliner/outliner_model.cpp \
    qtlib/outliner/outliner_treeview.cpp \
    sak/project_outliner_items.cpp \
    qtlib/outliner/outliner_abstract_item.cpp \
    qtlib/outliner/outliner_abstract_root_item.cpp \
    qtlib/outliner/outliner_abstract_readonly_item.cpp \
    qtlib/outliner/outliner_branch_item.cpp \
    qtlib/outliner/outliner_leaf_item.cpp \
    qtlib/outliner/outliner_trunk_item.cpp \
    qtlib/outliner/outliner_root_branch_item.cpp \
    qtlib/outliner/outliner_root_trunk_item.cpp \
    qtlib/outliner/outliner_parented_item.cpp \
    qtlib/outliner/outliner_multitrunk_item.cpp \
    generic/uintid.cpp \
    generic/uintid_manager.cpp \
    generic/uintid_traits.cpp \
    qtlib/outliner/outliner_orphan_item.cpp \
    sak/file_interface_traits.cpp \
    sak/name_utilities.cpp \
    sak/file_manager.cpp \
    sak/file_widget.cpp \
    sak/project_outliner.cpp \
    sak/project_editor.cpp \
    sak/file.cpp \
    sak/common_data.cpp \
    sak/common_data_widget.cpp \
    sak/common_data_interface_traits.cpp
    

HEADERS  += \
    sak/project_window.h \
    sak/project_widget.h \
    sak/dialog/new_project_dialog.h \
    qtlib/validating_line_edit.h \
    qtlib/text_colour_state_changer.h \
    qtlib/state_changer.h \
    qtlib/directory_name_validator.h \
    qtlib/existing_directory_validator.h \
    sak/fixed_settings.h \
    sak/project.h \
    sak/exceptions/exception.h \
    sak/system_settings.h \
    qtlib/outliner/outliner_delegate.h \
    qtlib/outliner/outliner_model.h \
    qtlib/outliner/outliner_treeview.h \
    sak/project_outliner_items.h \
    qtlib/outliner/outliner_abstract_item.h \
    qtlib/outliner/outliner_abstract_root_item.h \
    qtlib/outliner/outliner_abstract_readonly_item.h \
    qtlib/outliner/outliner_branch_item.h \
    qtlib/outliner/outliner_leaf_item.h \
    qtlib/outliner/outliner_trunk_item.h \
    qtlib/outliner/outliner_root_branch_item.h \
    qtlib/outliner/outliner_root_trunk_item.h \
    qtlib/outliner/outliner_parented_item.h \
    qtlib/outliner/outliner_multitrunk_item.h \
    generic/manager.h \
    generic/uintid.h \
    generic/uintid_manager.h \
    generic/uintid_traits.h \
    generic/extended_manager.h \
    qtlib/outliner/outliner_orphan_item.h \
    sak/file_interface_traits.h \
    generic/fwd_uintid.h \
    generic/fwd_manager.h \
    generic/fwd_uintid_manager.h \
    generic/fwd_extended_manager.h \
    sak/fwd_file.h \
    sak/file_basic_manager.h \
    sak/file_manager.h \
    sak/name_utilities.h \
    sak/file_widget.h \
    sak/project_outliner.h \
    sak/project_signalbox.h \
    sak/project_editor.h \
    sak/file.h \
    sak/common_data.h \
    sak/common_data_widget.h \
    sak/common_data_interface_traits.h
    

FORMS

OTHER_FILES +=

DISTFILES += \
    README.md \
    project_layout.txt

FORMS += \
    sak/dialog/new_project_dialog.ui
