#ifndef SAK_ABSTRACT_PROJECT_SIGNALBOX_FWD_HPP
#define SAK_ABSTRACT_PROJECT_SIGNALBOX_FWD_HPP

#ifndef SAK_SECTION_DATA_FWD_HPP
#include "section_data_fwd.hpp"
#endif

namespace sak
{
  class Abstract_Project_Signalbox;

  namespace v2
  {
    //---------------------------------------------------------------------------
    // Abstract_Signalbox<T>
    //---------------------------------------------------------------------------

    // One type has all these functions.
    template <typename T>
    class Abstract_Signalbox;

    //---------------------------------------------------------------------------
    // Abstract_Chained_Signalbox<Args...>
    //---------------------------------------------------------------------------
    // For a project managing Args as parallel types that all have the same
    // format of signals.

    template <typename T, typename...Args>
    class Abstract_Chained_Signalbox;

    //---------------------------------------------------------------------------
    // Abstract_Project_Signalbox
    //---------------------------------------------------------------------------
    // Being able to expand this whenever is literally the only reason to do this.
    using Abstract_Project_Signalbox = Abstract_Chained_Signalbox<File_Data,Texture_Data>;
  }
} // namespace sak

#endif // SAK_ABSTRACT_PROJECT_SIGNALBOX_FWD_HPP
