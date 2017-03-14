#ifndef SAK_SHARED_DATA_MANAGER_HPP
#define SAK_SHARED_DATA_MANAGER_HPP

#include "fwd/data_manager.hpp"
#include "manager.hpp"
#include <sak/project/fwd/object.hpp>

#include "signalbox.hpp"
#include <vector>
#include <QString>
class QXmlStreamWriter;
class QXmlStreamReader;

namespace sak
{
  namespace shared
  {
    //---------------------------------------------------------------------------
    // sak::shared::data_manager<T>
    //---------------------------------------------------------------------------
    // Splitting out the repeated backend management system for project.

    template <typename T>
    class data_manager :
        public abstract::signalbox<T>
    {
    public:
      // Typedefs
      //============================================================
      using inherited_type = abstract::signalbox<T>;
      using object_type = T;
      using manager_type = manager<object_type>;
      using handle_type = handle<object_type>;

      // Special 6
      //============================================================
      explicit data_manager(project::object& a_project);
      ~data_manager() override;

      // Virtuals
      //============================================================
      void changed(handle_type const& a_handle) override final;
      // When a File has its data changed in a specific place, this is called.
      void changed_at(handle_type const& a_handle, std::size_t a_section) override final;
      // When a File has been added, this is called.
      void added(handle_type const& a_handle) override final;
      // When a File has been removed, this is called.
      void removed(handle_type const& a_handle) override final;
      // When a File requests an editor, this is called.
      void requests_editor(handle_type const& a_handle) override final;

      // When a File requests an editor, this is called.
      void requests_focus(handle_type const& a_handle) override final;

      // Public Interface
      //============================================================
      // Are there any Files in this Project?
      bool empty() const;

      // How many any Files are in this Project?
      std::size_t count() const;

      bool has_handle(handle_type const& a_handle) const;

      // Get the file at this index, asssuming the Files are alphabetically sorted by name
      handle_type get_at(std::size_t a_index) const;

      // Get all the Files alphabetically sorted by name
      std::vector<handle_type> get_all() const;

      // Get all the Files alphabetically sorted names
      std::vector<QString> get_all_names() const;

      // You may create new Files using these two functions. Files created in this way
      // are part of the Project's data management system but have not yet been added to the
      // Project properly. That will only happen when the Project recieves a signal via its
      // Project_Signalbox that it should be addeed.

      // Make a new file using the supplied data. Project's data management system owns it but
      // it is not part of the Proeject.
      handle_type make_emplace(object_type&& a_object);

      // Make a new file using the default parameters. Project's data management system owns it
      // but it is not part of the Project.
      handle_type make();

      void to_xmlstream(QXmlStreamWriter& a_stream) const;

      void from_xmlstream(QXmlStreamReader& a_stream);

    private:
      // Data Members
      //============================================================
      project::object& m_project;
      manager_type m_manager;
      std::vector<handle_type> m_handles;
    };
  }
}


#endif // DATA_MANAGER_H
