
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
CONFIG += c++17


# the fuck is going on
# Need this for a subproject to find the QT includes
#INCLUDEPATH += $${PWD}/..


include($$PWD/../library_boost.pri)
include($$PWD/../library_flamingo.pri)

# Included Files
#==============================

SOURCES += \
    abstract_observer.cpp \
    entity_definition.cpp \
    entity_id.cpp \
    entity_manager.cpp \
    signal.cpp \
    signal_entity.cpp \
    signal_entity_name_changed.cpp \
    signal_source.cpp \
    variant.cpp \
    internal/abstract_command.cpp \
    internal/abstract_entity_icon.cpp \
    internal/abstract_entity_maker.cpp \
    internal/abstract_entity_name.cpp \
    internal/abstract_entity_tooltip.cpp \
    internal/abstract_entity_type.cpp \
    internal/command_history.cpp \
    internal/entity.cpp \
    internal/entity_collection.cpp \
    internal/entity_commands.cpp \
    internal/entity_definition_maker.cpp \
    internal/entity_factory.cpp \
    internal/entity_handle.cpp \
    internal/entity_icon.cpp \
    internal/entity_name.cpp \
    internal/entity_tooltip.cpp \
    internal/observer_manager.cpp \
    internal/entity_type.cpp \
    internal/name_utilities.cpp \
    data_type.cpp \
    types.cpp \
    string.cpp \
    numeric.cpp \
    filepath.cpp

HEADERS  += \
    abstract_observer.hpp \
    abstract_observer_fwd.hpp \
    entity_definition.hpp \
    entity_definition_fwd.hpp \
    entity_id.hpp \
    entity_id_fwd.hpp \
    entity_manager.hpp \
    entity_manager_fwd.hpp \
    signal.hpp \
    signal_entity.hpp \
    signal_entity_fwd.hpp \
    signal_entity_name_changed.hpp \
    signal_entity_name_changed_fwd.hpp \
    signal_fwd.hpp \
    signal_source.hpp \
    signal_source_fwd.hpp \
    variant_fwd.hpp \
    internal/abstract_command.hpp \
    internal/abstract_command_fwd.hpp \
    internal/abstract_entity_icon.hpp \
    internal/abstract_entity_icon_fwd.hpp \
    internal/abstract_entity_maker.hpp \
    internal/abstract_entity_maker_fwd.hpp \
    internal/abstract_entity_name.hpp \
    internal/abstract_entity_name_fwd.hpp \
    internal/abstract_entity_tooltip.hpp \
    internal/abstract_entity_tooltip_fwd.hpp \
    internal/abstract_entity_type.hpp \
    internal/abstract_entity_type_fwd.hpp \
    internal/command_history.hpp \
    internal/command_history_fwd.hpp \
    internal/entity.hpp \
    internal/entity_collection.hpp \
    internal/entity_collection_fwd.hpp \
    internal/entity_commands.hpp \
    internal/entity_commands_fwd.hpp \
    internal/entity_definition_maker.hpp \
    internal/entity_factory.hpp \
    internal/entity_factory_fwd.hpp \
    internal/entity_fwd.hpp \
    internal/entity_handle.hpp \
    internal/entity_handle_fwd.hpp \
    internal/entity_icon.hpp \
    internal/entity_icon_fwd.hpp \
    internal/entity_name.hpp \
    internal/entity_name_fwd.hpp \
    internal/observer_manager.hpp \
    internal/observer_manager_fwd.hpp \
    internal/entity_type.hpp \
    internal/entity_type_fwd.hpp \
    internal/name_utilities.hpp \
    internal/entity_definition_maker_fwd.hpp \
    data_type.hpp \
    data_type_fwd.hpp \
    string.hpp \
    numeric.hpp \
    numeric_fwd.hpp \
    string_fwd.hpp \
    filepath.hpp \
    filepath_fwd.hpp \
    variant.hpp

FORMS += \

OTHER_FILES +=

DISTFILES += \ 
    readme.md \
    readme.md

SUBDIRS += \
    sak.pro

