#ifndef SAK_PROJECT_OUTLINER_WIDGET_HPP
#define SAK_PROJECT_OUTLINER_WIDGET_HPP

#include "fwd/widget.hpp"
#include <sak/project/fwd/object.hpp>
#include <memory>
#include <QWidget>

namespace sak
{
  namespace project
  {
    namespace outliner
    {
      //---------------------------------------------------------------------------
      // outliner::widget
      //---------------------------------------------------------------------------
      class widget :
              public QWidget
      {
      public:
          explicit widget(object& a_project, QWidget* a_parent = nullptr);
          ~widget() override;

      private:
          // Pimpl Data
          //============================================================
          class impl;
          std::unique_ptr<impl> m_data;

          impl& imp()                { return *m_data; }
          impl const& cimp() const   { return *m_data; }
      };
    }
  }
}

#endif // SAK_PROJECT_OUTLINER_WIDGET_HPP
