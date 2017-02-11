#include "project_outliner_items.h"
#include "project.h"
#include <QString>
#include <QVariant>

sak::Outliner_Root::Outliner_Root(Project& a_project):
    qtlib::Outliner_Item_Root()
{
    this->append_child(std::make_unique<Outliner_Project>(a_project, this));
}

sak::Outliner_Root::~Outliner_Root() = default;


sak::Outliner_Project::Outliner_Project(Project& a_project, Outliner_Root* a_parent):
    qtlib::Outliner_Item_ReadOnly(a_parent),
    m_project{a_project}
{
    this->append_child(std::make_unique<Outliner_Header_Files>(a_project, this));
    this->append_child(std::make_unique<Outliner_Header_Textures>(a_project, this));
}

sak::Outliner_Project::~Outliner_Project() = default;

sak::Project& sak::Outliner_Project::get_project()
{
    return m_project;
}

sak::Project const& sak::Outliner_Project::cget_project() const
{
    return m_project;
}

// Virtuals
//============================================================
QVariant sak::Outliner_Project::v_get_data(int a_role) const
{
    if (a_role == Qt::DisplayRole)
    {
        return QVariant(m_project.name());
    }
    else
    {
        return QVariant(QString::fromUtf8(u8"PROJECT FUCK UP"));
    }
}

void sak::Outliner_Project::v_custom_context_menu(QAbstractItemView* a_view, qtlib::Outliner_Model* a_model, QPoint const& a_position)
{
    return this->Outliner_Item::v_custom_context_menu(a_view, a_model,a_position);
}



sak::Outliner_Header_Files::Outliner_Header_Files(Project& a_project, Outliner_Project* a_parent):
    qtlib::Outliner_Item_ReadOnly(a_parent)
{

}

sak::Outliner_Header_Files::~Outliner_Header_Files() = default;

sak::Project& sak::Outliner_Header_Files::get_project()
{
    return static_cast<Outliner_Project*>(get_parent())->get_project();
}

sak::Project const& sak::Outliner_Header_Files::cget_project() const
{
    return static_cast<Outliner_Project const*>(get_parent())->cget_project();
}

// Virtuals
//============================================================
QVariant sak::Outliner_Header_Files::v_get_data(int a_role) const
{
    if (a_role == Qt::DisplayRole)
    {
        return QVariant(u8"Files");
    }
    else
    {
        return QVariant(QString::fromUtf8(u8"Files FUCK UP"));
    }
}

void sak::Outliner_Header_Files::v_custom_context_menu(QAbstractItemView* a_view, qtlib::Outliner_Model* a_model, QPoint const& a_position)
{
    return this->Outliner_Item::v_custom_context_menu(a_view, a_model,a_position);
}


sak::Outliner_Header_Textures::Outliner_Header_Textures(Project& a_project, Outliner_Project* a_parent):
    qtlib::Outliner_Item_ReadOnly(a_parent)
{

}

sak::Outliner_Header_Textures::~Outliner_Header_Textures() = default;

sak::Project& sak::Outliner_Header_Textures::get_project()
{
    return static_cast<Outliner_Project*>(get_parent())->get_project();
}

sak::Project const& sak::Outliner_Header_Textures::cget_project() const
{
    return static_cast<Outliner_Project const*>(get_parent())->cget_project();
}


// Virtuals
//============================================================
QVariant sak::Outliner_Header_Textures::v_get_data(int a_role) const
{
    if (a_role == Qt::DisplayRole)
    {
        return QVariant(u8"Textures");
    }
    else
    {
        return QVariant(QString::fromUtf8(u8"Textures FUCK UP"));
    }
}

void sak::Outliner_Header_Textures::v_custom_context_menu(QAbstractItemView* a_view, qtlib::Outliner_Model* a_model, QPoint const& a_position)
{
    return this->Outliner_Item::v_custom_context_menu(a_view, a_model,a_position);
}
