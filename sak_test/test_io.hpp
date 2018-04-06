#ifndef SAK_TEST_TEST_IO_HPP
#define SAK_TEST_TEST_IO_HPP

// public parts
#include <sak/entity_id_fwd.hpp>
#include <sak/entity_definition_fwd.hpp>
#include <sak/entity_manager_fwd.hpp>
#include <sak/signal_fwd.hpp>
#include <sak/signal_source_fwd.hpp>

// internal parts
#include <sak/internal/entity_fwd.hpp>
#include <sak/internal/entity_handle_fwd.hpp>

#include <iosfwd>

namespace sak
{
  std::ostream& operator<<(std::ostream& a_ostream, Entity_ID a_id);
  std::ostream& operator<<(std::ostream& a_ostream, Entity_Definition const& a_def);
  std::ostream& operator<<(std::ostream& a_ostream, Entity_Manager const& a_manager);

  std::ostream& operator<<(std::ostream& a_ostream, Signal const& a_signal);
  std::ostream& operator<<(std::ostream& a_ostream, Signal_Type a_type);
  std::ostream& operator<<(std::ostream& a_ostream, Signal_Source a_source);

  std::ostream& operator<<(std::ostream& a_ostream, Entity const& a_entity);
  std::ostream& operator<<(std::ostream& a_ostream, Entity_Handle const& a_handle);

}
#endif // TEST_IO_HPP
