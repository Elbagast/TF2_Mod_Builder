#ifndef SAK_OUTLINER_WIDGET_HPP
#define SAK_OUTLINER_WIDGET_HPP

#include <memory>
#include <QWidget>

namespace sak
{
  class Project;

  namespace outliner
  {
    //---------------------------------------------------------------------------
    // outliner::widget
    //---------------------------------------------------------------------------
    class widget :
            public QWidget
    {
    public:
        explicit widget(Project& a_project, QWidget* a_parent = nullptr);
        ~widget() override;

    private:
        // Pimpl Data
        //============================================================
        class Implementation;
        std::unique_ptr<Implementation> m_data;

        Implementation& imp()                { return *m_data; }
        Implementation const& cimp() const   { return *m_data; }
    };
  }
}

#endif // SAK_OUTLINER_WIDGET_HPP
