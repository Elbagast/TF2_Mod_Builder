#include "section_widget.hpp"

#include "abstract_member_edit_widget.hpp"
#include "project_interface.hpp"
#include "section_interface.hpp"
#include "section_data.hpp"

#include <QHBoxLayout>
#include <QFormLayout>
#include <QDebug>

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

      using Handle_Type = Handle<Data_Type>;

      // Special 6
      //============================================================
      Member_Edit_Widget(Project_Interface* a_project, Handle_Type& a_handle, QWidget* a_parent = nullptr):
        Abstract_Member_Edit_Widget(a_parent),
        m_project{a_project},
        m_handle{a_handle},
        m_layout{std::make_unique<QHBoxLayout>(nullptr)},
        m_widget{Member_Type::make_widget()}
      {
        // Configure the layout.
        m_layout->setContentsMargins(0,0,0,0);
        m_layout->addWidget(m_widget.get());
        this->setLayout(m_layout.get());

        // Connect the editor.
        Member_Type::connect_to(m_widget.get(), this);

        // Update it.
        update_data();
      }
      ~Member_Edit_Widget() override final = default;

      // Virtuals
      //============================================================
      // Called when the data has changed elsewhere.
      void update_data() override final
      {
        qDebug() << "sak::Member_Edit_Widget::update_data";
        // Set the widget data to match the handle data.
        Member_Type::set_widget_value(m_widget.get(), m_handle->cmember_at<Index>());
      }

      // Called when the widget has been used to edit the value to
      // something acceptable.
      void editing_finished() override final
      {
        qDebug() << "sak::Member_Edit_Widget::editing_finished";
        // The editor now contains a different value to the data.

        // Use the interface to change stuff.
        auto l_result = m_project->get_interface<Data_Type>().change_at<Index>(m_handle, Member_Type::get_widget_value(m_widget.get()));

        // If a command wasn't issued then editing failed, so update the data
        if (!l_result)
        {
          this->Member_Edit_Widget::editing_failed();
        }
      }

      // Called when the widget has been used to edit the value to
      // something unacceptable.
      void editing_failed() override final
      {
        qDebug() << "sak::Member_Edit_Widget::editing_failed";
        // Just call update_data to make sure editor and data match.
        this->Member_Edit_Widget::update_data();
      }

      // Data members
      //============================================================
      Project_Interface* m_project;
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
      using Handle_Type = Handle<Data_Type>;

      using widget_type = Abstract_Member_Edit_Widget;
      using Widget_Array_Type = typename Section_Widget<T>::Widget_Array_Type;

      template <std::size_t Index, std::size_t End = std::tuple_size<Widget_Array_Type>::value>
      class do_loop
      {
      public:
        void operator()(Widget_Array_Type& a_widgets, QFormLayout* a_layout, Project_Interface* a_project, Handle_Type& a_handle)
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
        void operator()(Widget_Array_Type&, QFormLayout*, Project_Interface*, Handle_Type&)
        {
        }
      };

    public:
      Widget_Array_Type operator()(QFormLayout* a_layout, Project_Interface* a_project, Handle_Type& a_handle)
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

// Special 6
//============================================================
template <typename T>
sak::Section_Widget<T>::Section_Widget(Project_Interface* a_project, Handle_Type const& a_handle, QWidget* a_parent):
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
// Called when the data for this handle has drastically changed.
template <typename T>
void sak::Section_Widget<T>::changed()
{
  // Call update_data on all the widgets
  for (auto& l_widget : m_widgets)
  {
    // Take note that this different to QWidget::update
    l_widget->update_data();
  }
}

// Called when the data a given member has changed.
template <typename T>
void sak::Section_Widget<T>::changed_at(std::size_t a_section)
{
  // Call update_data on the indexed widgets
  // Take note that this different to QWidget::update
  m_widgets.at(a_section)->update_data();
}

// Get the handle this widget is related to. Mostly so what
template <typename T>
typename sak::Section_Widget<T>::Handle_Type const& sak::Section_Widget<T>::cget_handle() const
{
  return m_handle;
}


// Forced Instantiations
//============================================================
template sak::File_Widget;
template sak::Texture_Widget;
