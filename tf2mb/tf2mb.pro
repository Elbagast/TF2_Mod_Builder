#-------------------------------------------------
#
# Project created by QtCreator 2014-11-13T12:23:38
#
#-------------------------------------------------

# Qt bits
#==============================
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tf2mb
TEMPLATE = app

CONFIG += static
CONFIG += threads
#CONFIG += object_parallel_to_source
CONFIG += c++17

INCLUDE_DIR = $${PWD}/..
INCLUDEPATH += $${INCLUDE_DIR}

# Link to sak subproject
#==========================================
# Looking in the other subproject's build location
CONFIG(release, debug|release): LIBRARY_DIR = $$OUT_PWD/../sak/release/
CONFIG(debug, debug|release): LIBRARY_DIR = $$OUT_PWD/../sak/debug/

LIBS += -L$${LIBRARY_DIR} -lsak

# Need one of these for each .lib made
LIBS += -lsak

DEPENDPATH += $${LIBRARY_DIR}


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
    project.cpp \
    project_main_widget.cpp \
    project_main_window.cpp \
    project_editor_widget.cpp \
    project_holder.cpp \
    exception.cpp \
    fixed_settings.cpp \
    dialog/new_project_dialog.cpp \
    gui/directory_name_validator.cpp \
    gui/existing_directory_validator.cpp \
    gui/line_edit.cpp \
    gui/text_colour_state_changer.cpp \
    gui/validating_line_edit.cpp \
    project_outliner_widget.cpp \
    abstract_outliner_item.cpp \
    outliner_delegate.cpp \
    outliner_model.cpp \
    outliner_view_widget.cpp \
    abstract_outliner_branch_item.cpp \
    abstract_outliner_item.cpp \
    abstract_outliner_leaf_item.cpp \
    abstract_outliner_multitrunk_item.cpp \
    abstract_outliner_parented_item.cpp \
    abstract_outliner_trunk_item.cpp \
    project_outliner_items.cpp \
    abstract_project_outliner_root_item.cpp
    

HEADERS  += \
    project.hpp \
    project_fwd.hpp \
    project_main_widget.hpp \
    project_main_widget_fwd.hpp \
    project_main_window.hpp \
    project_main_window_fwd.hpp \
    project_editor_widget.hpp \
    project_editor_widget_fwd.hpp \
    project_holder.hpp \
    exception.hpp \
    exception_fwd.hpp \
    fixed_settings.hpp \
    dialog/new_project_dialog.hpp \
    gui/abstract_state_changer.hpp \
    gui/directory_name_validator.hpp \
    gui/existing_directory_validator.hpp \
    gui/line_edit.hpp \
    gui/text_colour_state_changer.hpp \
    gui/validating_line_edit.hpp \
    project_outliner_widget.hpp \
    project_outliner_widget_fwd.hpp \
    abstract_outliner_item.hpp \
    abstract_outliner_item_fwd.hpp \
    outliner_delegate.hpp \
    outliner_delegate_fwd.hpp \
    outliner_model.hpp \
    outliner_model_fwd.hpp \
    outliner_view_widget.hpp \
    outliner_view_widget_fwd.hpp \
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
    project_outliner_items.hpp \
    project_outliner_items_fwd.hpp \
    abstract_project_outliner_root_item.hpp \
    outliner_project_root_item_fwd.hpp
    

FORMS

OTHER_FILES +=

DISTFILES +=

FORMS += \
    dialog/new_project_dialog.ui
