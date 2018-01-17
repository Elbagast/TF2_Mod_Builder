#ifndef SAK_ABSTRACT_PROJECT_SIGNALBOX_HPP
#define SAK_ABSTRACT_PROJECT_SIGNALBOX_HPP

#ifndef SAK_ABSTRACT_PROJECT_SIGNALBOX_FWD_HPP
#include "abstract_project_signalbox_fwd.hpp"
#endif

#include "abstract_section_signalbox.hpp"

namespace sak
{
  class Abstract_Project_Signalbox :
      public Abstract_File_Signalbox
      ,public Abstract_Texture_Signalbox
  {
  public:
    ~Abstract_Project_Signalbox() override = 0;
  };
} // namespace sak

#endif // SAK_ABSTRACT_PROJECT_SIGNALBOX_HPP
