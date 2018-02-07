#ifndef SAK_PROJECT_SIGNALBOX_DATA_HPP
#define SAK_PROJECT_SIGNALBOX_DATA_HPP

#ifndef SAK_PROJECT_SIGNALBOX_DATA_FWD_HPP
#include "project_signalbox_data_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_PROJECT_SIGNALBOX_FWD_HPP
#include "abstract_project_signalbox_fwd.hpp"
#endif

#ifndef SAK_HANDLE_FWD_HPP
#include "handle_fwd.hpp"
#endif

#ifndef FLAMINGO_TYPELIST_HPP
#include <flamingo/typelist.hpp>
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

#ifndef INCLUDE_STD_VECTOR
#define INCLUDE_STD_VECTOR
#include <vector>
#endif

/*

Object uses inheritance for construction:



Project_Signalbox_Data_Imp<A,B,C>
  protected Project_Data_Signalbox_Section_Imp<List<A,B,C>,A,B,C>
    protected Project_Data_Signalbox_Section_Imp<List<A,B,C>,A>
      protected virtual Project_Signalbox_Data_Shared_Imp<A,B,C>
    protected Project_Data_Signalbox_Section_Imp<List<A,B,C>,B,C>
      protected Project_Data_Signalbox_Section_Imp<List<A,B,C>,B>
        protected virtual Project_Signalbox_Data_Shared_Imp<A,B,C>
      protected Project_Data_Signalbox_Section_Imp<List<A,B,C>,C>
        protected virtual Project_Signalbox_Data_Shared_Imp<A,B,C>


uh oh forgot that adding and removing is going to involve the position index
if you want undo/redo to restore the ordering...
*/
namespace sak
{
  //---------------------------------------------------------------------------
  // Project_Signalbox_Data_Shared_Imp<T,Args...>
  //---------------------------------------------------------------------------
  // Implement the parts that the data sections will depend on via virtual
  // inheritance.
  template <typename T, typename...Args>
  class Project_Signalbox_Data_Shared_Imp
  {
  public:
    // Typedefs
    //============================================================
    using Signalbox_Type = Abstract_Signalbox<T,Args...>;

    // Special 6
    //============================================================
    Project_Signalbox_Data_Shared_Imp();
    ~Project_Signalbox_Data_Shared_Imp();

    Project_Signalbox_Data_Shared_Imp(Project_Signalbox_Data_Shared_Imp const&) = delete;
    Project_Signalbox_Data_Shared_Imp& operator=(Project_Signalbox_Data_Shared_Imp const&) = delete;

    Project_Signalbox_Data_Shared_Imp(Project_Signalbox_Data_Shared_Imp &&);
    Project_Signalbox_Data_Shared_Imp& operator=(Project_Signalbox_Data_Shared_Imp &&);

    // Interface
    //============================================================
    // Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
    void add_signalbox(Signalbox_Type* a_signalbox);
    // Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
    void remove_signalbox(Signalbox_Type* a_signalbox);
    // Clear all the signalboxes so that nothing relies on changes to this.
    void clear_signalboxes();
  protected:
    // Internal Interface
    //============================================================
    // Access the signalboxes so functions can be called in them.
    std::vector<Signalbox_Type*>& get_signalboxes();
    std::vector<Signalbox_Type*> const& cget_signalboxes() const;

  private:
    // Data Members
    //============================================================
    std::vector<Signalbox_Type*> m_signalboxes;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  namespace internal
  {
    //---------------------------------------------------------------------------
    // Typelist_To_Project_Singnalbox_Data_Shared_Imp<List>
    //---------------------------------------------------------------------------
    // Metafunction to convert a list of template arguments into a
    // Project_Data_Shared_Imp so that it can be used.
    template <typename T>
    class Typelist_To_Project_Signalbox_Data_Shared_Imp;

    template <typename...Args>
    class Typelist_To_Project_Signalbox_Data_Shared_Imp<flamingo::typelist<Args...>>
    {
    public:
      using Type = Project_Signalbox_Data_Shared_Imp<Args...>;
    };

    template <typename T>
    using Typelist_To_Project_Signalbox_Data_Shared_Imp_Type = typename Typelist_To_Project_Signalbox_Data_Shared_Imp<T>::Type;
  } // namespace internal


  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Project_Signalbox_Data_Section_Imp<List,T,Args...>
  //---------------------------------------------------------------------------
  // Implement the data sections via a recursive template. Each argument
  // uses Project_Signalbox_Data_Shared_Imp via virtual inheritance.

  // A single type implements the data.
  template <typename T_List, typename T>
  class Project_Signalbox_Data_Section_Imp<T_List,T> :
      protected virtual internal::Typelist_To_Project_Signalbox_Data_Shared_Imp_Type<T_List>
  {
    using Base = internal::Typelist_To_Project_Signalbox_Data_Shared_Imp_Type<T_List>;
  public:
    // Special 6
    //============================================================
    Project_Signalbox_Data_Section_Imp();
    ~Project_Signalbox_Data_Section_Imp();

    Project_Signalbox_Data_Section_Imp(Project_Signalbox_Data_Section_Imp const&) = delete;
    Project_Signalbox_Data_Section_Imp& operator=(Project_Signalbox_Data_Section_Imp const&) = delete;

    Project_Signalbox_Data_Section_Imp(Project_Signalbox_Data_Section_Imp &&);
    Project_Signalbox_Data_Section_Imp& operator=(Project_Signalbox_Data_Section_Imp &&);

    // Public Interface
    //============================================================
    // calls each of these on all the stored signalboxes.

    // When a handle has its data changed, this is called.
    void changed(Handle<T> const& a_handle);
    // When a handle has its name changed, this is called.
    void changed_name(Handle<T> const& a_handle);
    // When a handle has its data changed in a specific place, this is called.
    // a_section == 0 denotes the name and may have special logic requirements.
    void changed_at(Handle<T> const& a_handle, std::size_t a_section);
    // When a handle has been added, this is called.
    void added(Handle<T> const& a_handle);
    // When a handle has been removed, this is called.
    void removed(Handle<T> const& a_handle);
    // When a handle editor is to be opened, this is called.
    void requests_editor(Handle<T> const& a_handle);
    // When focus is changed to be on a handle, call this
    void requests_focus(Handle<T> const& a_handle);

    using Base::add_signalbox;
    using Base::remove_signalbox;
    using Base::clear_signalboxes;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  // Multiple types defers to the single type implementation and
  // chains them together with multiple inheritance.
  template <typename T_List, typename T, typename R, typename...Args>
  class Project_Signalbox_Data_Section_Imp<T_List,T,R,Args...> :
      protected Project_Signalbox_Data_Section_Imp<T_List,T>,
      protected Project_Signalbox_Data_Section_Imp<T_List,R,Args...>
  {
    using Inh1 = Project_Signalbox_Data_Section_Imp<T_List,T>;
    using Inh2 = Project_Signalbox_Data_Section_Imp<T_List,R,Args...>;
    using Base = internal::Typelist_To_Project_Signalbox_Data_Shared_Imp_Type<T_List>;
  public:
    // Special 6
    //============================================================
    Project_Signalbox_Data_Section_Imp() = default;
    ~Project_Signalbox_Data_Section_Imp() = default;

    Project_Signalbox_Data_Section_Imp(Project_Signalbox_Data_Section_Imp const&) = delete;
    Project_Signalbox_Data_Section_Imp& operator=(Project_Signalbox_Data_Section_Imp const&) = delete;

    Project_Signalbox_Data_Section_Imp(Project_Signalbox_Data_Section_Imp &&) = default;
    Project_Signalbox_Data_Section_Imp& operator=(Project_Signalbox_Data_Section_Imp &&) = default;

    // Public Interface
    //============================================================

    using Inh1::changed;
    using Inh1::changed_at;
    using Inh1::changed_name;
    using Inh1::added;
    using Inh1::removed;
    using Inh1::requests_editor;
    using Inh1::requests_focus;

    using Inh2::changed;
    using Inh2::changed_at;
    using Inh2::changed_name;
    using Inh2::added;
    using Inh2::removed;
    using Inh2::requests_editor;
    using Inh2::requests_focus;

    using Base::add_signalbox;
    using Base::remove_signalbox;
    using Base::clear_signalboxes;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Project_Signalbox_Data_Imp<T,Args...>
  //---------------------------------------------------------------------------
  //
  template <typename T, typename...Args>
  class Project_Signalbox_Data_Imp :
      private Project_Signalbox_Data_Section_Imp<flamingo::typelist<T,Args...>,T,Args...>
  {
    using Inh = Project_Signalbox_Data_Section_Imp<flamingo::typelist<T,Args...>,T,Args...>;

  public:
    // Special 6
    //============================================================
    Project_Signalbox_Data_Imp();
    ~Project_Signalbox_Data_Imp();

    Project_Signalbox_Data_Imp(Project_Signalbox_Data_Imp const&) = delete;
    Project_Signalbox_Data_Imp& operator=(Project_Signalbox_Data_Imp const&) = delete;

    Project_Signalbox_Data_Imp(Project_Signalbox_Data_Imp &&);
    Project_Signalbox_Data_Imp& operator=(Project_Signalbox_Data_Imp &&);

    // Interface
    //============================================================
    using Inh::changed;
    using Inh::changed_at;
    using Inh::changed_name;
    using Inh::added;
    using Inh::removed;
    using Inh::requests_editor;
    using Inh::requests_focus;

    using Inh::add_signalbox;
    using Inh::remove_signalbox;
    using Inh::clear_signalboxes;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

} // namespace sak

#endif // SAK_PROJECT_SIGNALBOX_DATA_HPP
