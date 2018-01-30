#ifndef SAK_SECTION_WIDGET_HPP
#define SAK_SECTION_WIDGET_HPP

#ifndef SAK_SECTION_WIDGET_FWD_HPP
#include "section_widget_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_MEMBER_EDIT_WIDGET_FWD_HPP
#include "abstract_member_edit_widget_fwd.hpp"
#endif

#ifndef SAK_SECTION_HANDLE_HPP
#include "section_handle.hpp"
#endif

#ifndef SAK_PROJECT_INTERFACE_FWD_HPP
#include "project_interface_fwd.hpp"
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

#ifndef INCLUDE_STD_ARRAY
#define INCLUDE_STD_ARRAY
#include <array>
#endif

#ifndef INCLUDE_QT_QWIDGET
#define INCLUDE_QT_QWIDGET
#include <QWidget>
#endif

class QFormLayout;

namespace sak
{
  //---------------------------------------------------------------------------
  // Section_Widget<T>
  //---------------------------------------------------------------------------
  /*
  Ok so what do component widgets look like?
  If we start basic, just a form layout of the members, what do we need from that at runtime?

  - for each member
    - make a form row with the name and editor widget
    - connect the editing finished signal to output the changes
    - call update to set the editor to use the current value
  - editor needs
    - access to the handle for updating
    - void changed()
    - void connect(handle&) -> or guarantee a signal to connect to in the template
  - widget needs
    - the handle to signify that the data is active
    - void changed() -> call changed() on all editors
    - void changed_at(index) -> call changed() on the editor at index

  Since the main editor is only called to change things at runtime, the editors
  can be held in a runtime array with only the initialisation being the problem.
  Then the editors just need a baseclass...
  */
  template <typename T>
  class Section_Widget :
      public QWidget
  {
  public:
    // Typedefs
    //============================================================
    using Data_Type = T;
    using Handle_Type = Section_Handle<Data_Type>;
    using Widget_Array_Type = std::array<std::unique_ptr<Abstract_Member_Edit_Widget>, Section_Data_Size_v<Data_Type>>;

    // Special 6
    //============================================================
    Section_Widget(Project_Interface* a_project, Handle_Type const& a_handle, QWidget* a_parent = nullptr);
    ~Section_Widget() override;

    Section_Widget(Section_Widget const&) = delete;
    Section_Widget& operator=(Section_Widget const&) = delete;

    Section_Widget(Section_Widget &&) = delete;
    Section_Widget& operator=(Section_Widget &&) = delete;

    // Public Interface
    //============================================================
    // Called when the data for this handle has drastically changed.
    void changed();

    // Called when the data a given member has changed.
    void changed_at(std::size_t a_section);

    // Get the handle this widget is related to. Mostly so what
    // owns this can investigate it.
    Handle_Type const& cget_handle() const;

  private:
    // Data members
    //============================================================
    Project_Interface* m_project;
    Handle_Type m_handle;
    std::unique_ptr<QFormLayout> m_layout;
    Widget_Array_Type m_widgets;
  };
}

#endif // SAK_SECTION_WIDGET_HPP
