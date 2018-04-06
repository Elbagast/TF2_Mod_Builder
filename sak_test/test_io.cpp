#include "test_io.hpp"

// public parts
#include <sak/entity_id.hpp>
#include <sak/entity_definition.hpp>
#include <sak/entity_manager.hpp>
#include <sak/signal.hpp>
#include <sak/signal_source.hpp>

// internal parts
#include <sak/internal/entity.hpp>
#include <sak/internal/entity_handle.hpp>

#include <sak/internal/abstract_entity_type.hpp>
#include <sak/internal/abstract_entity_name.hpp>
#include <sak/internal/abstract_entity_tooltip.hpp>
#include <sak/internal/abstract_entity_icon.hpp>

#include <iostream>

std::ostream& sak::operator<<(std::ostream& a_ostream, Entity_ID a_id)
{
  a_ostream << "Entity_ID[ " << entity_id_value(a_id) << " ]";
  return a_ostream;
}

std::ostream& sak::operator<<(std::ostream& a_ostream, Entity_Definition const& a_def)
{
  a_ostream << "Entity_Definition[ "
            << "type=\"" << a_def.type() << "\" "
            << "tooltip=\"" << a_def.tooltip() << "\" "
            << "iconpath=\"" << a_def.iconpath() << "\""
            << " ]";
  return a_ostream;
}

std::ostream& sak::operator<<(std::ostream& a_ostream, Signal const& a_signal)
{
  a_ostream << "Signal[ "
            << a_signal.source() << ", "
            << a_signal.type() << " ]";
  return a_ostream;
}

std::ostream& sak::operator<<(std::ostream& a_ostream, Signal_Type a_type)
{
  a_ostream << "Signal_Type::";
  switch(a_type)
  {
    case Signal_Type::Entity_Added: a_ostream << "Entity_Added"; break;
    case Signal_Type::Entity_Removed: a_ostream << "Entity_Removed"; break;
    case Signal_Type::Entity_Name_Changed: a_ostream << "Entity_Name_Changed"; break;
    default: a_ostream << "UNKNOWN"; break;
  }
  return a_ostream;
}

std::ostream& sak::operator<<(std::ostream& a_ostream, Signal_Source a_source)
{
  a_ostream << "Signal_Source::";
  switch(a_source)
  {
    case Signal_Source::System: a_ostream << "System"; break;
    case Signal_Source::User: a_ostream << "User"; break;
    case Signal_Source::Editor: a_ostream << "Editor"; break;
    case Signal_Source::Outliner: a_ostream << "Outliner"; break;
    case Signal_Source::Redo: a_ostream << "Redo"; break;
    case Signal_Source::Undo: a_ostream << "Undo"; break;
    default: a_ostream << "UNKNOWN"; break;
  }
  return a_ostream;
}

std::ostream& sak::operator<<(std::ostream& a_ostream, Entity_Manager const& a_manager)
{
  a_ostream << "Entity_Manager \n[";

  for (std::size_t l_index = 0, l_end = a_manager.count(); l_index != l_end; ++l_index)
  {
    auto l_id = a_manager.get_at(l_index);
    a_ostream << l_id
              << " type=\"" << a_manager.type(l_id) << "\" "
              << " name=\"" << a_manager.name(l_id) << "\" "
              << " name=\"" << a_manager.iconpath(l_id) << "\" "
              << std::endl;
  }

  a_ostream << "\n]";

  return a_ostream;
}

std::ostream& sak::operator<<(std::ostream& a_ostream, Entity const& a_entity)
{
  a_ostream << "Entity[ "
            << "id=" << a_entity.id() << " "
            << "type=\"" << (a_entity.ctype_component() ? a_entity.ctype_component()->type() : "")<< "\" "
            << "name=\"" << (a_entity.cname_component() ? a_entity.cname_component()->get_name() : "")<< "\" "
            << "tooltip=\"" << (a_entity.ctooltip_component() ? a_entity.ctooltip_component()->tooltip() : "")<< "\" "
            << "icon=\"" << (a_entity.cicon_component() ? a_entity.cicon_component()->iconpath() : "")<< "\" "
            << "]";
  return a_ostream;
}

std::ostream& sak::operator<<(std::ostream& a_ostream, Entity_Handle const& a_handle)
{
  a_ostream << "Entity_Handle[ ";
  if (a_handle)
  {
    a_ostream << *a_handle;
  }
  a_ostream << " ]";
  return a_ostream;
}

