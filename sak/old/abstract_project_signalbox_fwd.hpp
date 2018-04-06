#ifndef SAK_ABSTRACT_PROJECT_SIGNALBOX_FWD_HPP
#define SAK_ABSTRACT_PROJECT_SIGNALBOX_FWD_HPP

#ifndef SAK_CLASS_DEFINITIONS_FWD_HPP
#include "class_definitions_fwd.hpp"
#endif

namespace sak
{
  enum class Signal_Source;

  template <typename T, typename...Args>
  class Abstract_Project_Signalbox_Imp;

  using Abstract_Project_Signalbox = Abstract_Project_Signalbox_Imp<File_Definition,Texture_Definition,Material_Definition>;
} // namespace sak

#endif // SAK_ABSTRACT_PROJECT_SIGNALBOX_FWD_HPP
