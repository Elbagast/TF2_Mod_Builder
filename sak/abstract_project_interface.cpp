#include "abstract_project_interface.hpp"

#include "project_data.hpp"
#include "command_history.hpp"
#include "section_data.hpp"
#include "tag.hpp"

#include <type_traits>

//---------------------------------------------------------------------------
// Abstract_Section_Member_Interface<T>
//---------------------------------------------------------------------------
template <std::size_t Index, typename T>
sak::v2::Abstract_Section_Member_Interface<Index,T>::~Abstract_Section_Member_Interface() = default;

//---------------------------------------------------------------------------
// Abstract_Chained_Member_Interface<T, Index, Last>
//---------------------------------------------------------------------------
template <typename T, std::size_t Index, std::size_t Last>
sak::v2::Abstract_Chained_Member_Interface<T,Index,Last>::~Abstract_Chained_Member_Interface() = default;

template <typename T, std::size_t Last>
sak::v2::Abstract_Chained_Member_Interface<T,Last,Last>::~Abstract_Chained_Member_Interface() = default;
//---------------------------------------------------------------------------
// Abstract_Section_Interface<T>
//---------------------------------------------------------------------------
template <typename T>
sak::v2::Abstract_Section_Interface<T>::~Abstract_Section_Interface() = default;

//---------------------------------------------------------------------------
// Abstract_Chained_Interface<Args...>
//---------------------------------------------------------------------------

// One type has all these functions.
template <typename T>
sak::v2::Abstract_Chained_Interface<T>::~Abstract_Chained_Interface() = default;

// For at least 2, we inherit one and use it's functions, then chain the next
// and expose its functions too.
template <typename T, typename R, typename...Args>
sak::v2::Abstract_Chained_Interface<T,R,Args...>::~Abstract_Chained_Interface() = default;

//---------------------------------------------------------------------------
// Abstract_Project_Common_Interface
//---------------------------------------------------------------------------
// The interface of the project that is not part of the sections.
//template <typename T, typename...Args>
//sak::v2::Abstract_Project_Common_Interface<T,Args...>::~Abstract_Project_Common_Interface() = default;

//---------------------------------------------------------------------------
// Abstract_Project_Save_Interface
//---------------------------------------------------------------------------
sak::v2::Abstract_Project_Save_Interface::~Abstract_Project_Save_Interface() = default;

//---------------------------------------------------------------------------
// Abstract_Project_Path_Interface
//---------------------------------------------------------------------------
sak::v2::Abstract_Project_Path_Interface::~Abstract_Project_Path_Interface() = default;

//---------------------------------------------------------------------------
// Abstract_Project_History_Interface
//---------------------------------------------------------------------------
sak::v2::Abstract_Project_History_Interface::~Abstract_Project_History_Interface() = default;


//---------------------------------------------------------------------------
// Abstract_Project_Signalbox_Interface
//---------------------------------------------------------------------------
template <typename T, typename...Args>
sak::v2::Abstract_Project_Signalbox_Interface<T,Args...>::~Abstract_Project_Signalbox_Interface() = default;


//---------------------------------------------------------------------------
// Abstract_Project_Chained_Interface<T,Args...>
//---------------------------------------------------------------------------
template <typename T, typename...Args>
sak::v2::Abstract_Project_Chained_Interface<T,Args...>::~Abstract_Project_Chained_Interface() = default;


// Forced Instantiations
//============================================================
template class sak::v2::Abstract_Project_Interface;

namespace sak
{
  namespace v2
  {
    //---------------------------------------------------------------------------
    // Project_Interface_Data<T,Args...>
    //---------------------------------------------------------------------------
    // Lowest level of implementation of the interface.
    template <typename T, typename...Args>
    class Project_Interface_Data :
        public Abstract_Project_Chained_Interface<T,Args...>
    {
    public:
      using Constructor_Arg = Project_Chained_Data<T,Args...>&&;

      explicit Project_Interface_Data(Constructor_Arg a_data);
      ~Project_Interface_Data() override;

      QString name() const override final;
      QString location() const override final;
      QString filepath() const override final;

      // Can we currently call undo?
      bool can_undo() const override final;
      // Can we currently call redo?
      bool can_redo() const override final;
      // How many times can undo() be called?
      std::size_t undo_count() const override final;
      // How many times can redo() be called?
      std::size_t redo_count() const override final;
      // Undo the last command issued.
      void undo() override final;
      // Redo the last undone command in the command history
      void redo() override final;
      // Clear the undo/redo history.
      void clear_history() override final;

      // Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
      void add_signalbox(Abstract_Chained_Signalbox<T,Args...>* a_signalbox) override final;
      // Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
      void remove_signalbox(Abstract_Chained_Signalbox<T,Args...>* a_signalbox) override final;
      // Clear all the signalboxes so that nothing relies on changes to this.
      void clear_signalboxes() override final;

    //protected:
      void set_data(Project_Chained_Data<T,Args...>&& a_data);
      void add_execute(std::unique_ptr<Abstract_Command>&& a_command);
      Project_Chained_Data<T,Args...>& data();
      Project_Chained_Data<T,Args...> const& cdata() const;
    private:
      Project_Chained_Data<T,Args...> m_data;
      Command_History m_history;
    };


    //---------------------------------------------------------------------------
    // Project_Interface_Impl<T_Base,T>
    //---------------------------------------------------------------------------
    // Implement this to implement the changes.

    template <typename T_Base, typename T>
    class Project_Interface_Impl
    {
    public:
      // Are there any objects in this Project?
      static bool is_empty(T_Base const*);
      static bool not_empty(T_Base const*);
      // How many objects are in this Project?
      static std::size_t count(T_Base const*);
      // Get the objects at this index
      static Handle<T> get_handle_at(T_Base const*, std::size_t a_index);
      // Get all the objects
      static std::vector<Handle<T>> get_all_handles(T_Base const*);
      // Get all the object names
      static std::vector<QString> get_all_names(T_Base const*);
      // Make a new object using the default parameters. Project's data management system owns it
      // but it is not part of the Project. Does not trigger any commands.
      static Handle<T> make_default(T_Base*);
      // Make a new object using the supplied data. Project's data management system owns it but
      // it is not part of the Project. Does not trigger any commands.
      static Handle<T> make_emplace(T_Base*, T&& a_data);
      // Undoable add a new object made using the default parameters. The name will be modified if it is
      // currently in use by another object.
      static void add_default(T_Base*);
      // Undoable add a new object using the supplied data. This data is assigned a new handle. The name will
      // be modified if it is currently in use by another object.
      static void add_emplace(T_Base*, T&& a_data);
      // Undoable add a new object using the supplied handle. The name will be modified if it is currently in
      // use by another object. If this handle is invalid or already in the data then nothing happens.
      static void add(T_Base*, Handle<T> const& a_handle);
      // Undoable remove object. If this handle is invalid or not in the data nothing happens.
      // Data is not deleted until the last reference is deleted.
      static void remove(T_Base*, Handle<T> const& a_handle);
      // Request that the editor for this file be opened or switched to.
      static void request_editor(T_Base*, Handle<T> const& a_handle);
      // Request that the focus change to this object.
      static void request_focus(T_Base*, Handle<T> const& a_handle);

      template <std::size_t Index>
      static bool change_at(T_Base*,
                            Handle<T> const& a_handle,
                            Section_Data_Member_Value_Type<Index,T> const& a_value
                           );
    };




    // Build the inheritance chain

    template <typename T_Base, std::size_t I, std::size_t End, typename T, typename...Args>
    class Project_Chained_Interface;

    // End of last one inherits the base
    template <typename T_Base, std::size_t End, typename T>
    class Project_Chained_Interface<T_Base,End,End,T> :
        public T_Base
    {
      using Inh = T_Base;
    public:
      using Constructor_Arg = typename Inh::Constructor_Arg;

      explicit Project_Chained_Interface(Constructor_Arg a_data):
        Inh(std::move(a_data))
      {}
      ~Project_Chained_Interface() override = default;

      // Are there any objects in this Project?
      bool is_empty(Tag<T>&&) const override final
      {
        return Project_Interface_Impl<T_Base,T>::is_empty(this);
      }

      bool not_empty(Tag<T>&&) const override final
      {
        return Project_Interface_Impl<T_Base,T>::not_empty(this);
      }

      // How many objects are in this Project?
      std::size_t count(Tag<T>&&) const override final
      {
        return Project_Interface_Impl<T_Base,T>::count(this);
      }

      // Get the objects at this index
      Handle<T> get_handle_at(Tag<T>&&, std::size_t a_index) const override final
      {
        return Project_Interface_Impl<T_Base,T>::get_handle_at(this,a_index);
      }

      // Get all the objects
      std::vector<Handle<T>> get_all_handles(Tag<T>&&) const override final
      {
        return Project_Interface_Impl<T_Base,T>::get_all_handles(this);
      }

      // Get all the object names
      std::vector<QString> get_all_names(Tag<T>&&) const override final
      {
        return Project_Interface_Impl<T_Base,T>::get_all_names(this);
      }

      // Make a new object using the default parameters. Project's data management system owns it
      // but it is not part of the Project. Does not trigger any commands.
      Handle<T> make_default(Tag<T>&&) override final
      {
        return Project_Interface_Impl<T_Base,T>::make_default(this);
      }

      // Make a new object using the supplied data. Project's data management system owns it but
      // it is not part of the Project. Does not trigger any commands.
      Handle<T> make_emplace(T&& a_data) override final
      {
        return Project_Interface_Impl<T_Base,T>::make_emplace(this,std::move(a_data));
      }

      // Undoable add a new object made using the default parameters. The name will be modified if it is
      // currently in use by another object.
      void add_default(Tag<T>&&) override final
      {
        return Project_Interface_Impl<T_Base,T>::add_default(this);
      }

      // Undoable add a new object using the supplied data. This data is assigned a new handle. The name will
      // be modified if it is currently in use by another object.
      void add_emplace(T&& a_data) override final
      {
        return Project_Interface_Impl<T_Base,T>::add_emplace(this,std::move(a_data));
      }

      // Undoable add a new object using the supplied handle. The name will be modified if it is currently in
      // use by another object. If this handle is invalid or already in the data then nothing happens.
      void add(Handle<T> const& a_handle) override final
      {
        return Project_Interface_Impl<T_Base,T>::add(this,a_handle);
      }

      // Undoable remove object. If this handle is invalid or not in the data nothing happens.
      // Data is not deleted until the last reference is deleted.
      void remove(Handle<T> const& a_handle) override final
      {
        return Project_Interface_Impl<T_Base,T>::remove(this,a_handle);
      }

      // Request that the editor for this file be opened or switched to.
      void request_editor(Handle<T> const& a_handle) override final
      {
        return Project_Interface_Impl<T_Base,T>::request_editor(this,a_handle);
      }

      // Request that the focus change to this object.
      void request_focus(Handle<T> const& a_handle) override final
      {
        return Project_Interface_Impl<T_Base,T>::request_focus(this,a_handle);
      }
    };

    // End of one in the middle starts work on the next
    template <typename T_Base, std::size_t End, typename T, typename R, typename...Args>
    class Project_Chained_Interface<T_Base,End,End,T,R,Args...> :
        public Project_Chained_Interface<T_Base,0,Section_Data_Size_v<R>,R,Args...>
    {
      using Inh = Project_Chained_Interface<T_Base,0,Section_Data_Size_v<R>,R,Args...>;
    public:
      using Constructor_Arg = typename Inh::Constructor_Arg;

      explicit Project_Chained_Interface(Constructor_Arg a_data):
        Inh(std::move(a_data))
      {}
      ~Project_Chained_Interface() override = default;

      // Are there any objects in this Project?
      bool is_empty(Tag<T>&&) const override final
      {
        return Project_Interface_Impl<T_Base,T>::is_empty(this);
      }

      bool not_empty(Tag<T>&&) const override final
      {
        return Project_Interface_Impl<T_Base,T>::not_empty(this);
      }

      // How many objects are in this Project?
      std::size_t count(Tag<T>&&) const override final
      {
        return Project_Interface_Impl<T_Base,T>::count(this);
      }

      // Get the objects at this index
      Handle<T> get_handle_at(Tag<T>&&, std::size_t a_index) const override final
      {
        return Project_Interface_Impl<T_Base,T>::get_handle_at(this,a_index);
      }

      // Get all the objects
      std::vector<Handle<T>> get_all_handles(Tag<T>&&) const override final
      {
        return Project_Interface_Impl<T_Base,T>::get_all_handles(this);
      }

      // Get all the object names
      std::vector<QString> get_all_names(Tag<T>&&) const override final
      {
        return Project_Interface_Impl<T_Base,T>::get_all_names(this);
      }

      // Make a new object using the default parameters. Project's data management system owns it
      // but it is not part of the Project. Does not trigger any commands.
      Handle<T> make_default(Tag<T>&&) override final
      {
        return Project_Interface_Impl<T_Base,T>::make_default(this);
      }

      // Make a new object using the supplied data. Project's data management system owns it but
      // it is not part of the Project. Does not trigger any commands.
      Handle<T> make_emplace(T&& a_data) override final
      {
        return Project_Interface_Impl<T_Base,T>::make_emplace(this,std::move(a_data));
      }

      // Undoable add a new object made using the default parameters. The name will be modified if it is
      // currently in use by another object.
      void add_default(Tag<T>&&) override final
      {
        return Project_Interface_Impl<T_Base,T>::add_default(this);
      }

      // Undoable add a new object using the supplied data. This data is assigned a new handle. The name will
      // be modified if it is currently in use by another object.
      void add_emplace(T&& a_data) override final
      {
        return Project_Interface_Impl<T_Base,T>::add_emplace(this,std::move(a_data));
      }

      // Undoable add a new object using the supplied handle. The name will be modified if it is currently in
      // use by another object. If this handle is invalid or already in the data then nothing happens.
      void add(Handle<T> const& a_handle) override final
      {
        return Project_Interface_Impl<T_Base,T>::add(this,a_handle);
      }

      // Undoable remove object. If this handle is invalid or not in the data nothing happens.
      // Data is not deleted until the last reference is deleted.
      void remove(Handle<T> const& a_handle) override final
      {
        return Project_Interface_Impl<T_Base,T>::remove(this,a_handle);
      }

      // Request that the editor for this file be opened or switched to.
      void request_editor(Handle<T> const& a_handle) override final
      {
        return Project_Interface_Impl<T_Base,T>::request_editor(this,a_handle);
      }

      // Request that the focus change to this object.
      void request_focus(Handle<T> const& a_handle) override final
      {
        return Project_Interface_Impl<T_Base,T>::request_focus(this,a_handle);
      }
    };

    // Any other adds implements the member
    template <typename T_Base, std::size_t Index, std::size_t End, typename T, typename...Args>
    class Project_Chained_Interface<T_Base,Index,End,T,Args...> :
        public Project_Chained_Interface<T_Base,Index+1,End,T,Args...>
    {
      using Inh = Project_Chained_Interface<T_Base,Index+1,End,T,Args...>;
    public:
      using Constructor_Arg = typename Inh::Constructor_Arg;

      // Special 6
      //============================================================
      explicit Project_Chained_Interface(Constructor_Arg a_data):
        Inh(std::move(a_data))
      {}
      ~Project_Chained_Interface() override = default;

      // Virtuals
      //============================================================

      // Undoable change an object's member value. Returns true if this call results in a change being made.
      // Does nothing and returns false if this handle is invalid or not in the data, or if the supplied value
      // doesn't result in data being changed.
      bool change_at( Index_Tag<Index>&&,
                      Handle<T> const& a_handle,
                      Section_Data_Member_Value_Type<Index,T> const& a_value
                     ) override final
      {
        return Project_Interface_Impl<T_Base,T>::change_at<Index>(this, a_handle, a_value);
      }
    };

    //---------------------------------------------------------------------------
    // Project_Final_Interface<t,Args...>
    //---------------------------------------------------------------------------
    // final object.
    template <typename T, typename...Args>
    class Project_Final_Interface :
        public Project_Chained_Interface<Project_Interface_Data<T,Args...>,0,Section_Data_Size_v<T>,T,Args...>
    {
      using Inh = Project_Chained_Interface<Project_Interface_Data<T,Args...>,0,Section_Data_Size_v<T>,T,Args...>;
    public:
      using Constructor_Arg = typename Inh::Constructor_Arg;

      Project_Final_Interface(Constructor_Arg a_data):
        Inh(std::move(a_data))
      {
      }
      ~Project_Final_Interface() override = default;


      void save() const override final  {}
      void load() override final        {}
    };


    using Project_Interface = Project_Final_Interface<File_Data,Texture_Data>;

  } // namespace v2
} // namespace sak

//---------------------------------------------------------------------------
// Project_Interface_Data<T,Args...>
//---------------------------------------------------------------------------
// Lowest level of implementation of the interface.
template <typename T, typename...Args>
sak::v2::Project_Interface_Data<T,Args...>::Project_Interface_Data(Constructor_Arg a_data):
  m_data{std::move(a_data)},
  m_history{}
{}

template <typename T, typename...Args>
sak::v2::Project_Interface_Data<T,Args...>::~Project_Interface_Data() = default;

template <typename T, typename...Args>
QString sak::v2::Project_Interface_Data<T,Args...>::name() const
{
  return m_data.name();
}

template <typename T, typename...Args>
QString sak::v2::Project_Interface_Data<T,Args...>::location() const
{
  return m_data.location();
}

template <typename T, typename...Args>
QString sak::v2::Project_Interface_Data<T,Args...>::filepath() const
{
  return m_data.filepath();
}


// Can we currently call undo?
template <typename T, typename...Args>
bool sak::v2::Project_Interface_Data<T,Args...>::can_undo() const
{
  return m_history.can_undo();
}

// Can we currently call redo?
template <typename T, typename...Args>
bool sak::v2::Project_Interface_Data<T,Args...>::can_redo() const
{
  return m_history.can_redo();
}

// How many times can undo() be called?
template <typename T, typename...Args>
std::size_t sak::v2::Project_Interface_Data<T,Args...>::undo_count() const
{
  return m_history.undo_count();
}

// How many times can redo() be called?
template <typename T, typename...Args>
std::size_t sak::v2::Project_Interface_Data<T,Args...>::redo_count() const
{
  return m_history.redo_count();
}

// Undo the last command issued.
template <typename T, typename...Args>
void sak::v2::Project_Interface_Data<T,Args...>::undo()
{
  m_history.undo();
}

// Redo the last undone command in the command history
template <typename T, typename...Args>
void sak::v2::Project_Interface_Data<T,Args...>::redo()
{
  m_history.redo();
}

// Clear the undo/redo history.
template <typename T, typename...Args>
void sak::v2::Project_Interface_Data<T,Args...>::clear_history()
{
  m_history.clear();
}

// Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
template <typename T, typename...Args>
void sak::v2::Project_Interface_Data<T,Args...>::add_signalbox(Abstract_Chained_Signalbox<T,Args...>* a_signalbox)
{
  m_data.add_signalbox(a_signalbox);
}

// Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
template <typename T, typename...Args>
void sak::v2::Project_Interface_Data<T,Args...>::remove_signalbox(Abstract_Chained_Signalbox<T,Args...>* a_signalbox)
{
  m_data.remove_signalbox(a_signalbox);
}

// Clear all the signalboxes so that nothing relies on changes to this.
template <typename T, typename...Args>
void sak::v2::Project_Interface_Data<T,Args...>::clear_signalboxes()
{
  m_data.clear_signalboxes();
}

template <typename T, typename...Args>
void sak::v2::Project_Interface_Data<T,Args...>::set_data(Project_Chained_Data<T,Args...>&& a_data)
{
  m_data = std::move(a_data);
}

template <typename T, typename...Args>
void sak::v2::Project_Interface_Data<T,Args...>::add_execute(std::unique_ptr<Abstract_Command>&& a_command)
{
  m_history.add_execute(std::move(a_command));
}

template <typename T, typename...Args>
sak::v2::Project_Chained_Data<T,Args...>& sak::v2::Project_Interface_Data<T,Args...>::data()
{
  return m_data;
}

template <typename T, typename...Args>
sak::v2::Project_Chained_Data<T,Args...> const& sak::v2::Project_Interface_Data<T,Args...>::cdata() const
{
  return m_data;
}


//---------------------------------------------------------------------------
// Project_Interface_Impl<T_Base,T>
//---------------------------------------------------------------------------
template <typename B,typename T>
bool sak::v2::Project_Interface_Impl<B,T>::is_empty(B const* a_base)
{
  return a_base->cdata().empty(Tag<T>());
}

template <typename B,typename T>
bool sak::v2::Project_Interface_Impl<B,T>::not_empty(B const* a_base)
{
  return !is_empty(a_base);
}
// How many objects are in this Project?
template <typename B,typename T>
std::size_t sak::v2::Project_Interface_Impl<B,T>::count(B const* a_base)
{
  return a_base->cdata().count(Tag<T>());
}
// Get the objects at this index
template <typename B,typename T>
sak::Handle<T> sak::v2::Project_Interface_Impl<B,T>::get_handle_at(B const* a_base, std::size_t a_index)
{
  return a_base->cdata().get_handle_at(Tag<T>(), a_index);
}
// Get all the objects
template <typename B,typename T>
std::vector<sak::Handle<T>> sak::v2::Project_Interface_Impl<B,T>::get_all_handles(B const* a_base)
{
  return a_base->cdata().get_all_handles(Tag<T>());
}
// Get all the object names
template <typename B,typename T>
std::vector<QString> sak::v2::Project_Interface_Impl<B,T>::get_all_names(B const* a_base)
{
  return a_base->cdata().get_all_names(Tag<T>());
}
// Make a new object using the default parameters. Project's data management system owns it
// but it is not part of the Project. Does not trigger any commands.
template <typename B,typename T>
sak::Handle<T> sak::v2::Project_Interface_Impl<B,T>::make_default(B* a_base)
{
  return a_base->data().make_default(Tag<T>());
}
// Make a new object using the supplied data. Project's data management system owns it but
// it is not part of the Project. Does not trigger any commands.
template <typename B,typename T>
sak::Handle<T> sak::v2::Project_Interface_Impl<B,T>::make_emplace(B* a_base, T&& a_data)
{
  return a_base->data().make_emplace(std::move(a_data));
}
// Undoable add a new object made using the default parameters. The name will be modified if it is
// currently in use by another object.
template <typename B,typename T>
void sak::v2::Project_Interface_Impl<B,T>::add_default(B* a_base)
{

}
// Undoable add a new object using the supplied data. This data is assigned a new handle. The name will
// be modified if it is currently in use by another object.
template <typename B,typename T>
void sak::v2::Project_Interface_Impl<B,T>::add_emplace(B* a_base, T&& a_data)
{
  //COMMAND GOES HERE
}
// Undoable add a new object using the supplied handle. The name will be modified if it is currently in
// use by another object. If this handle is invalid or already in the data then nothing happens.
template <typename B,typename T>
void sak::v2::Project_Interface_Impl<B,T>::add(B* a_base, Handle<T> const& a_handle)
{
  //COMMAND GOES HERE
}
// Undoable remove object. If this handle is invalid or not in the data nothing happens.
// Data is not deleted until the last reference is deleted.
template <typename B,typename T>
void sak::v2::Project_Interface_Impl<B,T>::remove(B* a_base, Handle<T> const& a_handle)
{
  //COMMAND GOES HERE
}
// Request that the editor for this file be opened or switched to.
template <typename B,typename T>
void sak::v2::Project_Interface_Impl<B,T>::request_editor(B* a_base, Handle<T> const& a_handle)
{
  if (not_null(a_handle) && a_base->cdata().has_handle(a_handle))
  {
    a_base->request_editor(a_handle);
  }
}
// Request that the focus change to this object.
template <typename B,typename T>
void sak::v2::Project_Interface_Impl<B,T>::request_focus(B* a_base, Handle<T> const& a_handle)
{
  if (not_null(a_handle) && a_base->cdata().has_handle(a_handle))
  {
    a_base->request_focus(a_handle);
  }
}

template <typename B,typename T>
template <std::size_t Index>
bool sak::v2::Project_Interface_Impl<B,T>::change_at(B* a_base, Handle<T> const& a_handle, Section_Data_Member_Value_Type<Index,T> const& a_value)
{
  //COMMAND GOES HERE
  return false;
}


std::unique_ptr<sak::v2::Abstract_Project_Interface> sak::v2::make_project_interface(Project_Data&& a_data)
{
  //return std::unique_ptr<Abstract_Project_Interface>(nullptr);
  return std::make_unique<Project_Interface>(std::move(a_data));
}
