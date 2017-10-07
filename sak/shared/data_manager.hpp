#ifndef SAK_SHARED_DATA_MANAGER_HPP
#define SAK_SHARED_DATA_MANAGER_HPP

#include "fwd/data_manager.hpp"
#include "manager.hpp"

#include "fwd/signalbox.hpp"
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

    /*
    Assessment:
    ------------
    - project::object dependency can be removed
      - it is currently a circular reference...project::object owns this and directs
        calls to get the name list to this, so we don't need the reference in here at all...
        - successfully removed
    - the reason this inherits the signalbox<T> os so that we are guaranteed that it has
      the signal functions.
      - that could probably be skipped and signalbox<T> reserved for dependent signal
        monitoring objects rather than the originator, which is what this is/would be.
        - actually if this takes the signal_dispatcher code into itself then it shouldn't
          inherit the signalbox because then the 'forbidden' object is irrelevent.
          - successfully added

    */

    template <typename T>
    class data_manager
    {
    public:
      // Typedefs
      //============================================================
      using signalbox_type = abstract::signalbox<T>;
      using object_type = T;
      using manager_type = manager<object_type>;
      using handle_type = handle<object_type>;

      // Special 6
      //============================================================
      explicit data_manager();
      ~data_manager();

      // Signalling interface
      //============================================================
      // This part of the interface is the same as the entire signalbox_type
      // interface.

      void changed(handle_type const& a_handle);
      // When a File has its data changed in a specific place, this is called.
      void changed_at(handle_type const& a_handle, std::size_t a_section);
      // When a File has been added, this is called.
      void added(handle_type const& a_handle);
      // When a File has been removed, this is called.
      void removed(handle_type const& a_handle);
      // When a File requests an editor, this is called.
      void requests_editor(handle_type const& a_handle);

      // When a File requests an editor, this is called.
      void requests_focus(handle_type const& a_handle);

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

      // You may create new objects using these two functions. Objects created in this way
      // are part of the data management system but nothing outside of it has been notified
      // of their presense.

      // Make a new file using the supplied data. Project's data management system owns it but
      // it is not part of the Project.
      handle_type make_emplace(object_type&& a_object);

      // Make a new file using the default parameters. Project's data management system owns it
      // but it is not part of the Project.
      handle_type make();

      void to_xmlstream(QXmlStreamWriter& a_stream) const;

      void from_xmlstream(QXmlStreamReader& a_stream);

      // Add an object that will rely on the outbound data signals. If nulltpr, nothing happens.
      void add_signalbox(signalbox_type* a_signalbox);

      // Remove an object that will rely on the outbound data signals. If nulltpr, nothing happens.
      void remove_signalbox(signalbox_type* a_signalbox);

      // Remove all signalboxes
      void clear_signalboxes();

    private:
      // Data Members
      //============================================================
      manager_type m_manager;
      std::vector<handle_type> m_handles;
      std::vector<signalbox_type*> m_signalboxes;
    };
  }
}

#endif // DATA_MANAGER_H
