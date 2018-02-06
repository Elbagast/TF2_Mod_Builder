#ifndef SAK_PROJECT_DATA_HPP
#define SAK_PROJECT_DATA_HPP

#ifndef SAK_PROJECT_DATA_FWD_HPP
#include "project_data_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_PROJECT_SIGNALBOX_FWD_HPP
#include "abstract_project_signalbox_fwd.hpp"
#endif

#ifndef SAK_TAG_FWD_HPP
#include "tag_fwd.hpp"
#endif

#ifndef SAK_HANDLE_HPP
#include "handle.hpp"
#endif

#ifndef SAK_HANDLE_FACTORY_HPP
#include "handle_factory.hpp"
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

#ifndef INCLUDE_QT_QSTRING
#define INCLUDE_QT_QSTRING
#include <QString>
#endif

#ifndef INCLUDE_QT_QFILEINFO
#define INCLUDE_QT_QFILEINFO
#include <QFileInfo>
#endif
/*

Object uses inheritance for construction:

Project_Data_Imp<A,B,C>
  protected Project_Data_Section_Imp<List<A,B,C>,A,B,C>
    protected Project_Data_Section_Imp<List<A,B,C>,A>
      protected virtual Project_Data_Shared_Imp<A,B,C>
    protected Project_Data_Section_Imp<List<A,B,C>,B,C>
      protected Project_Data_Section<List<A,B,C>,B>
        protected virtual Project_Data_Shared_Imp<A,B,C>
      protected Project_Data_Section_Imp<List<A,B,C>,C>
        protected virtual Project_Data_Shared_Imp<A,B,C>



*/
namespace sak
{
  //---------------------------------------------------------------------------
  // Project_Data_Shared_Imp<T,Args...>
  //---------------------------------------------------------------------------
  // Implement the parts that the data sections will depend on via virtual
  // inheritance.
  template <typename T, typename...Args>
  class Project_Data_Shared_Imp
  {
  public:
    // Typedefs
    //============================================================
    using Signalbox_Type = Abstract_Signalbox<T,Args...>;

    // Special 6
    //============================================================
    Project_Data_Shared_Imp();
    ~Project_Data_Shared_Imp();

    Project_Data_Shared_Imp(Project_Data_Shared_Imp const&) = delete;
    Project_Data_Shared_Imp& operator=(Project_Data_Shared_Imp const&) = delete;

    Project_Data_Shared_Imp(Project_Data_Shared_Imp &&);
    Project_Data_Shared_Imp& operator=(Project_Data_Shared_Imp &&);

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

    // Get the next id for making handles.
    std::size_t next_id() const;
  private:
    // Data Members
    //============================================================
    mutable std::size_t m_next_id;
    std::vector<Signalbox_Type*> m_signalboxes;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  namespace internal
  {
    //---------------------------------------------------------------------------
    // Typelist_To_Project_Data_Shared_Imp<List>
    //---------------------------------------------------------------------------
    // Metafunction to convert a list of template arguments into a
    // Project_Data_Shared_Imp so that it can be used.
    template <typename T>
    class Typelist_To_Project_Data_Shared_Imp;

    template <typename...Args>
    class Typelist_To_Project_Data_Shared_Imp<flamingo::typelist<Args...>>
    {
    public:
      using Type = Project_Data_Shared_Imp<Args...>;
    };

    template <typename T>
    using Typelist_To_Project_Data_Shared_Imp_Type = typename Typelist_To_Project_Data_Shared_Imp<T>::Type;
  } // namespace internal


  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Project_Data_Section_Imp<List,T,Args...>
  //---------------------------------------------------------------------------
  // Implement the data sections via a recursive template. Each argument
  // uses Project_Data_Shared_Imp via virtual inheritance.

  // A single type implements the data.
  template <typename T_List, typename T>
  class Project_Data_Section_Imp<T_List,T> :
      protected virtual internal::Typelist_To_Project_Data_Shared_Imp_Type<T_List>
  {
    using Base = internal::Typelist_To_Project_Data_Shared_Imp_Type<T_List>;
  public:
    // Special 6
    //============================================================
    Project_Data_Section_Imp();
    ~Project_Data_Section_Imp();

    Project_Data_Section_Imp(Project_Data_Section_Imp const&) = delete;
    Project_Data_Section_Imp& operator=(Project_Data_Section_Imp const&) = delete;

    Project_Data_Section_Imp(Project_Data_Section_Imp &&);
    Project_Data_Section_Imp& operator=(Project_Data_Section_Imp &&);

    // Public Interface
    //============================================================
    // Are there any handles of this type in the currently active project data?
    bool empty(Tag<T>&&) const;

    // How handles of this type in the currently active project data?
    std::size_t count(Tag<T>&&) const;

    // Does this handle appear in the data?
    bool has_handle(Handle<T> const& a_handle) const;

    // Does this name appear in the data?
    bool has_handle_named(Tag<T>&&, QString const& a_name) const;

    // Get the handle at this index. Handles are sorted alphabetically by the name
    // member of the objects they reference.
    Handle<T> get_handle_at(Tag<T>&&, std::size_t a_index) const;

    // Get the handle with this name. If the name is invalid a null handle is returned.
    Handle<T> get_handle_named(Tag<T>&&, QString const& a_name) const;

    // Get all the handles in data order
    std::vector<Handle<T>> const& get_handles(Tag<T>&&) const;

    // Get all the handles names in data order
    std::vector<QString> get_names(Tag<T>&&) const;

    // You may create new objects using these two functions. Objects created in this way
    // are part of the data management system but nothing outside of it has been notified
    // of their presense. Calling has_handle on the handle returned by these functions
    // immediately after will return false.

    // Make a new object using the supplied data. Project's data management system owns it but
    // it is not part of the Project.
    Handle<T> make_emplace(Data<T>&& a_object) const;

    // Make a new file using the default parameters. Project's data management system owns it
    // but it is not part of the Project.
    Handle<T> make_default(Tag<T>&&) const;

    // Attempt to add a handle to the data and return true if it succeeds. Will
    // fail and return false if the handle is null or already present in the data.
    bool add(Handle<T> const& a_handle);

    // Attempt to remove a handle from the data and return true if it succeeds. Will
    // fail and return false if the handle is null or not present in the data.
    bool remove(Handle<T> const& a_handle);

    // Interface
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

  private:
    // Data Members
    //============================================================
    std::vector<Handle<T>> m_handles;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  // Multiple types defers to the single type implementation and
  // chains them together with multiple inheritance.
  template <typename T_List, typename T, typename R, typename...Args>
  class Project_Data_Section_Imp<T_List,T,R,Args...> :
      protected Project_Data_Section_Imp<T_List,T>,
      protected Project_Data_Section_Imp<T_List,R,Args...>
  {
    using Inh1 = Project_Data_Section_Imp<T_List,T>;
    using Inh2 = Project_Data_Section_Imp<T_List,R,Args...>;
    using Base = internal::Typelist_To_Project_Data_Shared_Imp_Type<T_List>;
  public:
    // Special 6
    //============================================================
    Project_Data_Section_Imp() = default;
    ~Project_Data_Section_Imp() = default;

    Project_Data_Section_Imp(Project_Data_Section_Imp const&) = delete;
    Project_Data_Section_Imp& operator=(Project_Data_Section_Imp const&) = delete;

    Project_Data_Section_Imp(Project_Data_Section_Imp &&) = default;
    Project_Data_Section_Imp& operator=(Project_Data_Section_Imp &&) = default;

    // Public Interface
    //============================================================

    using Inh1::empty;
    using Inh1::count;
    using Inh1::has_handle;
    using Inh1::has_handle_named;
    using Inh1::get_handle_at;
    using Inh1::get_handle_named;
    using Inh1::get_handles;
    using Inh1::get_names;
    using Inh1::make_emplace;
    using Inh1::make_default;
    using Inh1::add;
    using Inh1::remove;

    using Inh1::changed;
    using Inh1::changed_at;
    using Inh1::added;
    using Inh1::removed;
    using Inh1::requests_editor;
    using Inh1::requests_focus;


    using Inh2::empty;
    using Inh2::count;
    using Inh2::has_handle;
    using Inh2::has_handle_named;
    using Inh2::get_handle_at;
    using Inh2::get_handle_named;
    using Inh2::get_handles;
    using Inh2::get_names;
    using Inh2::make_emplace;
    using Inh2::make_default;
    using Inh2::add;
    using Inh2::remove;

    using Inh2::changed;
    using Inh2::changed_at;
    using Inh2::added;
    using Inh2::removed;
    using Inh2::requests_editor;
    using Inh2::requests_focus;

    using Base::add_signalbox;
    using Base::remove_signalbox;
    using Base::clear_signalboxes;

  private:
    // Data Members
    //============================================================
    mutable Handle_Factory<T> m_factory;
    std::vector<Handle<T>> m_handles;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Project_Data_Imp<T,Args...>
  //---------------------------------------------------------------------------
  // The top of the project data implements the parts of the project that are
  // independent of all else (e.g. filename) and also the parts that require
  // all the data sections (e.g. fix_name).
  template <typename T, typename...Args>
  class Project_Data_Imp :
      private Project_Data_Section_Imp<flamingo::typelist<T,Args...>,T,Args...>
  {
    using Inh = Project_Data_Section_Imp<flamingo::typelist<T,Args...>,T,Args...>;

  public:
    // Special 6
    //============================================================
    explicit Project_Data_Imp(QString const& a_filepath);
    ~Project_Data_Imp();

    Project_Data_Imp(Project_Data_Imp const&) = delete;
    Project_Data_Imp& operator=(Project_Data_Imp const&) = delete;

    Project_Data_Imp(Project_Data_Imp &&);
    Project_Data_Imp& operator=(Project_Data_Imp &&);

    // Interface
    //============================================================
    QString name() const;
    QString location() const;
    QString filepath() const;

    // Does this name appear in the data?
    bool has_name(QString const& a_name) const;
    // Get all the objects names in data order
    std::vector<QString> get_all_names() const;
    // Alter the supplied name so that it is unique among the existing data names
    void fix_name(QString& a_name) const;

    // Each of these will be overloaded for as many template args there are.
    using Inh::empty;
    using Inh::count;
    using Inh::has_handle;
    using Inh::has_handle_named;
    using Inh::get_handle_at;
    using Inh::get_handle_named;
    using Inh::get_handles;
    using Inh::get_names;
    using Inh::make_emplace;
    using Inh::make_default;
    using Inh::add;
    using Inh::remove;

    using Inh::changed;
    using Inh::changed_at;
    using Inh::added;
    using Inh::removed;
    using Inh::requests_editor;
    using Inh::requests_focus;

    using Inh::add_signalbox;
    using Inh::remove_signalbox;
    using Inh::clear_signalboxes;
  private:
    QFileInfo m_filepath;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

} // namespace sak

#endif // SAK_PROJECT_DATA_HPP
