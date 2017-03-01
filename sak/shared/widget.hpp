#ifndef SAK_SHARED_WIDGET_HPP
#define SAK_SHARED_WIDGET_HPP

#include "fwd/widget.hpp"
#include "fwd/member_widget.hpp"
#include <sak/shared/object.hpp>
#include <sak/shared/extended_manager.hpp>
#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFormLayout>
#include <tuple>
#include <memory>
#include <array>

class QHBoxLayout;
class QFormLayout;


namespace sak
{
  namespace shared
  {
    //---------------------------------------------------------------------------
    // shared::widget<T>
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
    class widget :
        public QWidget
    {
    public:
      // Typedefs
      //============================================================
      using object_type = T;

      using extended_handle_type = extended_handle<object_type>;

      using widget_type = abstract::member_edit_widget;
      using widget_array = std::array<std::unique_ptr<widget_type>, object_type::size()>;

      // Special 6
      //============================================================
      explicit widget(extended_handle_type const& a_ehandle, QWidget* a_parent = nullptr);
      ~widget() override;

      // Public Interface
      //============================================================
      void data_changed();
      void data_changed_at(std::size_t a_section);
      extended_handle_type const& cget_handle() const;

    private:
      // Data members
      //============================================================
      extended_handle_type m_ehandle;
      std::unique_ptr<QFormLayout> m_layout;
      widget_array m_widgets;
    };
  }
}
#endif // SAK_SHARED_WIDGET_HPP
