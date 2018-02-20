#include "test_abstract_project_interface.hpp"

#include <sak/data_definitions.hpp>
#include <sak/class_definitions.hpp>
#include <sak/tag.hpp>
#include <sak/id.hpp>
#include <sak/abstract_project_interface.hpp>
#include <sak/signal_source.hpp>

#include <iostream>
#include <cassert>

#include <QString>

#include <flamingo/typelist.hpp>

namespace sak
{
  //---------------------------------------------------------------------------
  // Member_Interface_Imp<List,LI,MI,LL,ML>
  //---------------------------------------------------------------------------
  // Declaration and default arguments for the template class that builds the
  // template chain.

  template
  <
    typename T_List,
    std::size_t T_List_Index = 0,
    std::size_t T_Member_Index = 0,
    std::size_t T_List_Last = (flamingo::typelist_size_v<T_List> - 1 ), // for count N, is N-1
    std::size_t T_Member_Last = (Class_Def_Size_v<flamingo::typelist_at_t<T_List,T_List_Index>>) // for count N, is N
  >
  class Member_Interface_Imp;

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Member_Interface_Imp<List,LI,MI,LL,ML>
  //---------------------------------------------------------------------------
  // For a member that isn't the last in a type that isn't the last in the list.

  template <std::size_t LI, std::size_t MI, std::size_t LL, std::size_t ML, typename...Args>
  class Member_Interface_Imp<flamingo::typelist<Args...>,LI,MI,LL,ML> :
      public Member_Interface_Imp<flamingo::typelist<Args...>,LI,MI+1>
  {
    using Inh = Member_Interface_Imp<flamingo::typelist<Args...>,LI,MI+1>;
    using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,LI>;
    using Data_Type = Data<Type>;
    using ID_Type = ID<Type>;
    static constexpr std::size_t const index = MI;
    using Index_Tag_Type = Index_Tag<index>;
    using Member_Value_Type = Data_Member_Value_Type<index,Data_Type>;

    static_assert(Class_Def_Size_v<Type> != 0, "Cannot use data with no members.");
  public:

    // Special 6
    //============================================================
    ~Member_Interface_Imp() override = default;

    // Interface
    //============================================================
    // Attempt to get the data value for the member at this index in the data associated with the
    // supplied id. If the id is valid, the returned pair consists of true and the data value. If
    // the id is null or invalid, the returned pair consists of false and a default constructed
    // value.
    std::pair<bool,Member_Value_Type> try_get(Index_Tag_Type&&, ID_Type const& a_id) const override
    {
      std::cout << "sak::Member_Interface_Imp::try_get" << " " << LI << "," << MI << "," << LL << "," << ML << std::endl;
      return std::pair<bool,Member_Value_Type>{};
    }

    // Attempt an undoable change to the data value for the member at this index in the data
    // associated with the supplied id. If the id is valid and the supplied value results in a
    // change to the data (e.g. does not compare the same as the current), signals are emitted
    // telling everything to update this value, and true is returned. If the id is null or
    // invalid, nothing happens and false is returned.
    bool try_set(Index_Tag_Type&&, ID_Type const& a_id, Member_Value_Type const& a_value) const override
    {
      std::cout << "sak::Member_Interface_Imp::try_set" << " " << LI << "," << MI << "," << LL << "," << ML << std::endl;
      return false;
    }
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Member_Interface_Imp<List,LI,ML,LL,ML>
  //---------------------------------------------------------------------------
  // For a member that is the last in a type that isn't the last in the list.

  template <std::size_t LI, std::size_t LL, std::size_t ML, typename...Args>
  class Member_Interface_Imp<flamingo::typelist<Args...>,LI,ML,LL,ML> :
      public Member_Interface_Imp<flamingo::typelist<Args...>,LI+1>
  {
  public:
    // Special 6
    //============================================================
    ~Member_Interface_Imp() override = default;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Member_Interface_Imp<List,LL,ML,LL,ML>
  //---------------------------------------------------------------------------
  // For a member that is the last in the last type in the list. This is the
  // end of the template chain.

  template <std::size_t LL, std::size_t ML, typename...Args>
  class Member_Interface_Imp<flamingo::typelist<Args...>,LL,ML,LL,ML> :
      public Abstract_Project_Interface_Imp<Args...>
  {
  public:
    // Special 6
    //============================================================
    ~Member_Interface_Imp() override = default;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Section_Interface_Imp<List,LI,LL>
  //---------------------------------------------------------------------------
  // Declaration and default arguments for the template class that builds the
  // template chain.
  template
  <
      typename T_List,
      std::size_t T_List_Index = 0,
      std::size_t T_List_Size = (flamingo::typelist_size_v<T_List>) // for list size N, is N
  >
  class Section_Interface_Imp;

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Section_Interface_Imp<List,LI,LS>
  //---------------------------------------------------------------------------
  // For a type in the list, build its interface.

  template <std::size_t LI, std::size_t LS, typename...Args>
  class Section_Interface_Imp<flamingo::typelist<Args...>,LI,LS> :
      public Section_Interface_Imp<flamingo::typelist<Args...>,LI+1>
  {
    using Inh = Section_Interface_Imp<flamingo::typelist<Args...>,LI+1>;
    using Type = flamingo::typelist_at_t<flamingo::typelist<Args...>,LI>;
    using Data_Type = Data<Type>;
    using ID_Type = ID<Type>;
    //using Handle_Type = Handle<Type>;
    using Tag_Type = Tag<Type>;

    static_assert(Class_Def_Size_v<Type> != 0, "Cannot use data with no members.");
  public:

    // Special 6
    //============================================================
    ~Section_Interface_Imp() override = default;

    // Interface
    //============================================================

    // Collection Interface
    //------------------------------------------------------------
    // Are there any objects in this Project?
    bool is_empty(Tag_Type&&) const override
    {
      std::cout << "sak::Section_Interface_Imp::is_empty" << " " << LI << "," << LS << std::endl;
      return false;
    }

    // How many objects are in this Project?
    std::size_t count(Tag_Type&&) const override
    {
      std::cout << "sak::Section_Interface_Imp::count" << " " << LI << "," << LS << std::endl;
      return std::size_t{};
    }

    // Does this id appear in the data?
    bool has(ID_Type const& a_id) const override
    {
      std::cout << "sak::Section_Interface_Imp::has" << " " << LI << "," << LS << std::endl;
      return false;
    }

    // Does this name appear in the data?
    bool has_name(Tag_Type&&, QString const&) const override
    {
      std::cout << "sak::Section_Interface_Imp::has_name" << " " << LI << "," << LS << std::endl;
      return false;
    }

    // Get the id at this index. If the index is invalid a null id is returned.
    ID_Type get_at(Tag_Type&&, std::size_t a_index) const override
    {
      std::cout << "sak::Section_Interface_Imp::get_at" << " " << LI << "," << LS << std::endl;
      return ID_Type{};
    }

    // Get the id with this name. If the name is invalid a null id is returned.
    ID_Type get_named(Tag_Type&&, QString const&) const override
    {
      std::cout << "sak::Section_Interface_Imp::get_named" << " " << LI << "," << LS << std::endl;
      return ID_Type{};
    }

    // Get all the ids in data order
    std::vector<ID_Type> get_ids(Tag_Type&&) const override
    {
      std::cout << "sak::Section_Interface_Imp::get_ids" << " " << LI << "," << LS << std::endl;
      return std::vector<ID_Type>{};
    }

    // Get all the handles names in data order
    std::vector<QString> get_names(Tag_Type&&) const override
    {
      std::cout << "sak::Section_Interface_Imp::get_names" << " " << LI << "," << LS << std::endl;
      return std::vector<QString>{};
    }

    // Data Interface
    //------------------------------------------------------------
    // Attempt to get the index of the data associated with the supplied id. This is the current
    // position in the project's collection of data for this type of index. If the id is valid,
    // the returned pair consists of true and the index. If the id is null or invalid, the
    // returned pair consists of false and zero.
    std::pair<bool,std::size_t> try_get_index(ID_Type const& a_id) const override
    {
      std::cout << "sak::Section_Interface_Imp::try_get_index" << " " << LI << "," << LS << std::endl;
      return std::pair<bool,std::size_t>{};
    }

    // Attempt to get the name for the data associated with the supplied id. If the id is valid,
    // the returned pair consists of true and the name value. If the id is null or invalid, the
    // returned pair consists of false and an empty string.
    std::pair<bool,QString> try_get_name(ID_Type const& a_id) const override
    {
      std::cout << "sak::Section_Interface_Imp::try_get_name" << " " << LI << "," << LS << std::endl;
      return std::pair<bool,QString>{};
    }

    // Data Editing Interface
    //------------------------------------------------------------
    // Attempt an undoable change to the name of the data associated with the supplied id. If
    // the id is valid and the supplied value results in a change to the data, signals are emitted
    // telling everything to update this name, and true is returned. If the id is null or
    // invalid, nothing happens and false is returned. Success does not indicate that the name
    // is set to what has been supplied, but that the name has changed.
    bool try_set_name(Signal_Source a_source, ID_Type const& a_id, QString const& a_name) override
    {
      std::cout << "sak::Section_Interface_Imp::try_set_name" << " " << LI << "," << LS << std::endl;
      return false;
    }

    // Collection Editing Interface
    //------------------------------------------------------------
    // Undoable add a new object made using the default parameters. Returns the id of the new
    // data.
    ID_Type add_default(Tag_Type&&, Signal_Source a_source) override
    {
      std::cout << "sak::Section_Interface_Imp::add_default" << " " << LI << "," << LS << std::endl;
      return ID_Type{};
    }

    // Undoable add a new object using the supplied handle. The name will be modified if it is currently in
    // use by another object. Return true if the operation resulted in an undoable command. If this handle
    // is invalid or already in the data then nothing happens and returns false.
    bool try_add(Signal_Source a_source, ID_Type const& a_id) override
    {
      std::cout << "sak::Section_Interface_Imp::try_add" << " " << LI << "," << LS << std::endl;
      return false;
    }

    // Undoable remove object. Return true if the operation resulted in an undoable command. If this handle
    // is invalid or already in the data then nothing happens and returns false. Handle data is not deleted
    // until the last handle for it is deleted.
    bool try_remove(Signal_Source a_source, ID_Type const& a_id) override
    {
      std::cout << "sak::Section_Interface_Imp::try_remove" << " " << LI << "," << LS << std::endl;
      return false;
    }

    // Request that the editor for this file be opened or switched to.
    bool try_request_editor(Signal_Source a_source, ID_Type const& a_id) override
    {
      std::cout << "sak::Section_Interface_Imp::try_request_editor" << " " << LI << "," << LS << std::endl;
      return false;
    }

    // Request that the focus change to this object.
    bool try_request_outliner(Signal_Source a_source, ID_Type const& a_id) override
    {
      std::cout << "sak::Section_Interface_Imp::try_request_outliner" << " " << LI << "," << LS << std::endl;
      return false;
    }
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Section_Interface_Imp<List,LS,LS>
  //---------------------------------------------------------------------------
  // At the end of the list start building the member interfaces.
  template <std::size_t LS, typename...Args>
  class Section_Interface_Imp<flamingo::typelist<Args...>,LS,LS> :
      public Member_Interface_Imp<flamingo::typelist<Args...>>
  {
  public:
    // Special 6
    //============================================================
     ~Section_Interface_Imp() override = default;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Project_Interface_Imp<List,LS,LS>
  //---------------------------------------------------------------------------
  // The top interface implements everything that isn't section or member
  // dependent and supplies a means of accessing the section and member
  // interfaces.

  template <typename T, typename...Args>
  class Project_Interface_Imp :
      public Section_Interface_Imp<flamingo::typelist<T,Args...>>
  {
    using Inh = Section_Interface_Imp<flamingo::typelist<T,Args...>>;
    using Interface_Type = Abstract_Project_Interface_Imp<T,Args...>;
    using Signalbox_Type = typename Interface_Type::Signalbox_Type;
  public:
    // Typedefs
    //============================================================

    // Special 6
    //============================================================
    ~Project_Interface_Imp() override = default;

    // Virtuals
    //============================================================
    void save() const override
    {
      std::cout << "sak::Project_Interface_Imp::save" << std::endl;
    }

    void load() override
    {
      std::cout << "sak::Project_Interface_Imp::load" << std::endl;
    }

    // Data that is fixed on contruction.
    QString name() const override
    {
      std::cout << "sak::Project_Interface_Imp::name" << std::endl;
      return QString{};
    }

    QString location() const override
    {
      std::cout << "sak::Project_Interface_Imp::location" << std::endl;
      return QString{};
    }

    QString filepath() const override
    {
      std::cout << "sak::Project_Interface_Imp::filepath" << std::endl;
      return QString{};
    }

    // Can we currently call undo?
    bool can_undo() const override
    {
      std::cout << "sak::Project_Interface_Imp::can_undo" << std::endl;
      return false;
    }

    // Can we currently call redo?
    bool can_redo() const override
    {
      std::cout << "sak::Project_Interface_Imp::can_redo" << std::endl;
      return false;
    }

    // How many times can undo() be called?
    std::size_t undo_count() const  override
    {
      std::cout << "sak::Project_Interface_Imp::undo_count" << std::endl;
      return std::size_t{0};
    }

    // How many times can redo() be called?
    std::size_t redo_count() const override
    {
      std::cout << "sak::Project_Interface_Imp::redo_count" << std::endl;
      return std::size_t{0};
    }

    // Undo the last command issued.
    void undo() override
    {
      std::cout << "sak::Project_Interface_Imp::undo" << std::endl;
    }

    // Redo the last undone command in the command history
    void redo() override
    {
      std::cout << "sak::Project_Interface_Imp::redo" << std::endl;
    }

    // Clear the undo/redo history.
    void clear_history() override
    {
      std::cout << "sak::Project_Interface_Imp::clear_history" << std::endl;
    }

    // Does this name appear in the data?
    bool has_name(QString const&) const override
    {
      std::cout << "sak::Project_Interface_Imp::has_name" << std::endl;
      return false;
    }

    // Get all the objects names in data order
    std::vector<QString> get_all_names() const override
    {
      std::cout << "sak::Project_Interface_Imp::get_all_names" << std::endl;
      return std::vector<QString>{};
    }

    // Alter the supplied name so that it is unique among the existing data names
    void fix_name(QString&) const override
    {
      std::cout << "sak::Project_Interface_Imp::fix_name" << std::endl;
    }

    // Add an object that will rely on the Project's signals. If
    // nulltpr or already present, nothing happens.
    void add_signalbox(Signalbox_Type* a_signalbox) override
    {
      std::cout << "sak::Project_Interface_Imp::add_signalbox" << std::endl;
    }

    // Remove an object that will rely on the Project's signals. If
    // nulltpr or not present, nothing happens.
    void remove_signalbox(Signalbox_Type* a_signalbox) override
    {
      std::cout << "sak::Project_Interface_Imp::remove_signalbox" << std::endl;
    }

    // Clear all the signalboxes so that nothing relies on changes to this.
    void clear_signalboxes() override
    {
      std::cout << "sak::Project_Interface_Imp::clear_signalboxes" << std::endl;
    }

  };
  //------------------------------------------------------------------------------------------------------------------------------------------------------
}

namespace sak
{
  using API = Abstract_Project_Interface_Imp<File_Definition,Texture_Definition,Material_Definition>;
  using PI = Project_Interface_Imp<File_Definition,Texture_Definition,Material_Definition>;
  using ASB = API::Signalbox_Type;

  namespace
  {
    template <typename T>
    void do_test_section(API* a_api)
    {
      std::cout << "-------------------------" << std::endl;
      std::cout << "Typestring = \"" << T::Typestring_Type::data() << "\"" << std::endl;

      auto l_si = a_api->get_section<T>();
      l_si->is_empty(Tag<T>{});
      l_si->count(Tag<T>{});
      l_si->has(ID<T>{});
      l_si->has_name(Tag<T>{}, QString{});
      l_si->get_at(Tag<T>{}, std::size_t{});
      l_si->get_named(Tag<T>{}, QString{});
      l_si->get_ids(Tag<T>{});
      l_si->get_names(Tag<T>{});
      std::cout << "-------------------------" << std::endl;
    }
  }
}


void sak::testing::test_abstract_project_interface()
{
  std::cout << "Testing sak::Abstract_Project_Interface" << std::endl;
  std::cout << "==============================" << std::endl;

  using namespace sak;


  std::unique_ptr<API> l_api{ new PI{}};

  l_api->save();
  l_api->load();
  l_api->name();
  l_api->location();
  l_api->filepath();
  l_api->can_undo();
  l_api->can_redo();
  l_api->undo_count();
  l_api->redo_count();
  l_api->undo();
  l_api->redo();
  l_api->can_redo();
  l_api->clear_history();
  QString l_name{};
  l_api->has_name(l_name);
  l_api->get_all_names();
  l_api->fix_name(l_name);

  ASB* l_asb{nullptr};
  l_api->add_signalbox(l_asb);
  l_api->remove_signalbox(l_asb);
  l_api->clear_signalboxes();

  do_test_section<File_Definition>(l_api.get());
  do_test_section<Texture_Definition>(l_api.get());
  do_test_section<Material_Definition>(l_api.get());

  std::cout << "==============================" << std::endl;
}
