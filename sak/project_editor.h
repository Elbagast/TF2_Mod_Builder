#ifndef PROJECT_EDITOR_H
#define PROJECT_EDITOR_H

#include <memory>
#include <QWidget>

namespace sak
{
    class Project;
    //---------------------------------------------------------------------------
    // Project_Editor
    //---------------------------------------------------------------------------
    class Project_Editor :
            public QWidget
    {
    public:
        // Special 6
        //============================================================
        explicit Project_Editor(Project& a_project, QWidget* a_parent = nullptr);
        ~Project_Editor() override;

    private:
        // Pimpl Data
        //============================================================
        class Implementation;
        std::unique_ptr<Implementation> m_data;

        Implementation& imp()                { return *m_data; }
        Implementation const& cimp() const   { return *m_data; }
    };
}

#endif // PROJECT_EDITOR_H
