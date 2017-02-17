#ifndef PROJECT_OUTLINER_H
#define PROJECT_OUTLINER_H

#include <memory>
#include <QWidget>

namespace sak
{
    class Project;
    //---------------------------------------------------------------------------
    // Project_Outliner
    //---------------------------------------------------------------------------
    class Project_Outliner :
            public QWidget
    {
    public:
        explicit Project_Outliner(Project& a_project, QWidget* a_parent = nullptr);
        ~Project_Outliner() override;

    private:
        // Pimpl Data
        //============================================================
        class Implementation;
        std::unique_ptr<Implementation> m_data;

        Implementation& imp()                { return *m_data; }
        Implementation const& cimp() const   { return *m_data; }
    };
}

#endif // PROJECT_OUTLINER_H
