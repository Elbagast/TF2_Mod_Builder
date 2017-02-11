#ifndef PROJECT_OUTLINER_ITEMS_H
#define PROJECT_OUTLINER_ITEMS_H

#include "../qtlib/outliner/outliner_item.h"
#include "../qtlib/outliner/outliner_item_root.h"
#include "../qtlib/outliner/outliner_item_readonly.h"

namespace sak
{
    class Project;

    class Outliner_Root :
            public qtlib::Outliner_Item_Root
    {
    public:
        explicit Outliner_Root(Project& a_project);
        ~Outliner_Root() override;
    };

    class Outliner_Project :
            public qtlib::Outliner_Item_ReadOnly
    {
    public:
        Outliner_Project(Project& a_project, Outliner_Root* a_parent);
        ~Outliner_Project() override;

        Project& get_project();
        Project const& cget_project() const;

    protected:
        // Virtuals
        //============================================================
        QVariant v_get_data(int a_role) const override;
        void v_custom_context_menu(QAbstractItemView* a_view, qtlib::Outliner_Model* a_model, QPoint const& a_position) override;

    private:
        Project& m_project;
    };

    class Outliner_Header_Files :
            public qtlib::Outliner_Item_ReadOnly
    {
    public:
        Outliner_Header_Files(Project& a_project, Outliner_Project* a_parent);
        ~Outliner_Header_Files() override;

        Project& get_project();
        Project const& cget_project() const;

    protected:
        // Virtuals
        //============================================================
        QVariant v_get_data(int a_role) const override;
        void v_custom_context_menu(QAbstractItemView* a_view, qtlib::Outliner_Model* a_model, QPoint const& a_position) override;
    };

    class Outliner_Header_Textures :
            public qtlib::Outliner_Item_ReadOnly
    {
    public:
        Outliner_Header_Textures(Project& a_project, Outliner_Project* a_parent);
        ~Outliner_Header_Textures() override;

        Project& get_project();
        Project const& cget_project() const;

    protected:
        // Virtuals
        //============================================================
        QVariant v_get_data(int a_role) const override;
        void v_custom_context_menu(QAbstractItemView* a_view, qtlib::Outliner_Model* a_model, QPoint const& a_position) override;
    };
}

#endif // PROJECT_OUTLINER_ITEMS_H
