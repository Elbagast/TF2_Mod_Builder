#ifndef SAK_SHARED_DATA_MANAGER_HPP
#define SAK_SHARED_DATA_MANAGER_HPP

#include "fwd/data_manager.hpp"
#include "extended_manager.hpp"
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
        public shared::abstract::signalbox<T>
    {
    public:
      // Typedefs
      //============================================================
      using inherited_type = shared::abstract::signalbox<T>;
      using object_type = T;
      using extended_manager_type = shared::extended_manager<object_type>;
      using extended_handle_type = shared::extended_handle<object_type>;
      using interface_traits_type = typename extended_manager_type::interface_traits_type;

      // Special 6
      //============================================================
      explicit data_manager(project::object& a_project);
      ~data_manager() override;

      // Virtuals
      //============================================================
      void changed(extended_handle_type const& a_ehandle) override final;
      // When a File has its data changed in a specific place, this is called.
      void changed_at(extended_handle_type const& a_ehandle, std::size_t a_section) override final;
      // When a File has been added, this is called.
      void added(extended_handle_type const& a_ehandle) override final;
      // When a File has been removed, this is called.
      void removed(extended_handle_type const& a_ehandle) override final;
      // When a File requests an editor, this is called.
      void requests_editor(extended_handle_type const& a_ehandle) override final;

      // When a File requests an editor, this is called.
      void requests_focus(extended_handle_type const& a_ehandle) override final;

      // Public Interface
      //============================================================
      // Are there any Files in this Project?
      bool empty() const;

      // How many any Files are in this Project?
      std::size_t count() const;

      bool has_handle(extended_handle_type const& a_ehandle) const;

      // Get the file at this index, asssuming the Files are alphabetically sorted by name
      extended_handle_type get_at(std::size_t a_index) const;

      // Get all the Files alphabetically sorted by name
      std::vector<extended_handle_type> get_all() const;

      // Get all the Files alphabetically sorted names
      std::vector<QString> get_all_names() const;

      // You may create new Files using these two functions. Files created in this way
      // are part of the Project's data management system but have not yet been added to the
      // Project properly. That will only happen when the Project recieves a signal via its
      // Project_Signalbox that it should be addeed.

      // Make a new file using the supplied data. Project's data management system owns it but
      // it is not part of the Proeject.
      extended_handle_type make_emplace(object_type&& a_object);

      // Make a new file using the default parameters. Project's data management system owns it
      // but it is not part of the Project.
      extended_handle_type make();

      void to_xmlstream(QXmlStreamWriter& a_stream) const;

      void from_xmlstream(QXmlStreamReader& a_stream);

    private:
      // Data Members
      //============================================================
      project::object& m_project;
      extended_manager_type m_emanager;
      std::vector<extended_handle_type> m_ehandles;
    };
  }
}


#endif // DATA_MANAGER_H
