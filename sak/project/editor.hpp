#ifndef SAK_PROJECT_EDITOR_HPP
#define SAK_PROJECT_EDITOR_HPP

#include "fwd/editor.hpp"
#include "fwd/object.hpp"
#include <memory>
#include <QWidget>

namespace sak
{
  namespace project
  {
    //---------------------------------------------------------------------------
    // project::editor
    //---------------------------------------------------------------------------
    class editor :
            public QWidget
    {
    public:
        // Special 6
        //============================================================
        explicit editor(object& a_project, QWidget* a_parent = nullptr);
        ~editor() override;

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


#endif // SAK_PROJECT_EDITOR_HPP
