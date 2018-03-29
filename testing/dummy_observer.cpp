#include "dummy_observer.hpp"

#include <sak/abstract_signal.hpp>

#include <iostream>

namespace sak
{
  namespace
  {
    std::ostream& operator<<(std::ostream& a_ostream, Signal_Source a_source)
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

    std::ostream& operator<<(std::ostream& a_ostream, Signal_Type a_type)
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

    std::ostream& operator<<(std::ostream& a_ostream, Abstract_Signal const& a_signal)
    {
      a_ostream << "Abstract_Signal["
                << a_signal.source() << ", "
                << a_signal.type() << "]";
      return a_ostream;
    }
  }
}

//---------------------------------------------------------------------------
// Dummy_Project_Observer
//---------------------------------------------------------------------------
// Dump all the parameter to std::cout

// Special 6
//============================================================
sak::Dummy_Observer::Dummy_Observer() = default;
sak::Dummy_Observer::~Dummy_Observer() = default;

// Interface
//============================================================
// Recieve a project signal. It should contain everything needed to update
// and representation of the Project. Guaranteed to be valid for at least
// the duration of this call.
void sak::Dummy_Observer::recieve(Abstract_Signal const& a_signal)
{
  std::cout << this << " : "
           << "sak::Dummy_Observer::recieve( "
           << std::addressof(a_signal)
           << " : " << a_signal
           << " )" << std::endl;
}

