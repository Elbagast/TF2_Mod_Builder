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
  class Abstract_Project_Signalbox :
      public Abstract_File_Signalbox
      ,public Abstract_Texture_Signalbox
  {
  public:
    ~Abstract_Project_Signalbox() override = 0;
  };
} // namespace sak

namespace sak
{

  namespace v2
  {
    //---------------------------------------------------------------------------
    // Abstract_Signalbox<T>
    //---------------------------------------------------------------------------

    // One type has all these functions.
    template <typename T>
    class Abstract_Signalbox
    {
    public:
      virtual ~Abstract_Signalbox() = 0;

      // When a handle has its data changed, this is called.
      virtual void changed(Handle<T> const& a_handle) = 0;
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

    //---------------------------------------------------------------------------
    // Abstract_Chained_Signalbox<Args...>
    //---------------------------------------------------------------------------
    // For a project managing Args as parallel types that all have the same
    // format of signals.

    template <typename T, typename...Args>
    class Abstract_Chained_Signalbox;

    // One type has all these functions.
    template <typename T>
    class Abstract_Chained_Signalbox<T> :
        private virtual Abstract_Section_Signalbox<T>
    {
    public:
      ~Abstract_Chained_Signalbox() override = 0;

      using Abstract_Section_Signalbox<T>::changed;
      using Abstract_Section_Signalbox<T>::changed_at;
      using Abstract_Section_Signalbox<T>::added;
      using Abstract_Section_Signalbox<T>::removed;
      using Abstract_Section_Signalbox<T>::requests_editor;
      using Abstract_Section_Signalbox<T>::requests_focus;
    };

    // For at least 2, we inherit one and use it's functions, then chain the next
    // and expose its functions too.
    template <typename T, typename R, typename...Args>
    class Abstract_Chained_Signalbox<T,R,Args...>:
        private virtual Abstract_Chained_Signalbox<T>,
        private virtual Abstract_Chained_Signalbox<R, Args...>
    {
    public:
      ~Abstract_Chained_Signalbox() override = 0;

      using Abstract_Chained_Signalbox<T>::changed;
      using Abstract_Chained_Signalbox<T>::changed_at;
      using Abstract_Chained_Signalbox<T>::added;
      using Abstract_Chained_Signalbox<T>::removed;
      using Abstract_Chained_Signalbox<T>::requests_editor;
      using Abstract_Chained_Signalbox<T>::requests_focus;

      using Abstract_Chained_Signalbox<R, Args...>::changed;
      using Abstract_Chained_Signalbox<R, Args...>::changed_at;
      using Abstract_Chained_Signalbox<R, Args...>::added;
      using Abstract_Chained_Signalbox<R, Args...>::removed;
      using Abstract_Chained_Signalbox<R, Args...>::requests_editor;
      using Abstract_Chained_Signalbox<R, Args...>::requests_focus;
    };

    //---------------------------------------------------------------------------
    // Abstract_Project_Signalbox
    //---------------------------------------------------------------------------
    // Being able to expand this whenever is literally the only reason to do this.
    using Abstract_Project_Signalbox = Abstract_Chained_Signalbox<File_Data,Texture_Data>;
  }
}


//---------------------------------------------------------------------------
// Abstract_Signalbox<T>
//---------------------------------------------------------------------------
template <typename T>
sak::v2::Abstract_Signalbox<T>::~Abstract_Signalbox() = default;

//---------------------------------------------------------------------------
// Abstract_Chained_Signalbox<Args...>
//---------------------------------------------------------------------------
//template <>
//sak::v2::Abstract_Chained_Signalbox<>::~Abstract_Chained_Signalbox() = default;

template <typename T>
sak::v2::Abstract_Chained_Signalbox<T>::~Abstract_Chained_Signalbox() = default;

template <typename T, typename R, typename...Args>
sak::v2::Abstract_Chained_Signalbox<T,R,Args...>::~Abstract_Chained_Signalbox() = default;

#endif // SAK_ABSTRACT_PROJECT_SIGNALBOX_HPP
