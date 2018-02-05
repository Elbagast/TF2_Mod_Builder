#ifndef SAK_ABSTRACT_PROJECT_SIGNALBOX_HPP
#define SAK_ABSTRACT_PROJECT_SIGNALBOX_HPP

#ifndef SAK_ABSTRACT_PROJECT_SIGNALBOX_FWD_HPP
#include "abstract_project_signalbox_fwd.hpp"
#endif

#ifndef SAK_HANDLE_FWD_HPP
#include "handle_fwd.hpp"
#endif

#include "section_data_fwd.hpp"

#include "abstract_section_signalbox.hpp"

namespace sak
{
  //---------------------------------------------------------------------------
  // Abstract_Signalbox<T,Args...>
  //---------------------------------------------------------------------------

  // One type has all these functions.
  template <typename T>
  class Abstract_Signalbox<T>
  {
  public:
    virtual ~Abstract_Signalbox() = 0;

    // When a handle has its data changed, this is called.
    virtual void changed(Handle<T> const& a_handle) = 0;
    // When a handle has its name changed, this is called.
    virtual void changed_name(Handle<T> const& a_handle) = 0;
    // When a handle has its data changed in a specific place, this is called.
    // a_section == 0 denotes the name and may have special logic requirements.
    virtual void changed_at(Handle<T> const& a_handle, std::size_t a_section) = 0;
    // When a handle has been added, this is called.
    virtual void added(Handle<T> const& a_handle) = 0;
    // When a handle has been removed, this is called.
    virtual void removed(Handle<T> const& a_handle) = 0;
    // When a handle editor is to be opened, this is called.
    virtual void requests_editor(Handle<T> const& a_handle) = 0;
    // When focus is changed to be on a handle, call this
    virtual void requests_focus(Handle<T> const& a_handle) = 0;
  };


  // For at least 2, we inherit one and use it's functions, then chain the next
  // and expose its functions too.
  template <typename T, typename R, typename...Args>
  class Abstract_Signalbox<T,R,Args...>:
      private virtual Abstract_Signalbox<T>,
      private virtual Abstract_Signalbox<R, Args...>
  {
    using Inh1 = Abstract_Signalbox<T>;
    using Inh2 = Abstract_Signalbox<R, Args...>;
  public:
    ~Abstract_Signalbox() override = 0;

    using Inh1::changed;
    using Inh1::changed_name;
    using Inh1::changed_at;
    using Inh1::added;
    using Inh1::removed;
    using Inh1::requests_editor;
    using Inh1::requests_focus;

    using Inh2::changed;
    using Inh2::changed_name;
    using Inh2::changed_at;
    using Inh2::added;
    using Inh2::removed;
    using Inh2::requests_editor;
    using Inh2::requests_focus;
  };

  //---------------------------------------------------------------------------
  // Abstract_Project_Signalbox
  //---------------------------------------------------------------------------
  // Being able to expand this whenever is literally the only reason to do this.
  //using Abstract_Project_Signalbox = Abstract_Signalbox<File_Data,Texture_Data>;

} // namespace sak


//---------------------------------------------------------------------------
// Abstract_Signalbox<T>
//---------------------------------------------------------------------------
template <typename T>
sak::Abstract_Signalbox<T>::~Abstract_Signalbox() = default;

template <typename T, typename R, typename...Args>
sak::Abstract_Signalbox<T,R,Args...>::~Abstract_Signalbox() = default;

#endif // SAK_ABSTRACT_PROJECT_SIGNALBOX_HPP
