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
    sak/dialog/new_project_dialog.cpp
    

HEADERS  += \
    sak/project_window.h \
    sak/project_widget.h \
    sak/dialog/new_project_dialog.h
    

FORMS

OTHER_FILES +=

DISTFILES += \
    README.md \
    project_layout.txt

FORMS += \
    sak/dialog/new_project_dialog.ui
