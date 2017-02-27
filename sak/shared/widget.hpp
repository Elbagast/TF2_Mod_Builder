#ifndef SAK_SHARED_WIDGET_HPP
#define SAK_SHARED_WIDGET_HPP

#include "fwd/widget.hpp"
#include <sak/shared/object.hpp>
#include <sak/shared/extended_manager.hpp>
#include <dclib/rt/v1/polymorhpic_tuple.hpp>
#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFormLayout>
#include <tuple>
#include <memory>

namespace sak
{
  namespace shared
  {
    namespace abstract
    {
      //---------------------------------------------------------------------------
      // edit::abstract::member_widget
      //---------------------------------------------------------------------------
      // This is the base class for member value editor widgets. These are the
      // things that must be supplied. Inherit this class and compose the true
      // editor in it.
      class member_widget :
          public QWidget
      {
        Q_OBJECT
      public:
        explicit member_widget(QWidget* a_parent):
          QWidget(a_parent)
        {}
        virtual ~member_widget() = default;

        virtual void update() = 0;
      signals:
        void editing_finished();
      };
    }

    template <typename T, std::size_t I>
    class member_widget;

    // does this even make sense? might be too much too low down.
    // But we need the handle to do the update call...so this has to know it's
    // type at least...
    template <std::size_t I, typename T, typename...Ms>
    class member_widget<object<T,Ms...>,I> :
        public abstract::member_widget
    {
    public:
      using object_type = object<T,Ms...>;
      using member_type = mf::object_member_t<object_type,I>;
      using value_type = typename member_type::value_type;

      using extended_handle_type = extended_handle<object_type>;

      explicit member_widget(extended_handle_type& a_ehandle, QWidget* a_parent):
        abstract::member_widget(a_parent),
        m_ehandle{a_ehandle},
        m_layout{std::make_unique<>(nullptr)},
        m_widget{std::make_unique<QLineEdit>(nullptr)}
      {
        m_layout->setContentsMargins(0,0,0,0);
        m_layout->addWidget(m_widget.get());
        this->setLayout(m_layout.get());

        // Normalise the signal
        QObject::connect(this, &QLineEdit::editingFinished, [this]()
        {
          this->emit editing_finished();
        });
      }
      ~member_widget() override = default;

      void update() override
      {
        // Normally, th
        m_widget->setText(m_ehandle.cget().cat<I>().cget());
      }
    private:
      extended_handle_type& m_ehandle;
      std::unique_ptr<QHBoxLayout> m_layout;
      std::unique_ptr<QLineEdit> m_widget;
    };


    template <typename T>
    struct editor_widget_traits
    {
      using type = QLineEdit;

      static std::unique_ptr<QLineEdit> make_widget()
      {
        return std::make_unique<QLineEdit>(nullptr);
      }


      static std::unique_ptr<QWidget> make_anon_widget();
      static T const& get_editor_data(QWidget* a_editor);
    };



    template <typename T>
    using editor_widget_t = typename editor_widget_traits<T>::type;


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

      using widget_typelist = dclib::meta::typelist<editor_widget_type<typename Ms::value_type>...>;
      using widget_tuple = dclib::rt::v1::polymorphic_tuple<QWidget, editor_widget_t<typename Ms::value_type>...>;

      struct make_widgets
      {
        template <std::size_t Index, std::size_t End = widget_tuple::size()>
        struct do_loop
        {
          void operator()(widget_tuple& a_widgets, QFormLayout* a_layout, extended_handle_type& a_ehandle)
          {
            using widget_type = dclib::meta::mf::type_at_t<widget_typelist, Index>;

            std::get<Index>(a_widgets) = std::make_unique<widget_type, Index>>(nullptr);

            QObject::connect(std::get<Index>(a_widgets).get(), &widget_type::editingFinished, [a_ehandle]()
            {
                a_ehandle.get().cat<Index>().set(std::get<Index>(a_widgets)->text());// going to need a standardised editor interface
            });
            do_loop<Index+1,End>()(a_widgets, a_layout);

            m_layout->addRow(a_ehandle.cget().cat<Index>().name(), std::get<Index>(a_widgets).get());
          }
        };

        template <std::size_t End>
        struct do_loop<End,End>
        {

        }


        widget_tuple operator()(QFormLayout* a_layout, extended_handle_type& m_ehandle)
        {
          widget_tuple l_widgets{};
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

      void data_changed();
      void data_changed_at(std::size_t a_section);

      extended_handle_type const& cget_handle() const
      {
        return m_ehandle;
      }
    private:
        extended_handle_type m_ehandle;
        std::unique_ptr<QFormLayout> m_layout;
        widget_tuple m_widgets;
    };
  }
}
#endif // SAK_SHARED_WIDGET_HPP
