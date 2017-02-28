#include "widget.hpp"

//---------------------------------------------------------------------------
// shared::abstract::member_edit_widget
//---------------------------------------------------------------------------
// This is the base class for member value editor widgets. These are the
// things that must be supplied. Inherit this class and compose the true
// editor in it. Also for a signal to be generated it must not be part of a template.

// Special 6
//============================================================
sak::shared::abstract::member_edit_widget::member_edit_widget(QWidget* a_parent):
  QWidget(a_parent)
{}

sak::shared::abstract::member_edit_widget::~member_edit_widget() = default;

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

      //template <std::size_t Index, typename T, typename...Ms>
      //class member_edit_widget<object<T,Ms...>,Index> :
      //    public abstract::member_edit_widget
      //{
      //public:
      //  using object_type = object<T,Ms...>;
      template <typename T, std::size_t Index>
      class member_edit_widget :
          public abstract::member_edit_widget
      {
      public:
        // Typedefs
        //============================================================
        using object_type = T;
        using member_type = mf::object_member_t<object_type,Index>;
        using value_type = typename member_type::value_type;

        using extended_handle_type = extended_handle<object_type>;

        using widget_traits_type = qtlib::edit::widget_traits<value_type>;
        using widget_type = typename widget_traits_type::widget_type;

        // Special 6
        //============================================================
        explicit member_edit_widget(extended_handle_type& a_ehandle, QWidget* a_parent):
          abstract::member_edit_widget(a_parent),
          m_ehandle{a_ehandle},
          m_layout{std::make_unique<QHBoxLayout>(nullptr)},
          m_widget{std::make_unique<widget_type>(nullptr)}
        {
          m_layout->setContentsMargins(0,0,0,0);
          m_layout->addWidget(m_widget.get());
          this->setLayout(m_layout.get());

          // Capture the signal and dispatch it
          QObject::connect(m_widget.get(), widget_traits_type::editing_finished_signal(), this, &member_edit_widget::editing_finished);
          //{
          //  this->editing_finished();
          //});
          update();
        }
        ~member_edit_widget() override final= default;

        // Public Interface
        //============================================================
        void update() override final
        {
          widget_traits_type::set_widget_value(m_widget.get(), m_ehandle.cget().cat<Index>().cget());
        }
      private:
        // Private Interface
        //============================================================
        void editing_finished()
        {
          m_ehandle.get().at<Index>().set(widget_traits_type::get_widget_value(m_widget.get()));
          // hmm. set can fail to do anything. But it only fails if the input is the same as the data?
        }

        // Data members
        //============================================================
        extended_handle_type& m_ehandle;
        std::unique_ptr<QHBoxLayout> m_layout;
        std::unique_ptr<widget_type> m_widget;
      };

      template <typename T>
      struct make_widgets
      {
        using object_type = T;
        using extended_handle_type = extended_handle<object_type>;

        using widget_type = abstract::member_edit_widget;
        using widget_array = std::array<std::unique_ptr<widget_type>, object_type::size()>;

        template <std::size_t Index, std::size_t End = std::tuple_size<widget_array>::value>
        struct do_loop
        {
          void operator()(widget_array& a_widgets, QFormLayout* a_layout, extended_handle_type& a_ehandle)
          {
            using true_widget_type = member_edit_widget<object_type, Index>;

            // make the true widget as a base widget
            auto l_widget = std::unique_ptr<widget_type>(std::make_unique<true_widget_type>(a_ehandle,nullptr).release());

            // add it to the layout
            a_layout->addRow(QString::fromStdString(a_ehandle.cget().cat<Index>().name()), l_widget.get());

            // put it in the array
            std::swap(std::get<Index>(a_widgets), l_widget);

            // continue
            do_loop<Index+1,End>()(a_widgets, a_layout, a_ehandle);
          }
        };

        template <std::size_t End>
        struct do_loop<End,End>
        {
          void operator()(widget_array&, QFormLayout*, extended_handle_type&)
          {
          }
        };

        widget_array operator()(QFormLayout* a_layout, extended_handle_type& m_ehandle)
        {
          widget_array l_widgets{};
          do_loop<0>()(l_widgets, a_layout, m_ehandle);
          return l_widgets;
        }
      };
    }
  }
}

//---------------------------------------------------------------------------
// shared::member_edit_widget
//---------------------------------------------------------------------------
// Wraps the editor for the member value and normalises the signals so that we
// can use it. This widget is responsible for dispatching the call to change
// the member value when it is edited.
/*
// Special 6
//============================================================
template <typename T, std::size_t I>
sak::shared::member_edit_widget<T,I>::member_edit_widget(extended_handle_type& a_ehandle, QWidget* a_parent):
  abstract::member_edit_widget(a_parent),
  m_ehandle{a_ehandle},
  m_layout{std::make_unique<QHBoxLayout>(nullptr)},
  m_widget{std::make_unique<widget_type>(nullptr)}
{
  m_layout->setContentsMargins(0,0,0,0);
  m_layout->addWidget(m_widget.get());
  this->setLayout(m_layout.get());

  // Capture the signal and dispatch it
  QObject::connect(m_widget.get(), widget_traits_type::editing_finished_signal(), this, &member_edit_widget::editing_finished);
  //{
  //  this->editing_finished();
  //});
}

template <typename T, std::size_t I>
sak::shared::member_edit_widget<T,I>::~member_edit_widget() = default;

// Public Interface
//============================================================
template <typename T, std::size_t I>
void sak::shared::member_edit_widget<T,I>::update()
{
  widget_traits_type::set_widget_value(m_widget.get(), m_ehandle.cget().cat<Index>().cget());
}

// Private Interface
//============================================================
template <typename T, std::size_t I>
void sak::shared::member_edit_widget<T,I>::editing_finished()
{
  m_ehandle.get().at<Index>().set(widget_traits_type::get_widget_value(m_widget.get()));
  // hmm. set can fail to do anything. But it only fails if the input is the same as the data?
}
*/


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
sak::shared::widget<T>::widget(extended_handle_type const& a_ehandle, QWidget* a_parent = nullptr):
  QWidget(a_parent),
  m_ehandle{a_ehandle},
  m_layout{std::make_unique<QFormLayout>(nullptr)},
  m_widgets{make_widgets<T>()(m_layout.get(), m_ehandle)}
{
  this->setLayout(m_layout.get());
}

template <typename T>
sak::shared::widget<T>::~widget() = default;

// Public Interface
//============================================================
template <typename T>
void sak::shared::widget<T>::data_changed()
{
  for (auto& l_widget : m_widgets)
  {
    l_widget->update();
  }
}

template <typename T>
void sak::shared::widget<T>::data_changed_at(std::size_t a_section)
{
  m_widgets.at(a_section)->update();
}

template <typename T>
typename sak::shared::widget<T>::extended_handle_type const& sak::shared::widget<T>::cget_handle() const
{
  return m_ehandle;
}


// Forced Instantiations
//============================================================
template sak::file::widget;
