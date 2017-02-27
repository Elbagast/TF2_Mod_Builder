#ifndef SAK_SHARED_WIDGET_HPP
#define SAK_SHARED_WIDGET_HPP

#include "fwd/widget.hpp"
#include <sak/shared/object.hpp>
#include <sak/shared/extended_manager.hpp>
#include <qtlib/edit/widget_traits.hpp>
#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFormLayout>
#include <tuple>
#include <memory>
#include <array>


namespace sak
{
  namespace shared
  {
    namespace abstract
    {
      //---------------------------------------------------------------------------
      // shared::abstract::member_edit_widget
      //---------------------------------------------------------------------------
      // This is the base class for member value editor widgets. These are the
      // things that must be supplied. Inherit this class and compose the true
      // editor in it. Also for a signal to be generated it must not be part of a template.
      class member_edit_widget :
          public QWidget
      {
        //Q_OBJECT
      public:
        explicit member_edit_widget(QWidget* a_parent):
          QWidget(a_parent)
        {}
        ~member_edit_widget() override = default;

        virtual void update() = 0;
      signals:
        //void editing_finished(std::size_t a_index);
      };
    }

    template <typename T, std::size_t Index>
    class member_value_edit_widget;

    //---------------------------------------------------------------------------
    // shared::member_edit_widget
    //---------------------------------------------------------------------------
    // Wraps the editor for the member value and normalises the signals so that we
    // can use it. This widget is responsible for dispatching the call to change
    // the member value when it is edited.

    template <std::size_t Index, typename T, typename...Ms>
    class member_edit_widget<object<T,Ms...>,Index> :
        public abstract::member_edit_widget
    {
    public:
      using object_type = object<T,Ms...>;
      using member_type = mf::object_member_t<object_type,Index>;
      using value_type = typename member_type::value_type;

      using extended_handle_type = extended_handle<object_type>;

      using widget_traits_type = qtlib::edit::widget_traits<value_type>;
      using widget_type = typename widget_traits_type::widget_type;

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
      }
      ~member_edit_widget() override final= default;

      void update() override final
      {
        widget_traits_type::set_widget_value(m_widget.get(), m_ehandle.cget().cat<Index>().cget());
      }
    private:
      void editing_finished()
      {
        m_ehandle.get().at<Index>().set(widget_traits_type::get_widget_value(m_widget.get()));
        // hmm. set can fail to do anything. But it only fails if the input is the same as the data?
      }

      extended_handle_type& m_ehandle;
      std::unique_ptr<QHBoxLayout> m_layout;
      std::unique_ptr<widget_type> m_widget;
    };


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
    template <typename T, typename...Ms>
    class widget<object<T,Ms...>> :
        public QWidget
    {
    public:
      using object_type = object<T,Ms...>;
      using extended_handle_type = extended_handle<object_type>;

      using widget_type = abstract::member_edit_widget;
      using widget_array = std::array<std::unique_ptr<widget_type>, object_type::size()>;

      //using widget_typelist = dclib::meta::typelist<editor_widget_type<typename Ms::value_type>...>;
      //using widget_tuple = dclib::rt::v1::polymorphic_tuple<QWidget, editor_widget_t<typename Ms::value_type>...>;

      struct make_widgets
      {
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

      explicit widget(extended_handle_type const& a_ehandle, QWidget* a_parent = nullptr):
        QWidget(a_parent),
        m_ehandle{a_ehandle},
        m_layout{std::make_unique<QFormLayout>(nullptr)},
        m_widgets{make_widgets()(m_layout.get(), m_ehandle)}
      {
        this->setLayout(m_layout.get());
      }
      ~widget() override = default;

      void data_changed()
      {
        for (auto& l_widget : m_widgets)
        {
          l_widget->update();
        }
      }

      void data_changed_at(std::size_t a_section)
      {
        m_widgets.at(a_section)->update();
      }

      extended_handle_type const& cget_handle() const
      {
        return m_ehandle;
      }
    private:
      extended_handle_type m_ehandle;
      std::unique_ptr<QFormLayout> m_layout;
      widget_array m_widgets;
    };
  }
}
#endif // SAK_SHARED_WIDGET_HPP
