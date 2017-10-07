#include "widget.hpp"
#include "member_widget.hpp"
//#include <qtlib/edit/widget_traits.hpp>
#include <sak/edit/widget_traits.hpp>

#include <sak/project/object.hpp>
#include <sak/shared/interface.hpp>

namespace sak
{
  namespace shared
  {
    namespace
    {
      // This entire template does not need to be known to the world

      //---------------------------------------------------------------------------
      // shared::member_edit_widget
      //---------------------------------------------------------------------------
      // Wraps the editor for the member value and normalises the signals so that we
      // can use it. This widget is responsible for dispatching the call to change
      // the member value when it is edited.

      template <typename T, std::size_t Index>
      class member_edit_widget :
          public abstract::member_edit_widget
      {
      public:
        // Typedefs
        //============================================================
        using object_type = T;
        using member_value_variant = data_class_member_variant_t<object_type>;
        using member_type = data_class_member_t<object_type,Index>;
        using member_name_type = data_class_member_name_t<object_type,Index>;

        using handle_type = handle<object_type>;

        using widget_traits_type = sak::edit::widget_traits<member_type>;
        //using widget_type = typename widget_traits_type::widget_type;

        // Special 6
        //============================================================
        member_edit_widget(project::object& a_project, handle_type& a_handle, QWidget* a_parent = nullptr):
          abstract::member_edit_widget(a_parent),
          m_project{a_project},
          m_handle{a_handle},
          m_layout{std::make_unique<QHBoxLayout>(nullptr)},
          m_widget{widget_traits_type::make_empty_widget()}
        {
          m_layout->setContentsMargins(0,0,0,0);
          m_layout->addWidget(m_widget.get());
          this->setLayout(m_layout.get());

          this->setToolTip("This is a tooltip. Where should we get tooltips from for each type?");

          // Capture the signal and dispatch it
          //QObject::connect(m_widget.get(), widget_traits_type::editing_finished_signal(), this, &member_edit_widget::editing_finished);
          widget_traits_type::connect_to(m_widget.get(), this, &abstract::member_edit_widget::editing_finished);
          update();
        }
        ~member_edit_widget() override final = default;

        // Virtuals
        //============================================================
        void update() override final
        {
          widget_traits_type::set_widget_value(m_widget.get(), m_handle->cmember_at<Index>());
        }

        void editing_finished() override final
        {
          // hmm. set can fail to do anything. But it only fails if the input is the same as the data?
          //project_access<object_type>::change_at(&m_project, m_handle, Index, member_value_variant(widget_traits_type::get_widget_value(m_widget.get())));

          m_project.get_interface<object_type>().change_at<Index>(m_handle, widget_traits_type::get_widget_value(m_widget.get()));
        }

        // Data members
        //============================================================
        project::object& m_project;
        handle_type& m_handle;
        std::unique_ptr<QHBoxLayout> m_layout;
        std::unique_ptr<QWidget> m_widget;
      };


      //---------------------------------------------------------------------------
      // shared::make_widgets<T>
      //---------------------------------------------------------------------------
      // Make a widgt array by iterating through the object's members.
      template <typename T>
      struct make_widgets
      {
        using object_type = T;
        using handle_type = handle<object_type>;

        using widget_type = abstract::member_edit_widget;
        using widget_array = std::array<std::unique_ptr<widget_type>, data_class_size_v<object_type>>;

        template <std::size_t Index, std::size_t End = std::tuple_size<widget_array>::value>
        struct do_loop
        {
          void operator()(widget_array& a_widgets, QFormLayout* a_layout, project::object& a_project, handle_type& a_handle)
          {
            using true_widget_type = member_edit_widget<object_type, Index>;
            using member_name_type = data_class_member_name_t<object_type,Index>;

            // make the true widget as a base widget
            auto l_widget = std::unique_ptr<widget_type>(std::make_unique<true_widget_type>(a_project,a_handle,nullptr).release());

            // add it to the layout
            a_layout->addRow(QString::fromStdString(member_name_type::data()), l_widget.get());

            // put it in the array
            std::swap(std::get<Index>(a_widgets), l_widget);

            // continue
            do_loop<Index+1,End>()(a_widgets, a_layout, a_project, a_handle);
          }
        };

        template <std::size_t End>
        struct do_loop<End,End>
        {
          void operator()(widget_array&, QFormLayout*, project::object&, handle_type&)
          {
          }
        };

        widget_array operator()(QFormLayout* a_layout, project::object& a_project, handle_type& a_handle)
        {
          widget_array l_widgets{};
          do_loop<0>()(l_widgets, a_layout, a_project, a_handle);
          return l_widgets;
        }
      };
    }
  }
}



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

// Special 6
//============================================================
template <typename T>
sak::shared::widget<T>::widget(project::object& a_project, handle_type const& a_handle, QWidget* a_parent = nullptr):
  QWidget(a_parent),
  m_project{a_project},
  m_handle{a_handle},
  m_layout{std::make_unique<QFormLayout>(nullptr)},
  m_widgets{make_widgets<T>()(m_layout.get(), m_project, m_handle)}
{
  this->setLayout(m_layout.get());
}

template <typename T>
sak::shared::widget<T>::~widget() = default;

// Public Interface
//============================================================
template <typename T>
void sak::shared::widget<T>::changed()
{
  for (auto& l_widget : m_widgets)
  {
    l_widget->update();
  }
}

template <typename T>
void sak::shared::widget<T>::changed_at(std::size_t a_section)
{
  m_widgets.at(a_section)->update();
}

template <typename T>
typename sak::shared::widget<T>::handle_type const& sak::shared::widget<T>::cget_handle() const
{
  return m_handle;
}


// Forced Instantiations
//============================================================
template sak::file::widget;
template sak::texture::widget;
