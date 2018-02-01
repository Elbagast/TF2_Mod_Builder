#ifndef SAK_ABSTRACT_SECTION_SIGNALBOX_HPP
#define SAK_ABSTRACT_SECTION_SIGNALBOX_HPP

#ifndef SAK_ABSTRACT_SECTION_SIGNALBOX_FWD_HPP
#include "abstract_section_signalbox_fwd.hpp"
#endif

#ifndef SAK_HANDLE_FWD_HPP
#include "handle_fwd.hpp"
#endif

#ifndef INCLUDE_STD_CSTDDEF
#define INCLUDE_STD_CSTDDEF
#include <cstddef>
#endif

namespace sak
{
  // if you want signal origin tracking...


  //---------------------------------------------------------------------------
  // Abstract_Section_Signalbox<T>
  //---------------------------------------------------------------------------
  // All signals that are dispatched from Project for a given object type.
  template <typename T>
  class Abstract_Section_Signalbox
  {
  public:
    using Data_Type = T;
    using Handle_Type = Handle<T>;

    virtual ~Abstract_Section_Signalbox() = 0;

    // When a handle has its data changed, this is called.
    virtual void changed(Handle_Type const& a_handle) = 0;
    // When a handle has its data changed in a specific place, this is called.
    // a_section == 0 denotes the name and may have special logic requirements.
    virtual void changed_at(Handle_Type const& a_handle, std::size_t a_section) = 0;
    // When a handle has been added, this is called.
    virtual void added(Handle_Type const& a_handle) = 0;
    // When a handle has been removed, this is called.
    virtual void removed(Handle_Type const& a_handle) = 0;
    // When a handle editor is to be opened, this is called.
    virtual void requests_editor(Handle_Type const& a_handle) = 0;
    // When focus is changed to be on a handle, call this
    virtual void requests_focus(Handle_Type const& a_handle) = 0;
  };
}

#endif // SAK_ABSTRACT_SECTION_SIGNALBOX_HPP
