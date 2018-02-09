#ifndef SAK_PROJECT_DATA_HPP
#define SAK_PROJECT_DATA_HPP

#ifndef SAK_PROJECT_DATA_FWD_HPP
#include "project_data_fwd.hpp"
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


uh oh forgot that adding and removing is going to involve the position index
if you want undo/redo to restore the ordering...

*/
namespace sak
{
  //---------------------------------------------------------------------------
  // Project_Data_Section_Data_Imp<T,Args...>
  //---------------------------------------------------------------------------
  // Implement the data members for all the sections so that the part that
  // implements the interface can access all of the different handle types.
  // We could have this implement a bunch of the interface too but that would
  // make things messier.

  // A single type implements the data.
  template <typename T>
  class Project_Data_Section_Data_Imp<T>
  {
  public:
    // Special 6
    //============================================================
    Project_Data_Section_Data_Imp();
    ~Project_Data_Section_Data_Imp();

    Project_Data_Section_Data_Imp(Project_Data_Section_Data_Imp const&) = delete;
    Project_Data_Section_Data_Imp& operator=(Project_Data_Section_Data_Imp const&) = delete;

    Project_Data_Section_Data_Imp(Project_Data_Section_Data_Imp &&);
    Project_Data_Section_Data_Imp& operator=(Project_Data_Section_Data_Imp &&);

    // Public Interface
    //============================================================
    std::vector<Handle<T>>& imp_handles(Tag<T>&&);
    std::vector<Handle<T>> const& cimp_handles(Tag<T>&&) const;
  private:
    // Data Members
    //============================================================
    std::vector<Handle<T>> m_handles;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  // Multiple types defers to the single type implementation and
  // chains them together with multiple inheritance.
  template <typename T, typename R, typename...Args>
  class Project_Data_Section_Data_Imp<T,R,Args...> :
      protected Project_Data_Section_Data_Imp<T>,
      protected Project_Data_Section_Data_Imp<R,Args...>
  {
    using Inh1 = Project_Data_Section_Data_Imp<T>;
    using Inh2 = Project_Data_Section_Data_Imp<R,Args...>;
  public:
    // Special 6
    //============================================================
    Project_Data_Section_Data_Imp() = default;
    ~Project_Data_Section_Data_Imp() = default;

    Project_Data_Section_Data_Imp(Project_Data_Section_Data_Imp const&) = delete;
    Project_Data_Section_Data_Imp& operator=(Project_Data_Section_Data_Imp const&) = delete;

    Project_Data_Section_Data_Imp(Project_Data_Section_Data_Imp &&) = default;
    Project_Data_Section_Data_Imp& operator=(Project_Data_Section_Data_Imp &&) = default;

    // Public Interface
    //============================================================

    using Inh1::imp_handles;
    using Inh1::cimp_handles;

    using Inh2::imp_handles;
    using Inh2::cimp_handles;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Project_Data_Shared_Imp<T,Args...>
  //---------------------------------------------------------------------------
  // Implement the parts that the data sections will depend on via virtual
  // inheritance.
  template <typename T, typename...Args>
  class Project_Data_Shared_Imp :
      protected Project_Data_Section_Data_Imp<T,Args...>
  {
    using Inh = Project_Data_Section_Data_Imp<T,Args...>;
  public:
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
    // Does this name appear in the data?
    bool has_name(QString const& a_name) const;
    // Get all the objects names in data order
    std::vector<QString> get_all_names() const;
    // Alter the supplied name so that it is unique among the existing data names
    void fix_name(QString& a_name) const;

    using Inh::imp_handles;
    using Inh::cimp_handles;
  protected:
    // Internal Interface
    //============================================================
    // Get the next id for making handles.
    std::size_t next_id() const;

  private:
    // Data Members
    //============================================================
    mutable std::size_t m_next_id;
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

    using Base::has_name;
    using Base::get_all_names;
    using Base::fix_name;
  private:
    using Base::imp_handles;
    using Base::cimp_handles;

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

    using Base::has_name;
    using Base::get_all_names;
    using Base::fix_name;

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
      protected Project_Data_Section_Imp<flamingo::typelist<T,Args...>,T,Args...>
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

    using Inh::has_name;
    using Inh::get_all_names;
    using Inh::fix_name;

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

  private:
    QFileInfo m_filepath;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  namespace internal
  {
    //---------------------------------------------------------------------------
    // v2Project_Raw_Data_Part_Imp<List, Index, End>
    //---------------------------------------------------------------------------
    // Declaration and default arguments for the template class that builds the
    // template chain.
    template
    <
      typename T_List,
      std::size_t Index = 0,
      std::size_t End = (flamingo::typelist_size_v<T_List> - 1)
    >
    class v2Project_Raw_Data_Part_Imp;

    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // v2Project_Raw_Data_Part_Imp<List, Index, End>
    //---------------------------------------------------------------------------
    // For a type that isn't at the end of the list.
    template <std::size_t Index, std::size_t End, typename...Args>
    class v2Project_Raw_Data_Part_Imp<flamingo::typelist<Args...>,Index,End> :
        protected v2Project_Raw_Data_Part_Imp<flamingo::typelist<Args...>,Index+1,End>
    {
      // Typedefs
      //============================================================
      using Inh = v2Project_Raw_Data_Part_Imp<flamingo::typelist<Args...>,Index+1,End>;

      using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,Index>;
      using Handle_Type = Handle<Type>;
      using Tag_Type = Tag<Type>;

    public:
      // Special 6
      //============================================================
      v2Project_Raw_Data_Part_Imp();
      ~v2Project_Raw_Data_Part_Imp();

      // Interface
      //============================================================
      // Access the handles for direct manipulation.
      std::vector<Handle_Type>& get_raw_handles(Tag_Type&&);
      std::vector<Handle_Type> const& cget_raw_handles(Tag_Type&&) const;

      using Inh::get_raw_handles;
      using Inh::cget_raw_handles;

    private:
      std::vector<Handle_Type> m_handles;
    };

    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // v2Project_Raw_Data_Part_Imp<List, End, End>
    //---------------------------------------------------------------------------
    // For a type that isn't at the end of the list.
    template <std::size_t End, typename...Args>
    class v2Project_Raw_Data_Part_Imp<flamingo::typelist<Args...>,End,End>
    {
      // Typedefs
      //============================================================
      using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,End>;
      using Handle_Type = Handle<Type>;
      using Tag_Type = Tag<Type>;

    public:
      // Special 6
      //============================================================
      v2Project_Raw_Data_Part_Imp();
      ~v2Project_Raw_Data_Part_Imp();

      // Interface
      //============================================================
      // Access the handles for direct manipulation.
      std::vector<Handle_Type>& get_raw_handles(Tag_Type&&);
      std::vector<Handle_Type> const& cget_raw_handles(Tag_Type&&) const;

    private:
      std::vector<Handle_Type> m_handles;
    };

    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // v2Project_Raw_Data_Imp<List, End, End>
    //---------------------------------------------------------------------------
    // The bit that holds all of the Project data allowing access for layers that
    // need all of it.
    template <typename T, typename...Args>
    class v2Project_Raw_Data_Imp :
        protected v2Project_Raw_Data_Part_Imp<flamingo::typelist<T,Args...>>
    {
      // Typedefs
      //============================================================
      using Inh = v2Project_Raw_Data_Part_Imp<flamingo::typelist<T,Args...>>;
    public:
      // Special 6
      //============================================================
      v2Project_Raw_Data_Imp();
      ~v2Project_Raw_Data_Imp();

      // Interface
      //============================================================
      // Does this name appear in the data?
      bool has_name(QString const&) const;
      // Get all the objects names in alphabetical order. The true
      // types that are associated with the names are ignored.
      std::vector<QString> get_all_names() const;
      // Alter the supplied name so that it is unique among the
      // existing data names.
      void fix_name(QString&) const;

      using Inh::get_raw_handles;
      using Inh::cget_raw_handles;

      // Functions are as follows, with overloads for each Type in the
      // the arguments <T,Args...>:
      //------------------------------------------------------------
      // Access the handles for direct manipulation.
      //std::vector<Handle_Type>& get_handles(Tag_Type&&);
      //std::vector<Handle_Type> const& cget_handles(Tag_Type&&) const;
    };


    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // v2Project_Data_Part_Imp<List, Index, End>
    //---------------------------------------------------------------------------
    // Declaration and default arguments for the template class that builds the
    // template chain.
    template
    <
      typename T_List,
      std::size_t Index = 0,
      std::size_t End = (flamingo::typelist_size_v<T_List> - 1)
    >
    class v2Project_Data_Part_Imp;

    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // v2Project_Data_Part_Imp<List, Index, End>
    //---------------------------------------------------------------------------
    // For a type that isn't at the end of the list.
    template <std::size_t Index, std::size_t End, typename...Args>
    class v2Project_Data_Part_Imp<flamingo::typelist<Args...>,Index,End> :
        protected v2Project_Data_Part_Imp<flamingo::typelist<Args...>,Index+1,End>
    {
      // Typedefs
      //============================================================
      using Inh = v2Project_Data_Part_Imp<flamingo::typelist<Args...>,Index+1,End>;

      using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,Index>;
      using Data_Type = Data<Type>;
      using Handle_Type = Handle<Type>;
      using Tag_Type = Tag<Type>;

    public:
      // Special 6
      //============================================================
      v2Project_Data_Part_Imp();
      ~v2Project_Data_Part_Imp();

      // Interface
      //============================================================
      // Are there any handles of this type in the currently
      // active project data?
      bool empty(Tag_Type&&) const;

      // How handles of this type in the currently active project
      // data?
      std::size_t count(Tag_Type&&) const;

      // Does this handle appear in the data?
      bool has_handle(Handle_Type const& a_handle) const;

      // Does this name appear in the data?
      bool has_handle_named(Tag_Type&&, QString const& a_name) const;

      // Get the handle at this index. Handles are sorted
      // alphabetically by name. If the index is invalid a null
      // handle is returned.
      Handle_Type get_handle_at(Tag_Type&&, std::size_t a_index) const;

      // Get the handle with this name. If the name is invalid a null
      // handle is returned.
      Handle_Type get_handle_named(Tag_Type&&, QString const& a_name) const;

      // Get all the handles names in alphabetical order.
      std::vector<QString> get_names(Tag_Type&&) const;

      // Get all the handles
      std::vector<Handle_Type> const& get_handles(Tag_Type&&) const;

      using Inh::empty;
      using Inh::count;
      using Inh::has_handle;
      using Inh::has_handle_named;
      using Inh::get_handle_at;
      using Inh::get_handle_named;
      using Inh::get_names;
      using Inh::get_handles;

      using Inh::has_name;
      using Inh::get_all_names;
      using Inh::fix_name;

    protected:
      using Inh::get_raw_handles;
      using Inh::cget_raw_handles;
    };

    //------------------------------------------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // v2Project_Raw_Data_Part_Imp<List, End, End>
    //---------------------------------------------------------------------------
    // For a type that isn't at the end of the list.
    template <std::size_t End, typename...Args>
    class v2Project_Data_Part_Imp<flamingo::typelist<Args...>,End,End> :
        protected v2Project_Raw_Data_Part_Imp<flamingo::typelist<Args...>>
    {
      // Typedefs
      //============================================================
      using Inh = v2Project_Raw_Data_Part_Imp<flamingo::typelist<Args...>>;
      using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,End>;
      using Data_Type = Data<Type>;
      using Handle_Type = Handle<Type>;
      using Tag_Type = Tag<Type>;

    public:
      // Special 6
      //============================================================
      v2Project_Data_Part_Imp();
      ~v2Project_Data_Part_Imp();

      // Interface
      //============================================================
      // Are there any handles of this type in the currently
      // active project data?
      bool empty(Tag_Type&&) const;

      // How handles of this type in the currently active project
      // data?
      std::size_t count(Tag_Type&&) const;

      // Does this handle appear in the data?
      bool has_handle(Handle_Type const& a_handle) const;

      // Does this name appear in the data?
      bool has_handle_named(Tag_Type&&, QString const& a_name) const;

      // Get the handle at this index. Handles are sorted
      // alphabetically by name. If the index is invalid a null
      // handle is returned.
      Handle_Type get_handle_at(Tag_Type&&, std::size_t a_index) const;

      // Get the handle with this name. If the name is invalid a null
      // handle is returned.
      Handle_Type get_handle_named(Tag_Type&&, QString const& a_name) const;

      // Get all the handles names in alphabetical order.
      std::vector<QString> get_names(Tag_Type&&) const;

      // Get all the handles
      std::vector<Handle_Type> const& get_handles(Tag_Type&&) const;

      using Inh::empty;
      using Inh::count;
      using Inh::has_handle;
      using Inh::has_handle_named;
      using Inh::get_handle_at;
      using Inh::get_handle_named;
      using Inh::get_names;
      using Inh::get_handles;

      using Inh::has_name;
      using Inh::get_all_names;
      using Inh::fix_name;

    protected:
      using Inh::get_raw_handles;
      using Inh::cget_raw_handles;
      using Inh::next_id;
    };


  } // namespace internal

  template <typename T, typename...Args>
  class v2Project_Data_Imp :
      protected internal::v2Project_Raw_Data_Part_Imp<flamingo::typelist<T,Args...>>
  {
    // Typedefs
    //============================================================
    using Inh = internal::v2Project_Raw_Data_Part_Imp<flamingo::typelist<T,Args...>>;
  public:
    // Special 6
    //============================================================
    v2Project_Data_Imp();
    ~v2Project_Data_Imp();

    // Interface
    //============================================================
    // Does this name appear in the data?
    bool has_name(QString const&) const;
    // Get all the objects names in alphabetical order. The true
    // types that are associated with the names are ignored.
    std::vector<QString> get_all_names() const;
    // Alter the supplied name so that it is unique among the
    // existing data names.
    void fix_name(QString&) const;

    // Get the next id to make a handle with.
    std::size_t next_id() const;

    using Inh::empty;
    using Inh::count;
    using Inh::has_handle;
    using Inh::has_handle_named;
    using Inh::get_handle_at;
    using Inh::get_handle_named;
    using Inh::get_names;
    using Inh::get_handles;
    using Inh::cget_handles;

    // Functions are as follows, with overloads for each Type in the
    // the arguments <T,Args...>:
    //------------------------------------------------------------
    // Are there any handles of this type in the currently
    // active project data?
    //bool empty(Tag_Type&&) const;

    // How handles of this type in the currently active project
    // data?
    //std::size_t count(Tag_Type&&) const;

    // Does this handle appear in the data?
    //bool has_handle(Handle_Type const& a_handle) const;

    // Does this name appear in the data?
    //bool has_handle_named(Tag_Type&&, QString const& a_name) const;

    // Get the handle at this index. Handles are sorted
    // alphabetically by name. If the index is invalid a null
    // handle is returned.
    //Handle_Type get_handle_at(Tag_Type&&, std::size_t a_index) const;

    // Get the handle with this name. If the name is invalid a null
    // handle is returned.
    //Handle_Type get_handle_named(Tag_Type&&, QString const& a_name) const;

    // Get all the handles names in alphabetical order.
    //std::vector<QString> get_names(Tag_Type&&) const;

    // Access the handles for direct manipulation.
    //std::vector<Handle_Type>& get_handles(Tag_Type&&);

    //std::vector<Handle_Type> const& cget_handles(Tag_Type&&) const;
  private:
    mutable std::size_t m_next_id;
  };

} // namespace sak

#endif // SAK_PROJECT_DATA_HPP
