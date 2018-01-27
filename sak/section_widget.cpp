#include "section_widget.hpp"

#include "abstract_member_edit_widget.hpp"
//#include <qtlib/edit/widget_traits.hpp>
//#include "edit_widget_traits.hpp"

#include "project_data.hpp"
#include "section_interface.hpp"
#include "section_data.hpp"

#include <QHBoxLayout>
#include <QFormLayout>

namespace sak
{
  namespace
  {
    // This entire template does not need to be known to the world

    //---------------------------------------------------------------------------
    // Member_Edit_Widget
    //---------------------------------------------------------------------------
    // Wraps the editor for the member value and normalises the signals so that we
    // can use it. This widget is responsible for dispatching the call to change
    // the member value when it is edited.

    template <std::size_t Index, typename T>
    class Member_Edit_Widget :
        public Abstract_Member_Edit_Widget
    {
    public:
      // Typedefs
      //============================================================
      using Data_Type = T;
      //using Member_Value_Variant_Type = Section_Data_Member_Value_Variant_Type<Data_Type>;
      using Member_Type = Section_Data_Member_Type<Index,Data_Type>;
      using Member_Value_Type = Section_Data_Member_Value_Type<Index,Data_Type>;
      using Member_Name_Type = Section_Data_Member_Name_Type<Index,Data_Type>;

      using Handle_Type = Section_Handle<Data_Type>;

      // Currently we deduce the widget traits from the member type, but the
      // member type could instead hold the widget traits type which would
      // allow us to not need to make new data types whilst having new editing
      // widgets e.g. lots of things are strings as data but have input restrictions
      //using Widget_Traits_Type = Edit_Widget_Traits<Member_Type>;

      // Special 6
      //============================================================
      Member_Edit_Widget(Project_Data& a_project, Handle_Type& a_handle, QWidget* a_parent = nullptr):
        Abstract_Member_Edit_Widget(a_parent),
        m_project{a_project},
        m_handle{a_handle},
        m_layout{std::make_unique<QHBoxLayout>(nullptr)},
        m_widget{Member_Type::make_empty_widget()}
      {
        m_layout->setContentsMargins(0,0,0,0);
        m_layout->addWidget(m_widget.get());
        this->setLayout(m_layout.get());

        this->setToolTip("This is a tooltip. Where should we get tooltips from for each type?");

        // Capture the signal and dispatch it
        //QObject::connect(m_widget.get(), Widget_Traits_Type::editing_finished_signal(), this, &Member_Edit_Widget::editing_finished);
        Member_Type::connect_to(m_widget.get(), this);
        update();
      }
      ~Member_Edit_Widget() override final = default;

      // Virtuals
      //============================================================
      void update() override final
      {
        Member_Type::set_widget_value(m_widget.get(), m_handle->cmember_at<Index>());
      }

      void editing_finished() override final
      {
        m_project.get_interface<Data_Type>().change_at<Index>(m_handle, Member_Type::get_widget_value(m_widget.get()));
      }

      // Data members
      //============================================================
      Project_Data& m_project;
      Handle_Type& m_handle;
      std::unique_ptr<QHBoxLayout> m_layout;
      std::unique_ptr<QWidget> m_widget;
    };


    //---------------------------------------------------------------------------
    // Make_Member_Widgets<T>
    //---------------------------------------------------------------------------
    // Make a widget array by iterating through the object's members.
    template <typename T>
    class Make_Member_Widgets
    {
    private:
      using Data_Type = T;
      using Handle_Type = Section_Handle<Data_Type>;

      using widget_type = Abstract_Member_Edit_Widget;
      using Widget_Array_Type = typename Section_Widget<T>::Widget_Array_Type;

      template <std::size_t Index, std::size_t End = std::tuple_size<Widget_Array_Type>::value>
      class do_loop
      {
      public:
        void operator()(Widget_Array_Type& a_widgets, QFormLayout* a_layout, Project_Data& a_project, Handle_Type& a_handle)
        {
          using True_Widget_Type = Member_Edit_Widget<Index, Data_Type>;
          using Member_Name_Type = Section_Data_Member_Name_Type<Index,Data_Type>;

          // make the true widget as a base widget
          auto l_widget = std::unique_ptr<widget_type>(std::make_unique<True_Widget_Type>(a_project,a_handle,nullptr).release());

          // add it to the layout
          a_layout->addRow(QString::fromStdString(Member_Name_Type::data()), l_widget.get());

          // put it in the array
          std::swap(std::get<Index>(a_widgets), l_widget);

          // continue
          do_loop<Index+1,End>()(a_widgets, a_layout, a_project, a_handle);
        }
      };

      template <std::size_t End>
      class do_loop<End,End>
      {
      public:
        void operator()(Widget_Array_Type&, QFormLayout*, Project_Data&, Handle_Type&)
        {
        }
      };

    public:
      Widget_Array_Type operator()(QFormLayout* a_layout, Project_Data& a_project, Handle_Type& a_handle)
      {
        Widget_Array_Type l_widgets{};
        do_loop<0>()(l_widgets, a_layout, a_project, a_handle);
        return l_widgets;
      }
    };
  }
}



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

// Special 6
//============================================================
template <typename T>
sak::Section_Widget<T>::Section_Widget(Project_Data& a_project, Handle_Type const& a_handle, QWidget* a_parent):
  QWidget(a_parent),
  m_project{a_project},
  m_handle{a_handle},
  m_layout{std::make_unique<QFormLayout>(nullptr)},
  m_widgets{Make_Member_Widgets<T>()(m_layout.get(), m_project, m_handle)}
{
  this->setLayout(m_layout.get());
}

template <typename T>
sak::Section_Widget<T>::~Section_Widget() = default;

// Public Interface
//============================================================
template <typename T>
void sak::Section_Widget<T>::changed()
{
  for (auto& l_widget : m_widgets)
  {
    l_widget->update();
  }
}

template <typename T>
void sak::Section_Widget<T>::changed_at(std::size_t a_section)
{
  m_widgets.at(a_section)->update();
}

template <typename T>
typename sak::Section_Widget<T>::Handle_Type const& sak::Section_Widget<T>::cget_handle() const
{
  return m_handle;
}


// Forced Instantiations
//============================================================
template sak::File_Widget;
template sak::Texture_Widget;
