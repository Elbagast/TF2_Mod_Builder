#ifndef SAK_PROJECT_DATA_HPP
#define SAK_PROJECT_DATA_HPP

#ifndef SAK_PROJECT_DATA_FWD_HPP
#include "project_data_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_PROJECT_SIGNALBOX_FWD_HPP
#include "abstract_project_signalbox_fwd.hpp"
#endif

#ifndef SAK_SECTION_DATA_MANAGER_FWD_HPP
#include "section_data_manager_fwd.hpp"
#endif

#ifndef SAK_SECTION_INTERFACE_FWD_HPP
#include "section_interface_fwd.hpp"
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

#ifndef INCLUDE_STD_VECTOR
#define INCLUDE_STD_VECTOR
#include <vector>
#endif

#include "handle.hpp"

//#include "abstract_project_interface.hpp"

class QString;

#include <QString>
#include <QFileInfo>
//#include "command_history.hpp"
#include "handle_factory.hpp"

#include "abstract_project_signalbox.hpp"

#ifndef SAK_TAG_FWD_HPP
#include "tag_fwd.hpp"
#endif


namespace sak
{
  //---------------------------------------------------------------------------
  // Project_Data
  //---------------------------------------------------------------------------

  class Project_Data
  {
  public:
    // Special 6
    //============================================================
    // Construct the project using the supplied filename. If the directory
    // does not exist or is inaccessible it will fail. If the file does
    // not exist it will attempt to create it and save the initial data
    // to it. If the file exists it will attempt to load the data from it.
    explicit Project_Data(QString const& a_filepath);
    ~Project_Data();

    Project_Data(Project_Data const&) = delete;
    Project_Data& operator=(Project_Data const&) = delete;

    Project_Data(Project_Data &&);
    Project_Data& operator=(Project_Data &&);

    // Interface
    //============================================================
    QString name() const;
    QString location() const;
    QString filepath() const;

    // Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
    void add_signalbox(Abstract_Project_Signalbox* a_signalbox);

    // Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
    void remove_signalbox(Abstract_Project_Signalbox* a_signalbox);

    // Clear all the signalboxes so that nothing relies on changes to this.
    void clear_signalboxes();
    
    // Section data managers
    template <typename T>
    Section_Data_Manager<T>* get_manager();

    File_Data_Manager* get_file_manager();
    Texture_Data_Manager* get_texture_manager();

    // Section data managers
    template <typename T>
    Section_Data_Manager<T> const* cget_manager() const;

    File_Data_Manager const* cget_file_manager() const;
    Texture_Data_Manager const* cget_texture_manager() const;

  private:
    // Pimpl Data
    //============================================================
    class Implementation;
    std::unique_ptr<Implementation> m_data;

    Implementation& imp()                { return *m_data; }
    Implementation const& cimp() const   { return *m_data; }
  };

}

//------------------------------------------------------------------------------------------------------------------------------------------------------
namespace sak
{
  namespace v2
  {
    namespace internal
    {
      // build Project_Data in a way that results in the full interface in the top class.

      //---------------------------------------------------------------------------
      // Project_Base_Data
      //---------------------------------------------------------------------------
      // The bit that is detached from everything else.

      class Project_Base_Data
      {
      public:
        // Special 6
        //============================================================
        explicit Project_Base_Data(QString const& a_filepath);
        ~Project_Base_Data();

        // Interface
        //============================================================
        QString name() const;
        QString location() const;
        QString filepath() const;

      private:
        QFileInfo m_filepath;
      };

      //---------------------------------------------------------------------------
      // Project_Signalbox_Imp<T,Args...>
      //---------------------------------------------------------------------------
      // Implement the things that are not section dependent and will be used by
      // other parts of the implementation.
      template <typename T, typename...Args>
      class Project_Signalbox_Imp
      {
      public:
        // Special 6
        //============================================================
        Project_Signalbox_Imp();
        ~Project_Signalbox_Imp();

        // Virtuals
        //============================================================
        // Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
        void add_signalbox(v2::Abstract_Chained_Signalbox<T,Args...>* a_signalbox);
        // Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
        void remove_signalbox(v2::Abstract_Chained_Signalbox<T,Args...>* a_signalbox);
        // Clear all the signalboxes so that nothing relies on changes to this.
        void clear_signalboxes();

      protected:
        // Internal Interface
        //============================================================
        std::vector<v2::Abstract_Chained_Signalbox<T,Args...>*>& get_signalboxes();
        std::vector<v2::Abstract_Chained_Signalbox<T,Args...>*> const& cget_signalboxes() const;

      private:
        // Data Members
        //============================================================
        std::vector<v2::Abstract_Chained_Signalbox<T,Args...>*> m_signalboxes;
      };

      //---------------------------------------------------------------------------
      // Project_Chained_Signalbox_Imp<ASBD,Args...>
      //---------------------------------------------------------------------------
      // Create a class that allows triggering the signals

      template <typename T_Base, typename T, typename...Args>
      class Project_Chained_Signalbox_Imp;

      // For one type, implement the change.
      template <typename T_Base, typename T>
      class Project_Chained_Signalbox_Imp<T_Base, T> :
          protected virtual T_Base
      {
      public:
        Project_Chained_Signalbox_Imp();
        ~Project_Chained_Signalbox_Imp();

        // calls each of these on all the stored signalboxes.

        // When a handle has its data changed, this is called.
        void changed(Handle<T> const& a_handle);
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

        using T_Base::add_signalbox;
        using T_Base::remove_signalbox;
        using T_Base::clear_signalboxes;
      };

      // For at least 2 types, inherit the 1 type implementor and chain.
      // T_Base will be virtually inherited
      template <typename T_Base, typename T, typename R, typename...Args>
      class Project_Chained_Signalbox_Imp<T_Base, T,R,Args...> :
          protected Project_Chained_Signalbox_Imp<T_Base,T>,
          protected Project_Chained_Signalbox_Imp<T_Base,R,Args...>
      {
        using Inh1 = Project_Chained_Signalbox_Imp<T_Base,T>;
        using Inh2 = Project_Chained_Signalbox_Imp<T_Base,R,Args...>;

      public:
        Project_Chained_Signalbox_Imp() = default;
        ~Project_Chained_Signalbox_Imp() = default;

        using Inh1::changed;
        using Inh1::changed_at;
        using Inh1::added;
        using Inh1::removed;
        using Inh1::requests_editor;
        using Inh1::requests_focus;

        using Inh2::changed;
        using Inh2::changed_at;
        using Inh2::added;
        using Inh2::removed;
        using Inh2::requests_editor;
        using Inh2::requests_focus;

        using T_Base::add_signalbox;
        using T_Base::remove_signalbox;
        using T_Base::clear_signalboxes;
      };

      //---------------------------------------------------------------------------
      // Project_Signalbox_Data<T,Args...>
      //---------------------------------------------------------------------------
      // Implements the project signalbox interface and an interface for emiting
      // those signals.

      template <typename T, typename... Args>
      class Project_Signalbox_Data :
          protected Project_Chained_Signalbox_Imp<Project_Signalbox_Imp<T,Args...>,T,Args...>
      {
        using Inh = Project_Chained_Signalbox_Imp<Project_Signalbox_Imp<T,Args...>,T,Args...>;
      public:
        // Special 6
        //============================================================
        Project_Signalbox_Data() = default;
        ~Project_Signalbox_Data() = default;

        using Inh::add_signalbox;
        using Inh::remove_signalbox;
        using Inh::clear_signalboxes;

        // Each of these will be overloaded for as many template args there are.
        using Inh::changed;
        using Inh::changed_at;
        using Inh::added;
        using Inh::removed;
        using Inh::requests_editor;
        using Inh::requests_focus;
      };

      //---------------------------------------------------------------------------
      // Project_Section_Data_Imp<T>
      //---------------------------------------------------------------------------
      // the bit that manages data for a given type. No signals emitted.

      template <typename T>
      class Project_Section_Data_Imp
      {
      public:
        // Special 6
        //============================================================
        Project_Section_Data_Imp();
        ~Project_Section_Data_Imp();

        // Public Interface
        //============================================================
        // Are there any handles of this type in the currently active project data?
        bool empty(Tag<T>&&) const;

        // How handles of this type in the currently active project data?
        std::size_t count(Tag<T>&&) const;

        // Is this handle in the currently active project data?
        bool has_handle(Handle<T> const& a_handle) const;

        // Get the handle at this index. Handles are sorted alphabetically by the name
        // member of the objects they reference.
        Handle<T> get_handle_at(Tag<T>&&, std::size_t a_index) const;

        // Get all the handles alphabetically sorted by name
        std::vector<Handle<T>> get_all_handles(Tag<T>&&) const;

        // Get all the objects' alphabetically sorted names
        std::vector<QString> get_all_names(Tag<T>&&) const;

        // You may create new objects using these two functions. Objects created in this way
        // are part of the data management system but nothing outside of it has been notified
        // of their presense. Calling has_handle on the handle returned by these functions
        // immediately after will return false.

        // Make a new object using the supplied data. Project's data management system owns it but
        // it is not part of the Project.
        Handle<T> make_emplace(T&& a_object);

        // Make a new file using the default parameters. Project's data management system owns it
        // but it is not part of the Project.
        Handle<T> make_default(Tag<T>&&);

      private:
        // Data Members
        //============================================================
        Handle_Factory<T> m_factory;
        std::vector<Handle<T>> m_handles;
      };

      //---------------------------------------------------------------------------
      // Project_Section_Data<Args...>
      //---------------------------------------------------------------------------
      template <typename T, typename...Args>
      class Project_Section_Data;

      // For one use the implementation
      template <typename T>
      class Project_Section_Data<T> :
          protected Project_Section_Data_Imp<T>
      {
        using Inh = Project_Section_Data_Imp<T>;
      public:
        // Special 6
        //============================================================
        Project_Section_Data() = default;
        virtual ~Project_Section_Data() = default;

        // Public Interface
        //============================================================
        using Inh::empty;
        using Inh::count;
        using Inh::has_handle;
        using Inh::get_handle_at;
        using Inh::get_all_handles;
        using Inh::get_all_names;
        using Inh::make_emplace;
        using Inh::make_default;
      };

      // For two or more chain them
      template <typename T, typename R, typename...Args>
      class Project_Section_Data<T,R,Args...> :
          protected Project_Section_Data<T>,
          protected Project_Section_Data<R,Args...>
      {
        using Inh1 = Project_Section_Data<T>;
        using Inh2 = Project_Section_Data<R,Args...>;
      public:
        // Special 6
        //============================================================
        Project_Section_Data() = default;
        ~Project_Section_Data() = default;

        // Public Interface
        //============================================================
        using Inh1::empty;
        using Inh1::count;
        using Inh1::has_handle;
        using Inh1::get_handle_at;
        using Inh1::get_all_handles;
        using Inh1::get_all_names;
        using Inh1::make_emplace;
        using Inh1::make_default;

        using Inh2::empty;
        using Inh2::count;
        using Inh2::has_handle;
        using Inh2::get_handle_at;
        using Inh2::get_all_handles;
        using Inh2::get_all_names;
        using Inh2::make_emplace;
        using Inh2::make_default;
      };

    }


    //---------------------------------------------------------------------------
    // Project_Chained_Data<T,Args...>
    //---------------------------------------------------------------------------
    template <typename T, typename...Args>
    class Project_Chained_Data :
        protected internal::Project_Base_Data,
        protected internal::Project_Signalbox_Data<T,Args...>,
        protected internal::Project_Section_Data<T,Args...>
    {
      using Inh1 = internal::Project_Base_Data;
      using Inh2 = internal::Project_Signalbox_Data<T,Args...>;
      using Inh3 = internal::Project_Section_Data<T,Args...>;
    public:
      // Special 6
      //============================================================
      explicit Project_Chained_Data(QString const& a_filepath);
      ~Project_Chained_Data();

      using Inh1::name;
      using Inh1::location;
      using Inh1::filepath;

      using Inh2::add_signalbox;
      using Inh2::remove_signalbox;
      using Inh2::clear_signalboxes;

      // Each of these will be overloaded for as many template args there are.
      using Inh2::changed;
      using Inh2::changed_at;
      using Inh2::added;
      using Inh2::removed;
      using Inh2::requests_editor;
      using Inh2::requests_focus;

      using Inh3::empty;
      using Inh3::count;
      using Inh3::has_handle;
      using Inh3::get_handle_at;
      using Inh3::get_all_handles;
      using Inh3::get_all_names;
      using Inh3::make_emplace;
      using Inh3::make_default;
    };

  }
}


#endif // SAK_PROJECT_DATA_HPP
