#include "dummy_project_signalbox.hpp"


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
