#ifndef SAK_SECTION_DATA_MANAGER_HPP
#define SAK_SECTION_DATA_MANAGER_HPP

#ifndef SAK_SECTION_DATA_MANAGER_FWD_HPP
#include "section_data_manager_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_SECTION_SIGNALBOX_FWD_HPP
#include "abstract_section_signalbox_fwd.hpp"
#endif

#ifndef SAK_HANDLE_FWD_HPP
#include "handle_fwd.hpp"
#endif

#ifndef SAK_HANDLE_FACTORY_HPP
#include "handle_factory.hpp"
#endif

#ifndef INCLUDE_STD_VECTOR
#define INCLUDE_STD_VECTOR
#include <vector>
#endif

#ifndef INCLUDE_QT_QSTRING
#define INCLUDE_QT_QSTRING
#include <QString>
#endif

//class QXmlStreamWriter;
//class QXmlStreamReader;

namespace sak
{
  //---------------------------------------------------------------------------
  // sak::Section_Data_Manager<T>
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
  class Section_Data_Manager
  {
  public:
    // Typedefs
    //============================================================
    using Data_Type = T;
    using Factory_Type = Handle_Factory<T>;
    using Handle_Type = Handle<T>;

    using Signalbox_Type = Abstract_Section_Signalbox<T>;


    // Special 6
    //============================================================
    explicit Section_Data_Manager();
    ~Section_Data_Manager();

    // Signalling interface
    //============================================================
    // This part of the interface is the same as the entire Signalbox_Type
    // interface.

    // When a handle has its data changed drastically, or in an unknown place, this is called.
    void changed(Handle_Type const& a_handle);
    // When a handle has its data changed in a specific place, this is called.
    void changed_at(Handle_Type const& a_handle, std::size_t a_section);
    // When a handle has been added, this is called.
    void added(Handle_Type const& a_handle);
    // When a handle has been removed, this is called.
    void removed(Handle_Type const& a_handle);
    // When a handle requests an editor, this is called.
    void requests_editor(Handle_Type const& a_handle);

    // When a handle requests an editor, this is called.
    void requests_focus(Handle_Type const& a_handle);

    // Public Interface
    //============================================================
    // Are there any handles of this type in the currently active project data?
    bool empty() const;

    // How handles of this type in the currently active project data?
    std::size_t count() const;

    // Is this handle in the currently active project data?
    bool has_handle(Handle_Type const& a_handle) const;

    // Get the handle at this index. Handles are sorted alphabetically by the name
    // member of the objects they reference.
    Handle_Type get_at(std::size_t a_index) const;

    // Get all the handles alphabetically sorted by name
    std::vector<Handle_Type> get_all() const;

    // Get all the objects' alphabetically sorted names
    std::vector<QString> get_all_names() const;

    // You may create new objects using these two functions. Objects created in this way
    // are part of the data management system but nothing outside of it has been notified
    // of their presense. Calling has_handle on the handle returned by these functions
    // immediately after will return false.

    // Make a new object using the supplied data. Project's data management system owns it but
    // it is not part of the Project.
    Handle_Type make_emplace(Data_Type&& a_object);

    // Make a new file using the default parameters. Project's data management system owns it
    // but it is not part of the Project.
    Handle_Type make_default();

    // Add an object that will rely on the outbound data signals. If nulltpr, nothing happens.
    void add_signalbox(Signalbox_Type* a_signalbox);

    // Remove an object that will rely on the outbound data signals. If nulltpr, nothing happens.
    void remove_signalbox(Signalbox_Type* a_signalbox);

    // Remove all signalboxes
    void clear_signalboxes();

    // Swap the data with that of another
    void swap(Section_Data_Manager& a_other);

  private:
    // Data Members
    //============================================================
    Factory_Type m_factory;
    std::vector<Handle_Type> m_handles;
    std::vector<Signalbox_Type*> m_signalboxes;
  };


  template <typename T>
  void swap(Section_Data_Manager<T>& a_lhs, Section_Data_Manager<T>& a_rhs)
  {
    a_lhs.swap(a_rhs);
  }
}

#endif // SAK_SECTION_DATA_MANAGER_HPP
