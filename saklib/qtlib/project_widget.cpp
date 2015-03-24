#include "project_widget.h"

#include "../element.h"
#include "../attribute_type.h"

#include "outliner/outliner_model.h"
#include "outliner/outliner_delegate.h"
#include "outliner/outliner_treeview.h"

#include "qstring_operations.h"

#include <QHBoxLayout>
#include <QScrollArea>
#include <QLabel>

#include <cassert>

#include "../interal_element_definitions.h"

// Static Helpers
//============================================================
// Make an ElementID with the supplied manager by registering the Element type the first time
// this is run
Saklib::ElementID Saklib::Qtlib::Project_Widget::make_Project(Project_Manager& project_manager)
{
    static bool was_run{false};
    if (!was_run)
    {
        register_all_internal_definitions();
        was_run = true;
    }
    ElementID result{project_manager.make_element("Project")};
    assert(project_manager.is_valid(result));
    project_manager.set_element_name(result, "Default_Project_Name");
    return result;
}

// Special 6
//============================================================
Saklib::Qtlib::Project_Widget::Project_Widget(Path const& filepath, Project_Main_Window* parent) :
    QWidget(nullptr),
    mp_main_window{parent},
    m_project_manager{this},
    m_root_elementid{make_Project(m_project_manager)},
    m_root_filepath{m_project_manager.attributeid(m_root_elementid, "Filepath")},

    //m_outliner_manager(m_project_manager),

    m_outliner_delegate(new Outliner_Delegate(this)),

    m_outliner(new Outliner_Treeview(this)),
    m_scroll_area(new QScrollArea(this)),
    //m_editor(nullptr),

    m_layout(new QHBoxLayout(this))
{
    assert(mp_main_window != nullptr);

    // Store the filename in this attribute
    set_filepath(filepath);

    m_outliner->setModel(m_project_manager.outliner_model());
    m_outliner->setItemDelegate(m_outliner_delegate.get());

    m_project_manager.make_element("File");
    m_project_manager.make_element("SingleInt");

    // The outliner finds this...
    //make_Project(m_project_manager);

    //m_outliner->

    QObject::connect(m_project_manager.outliner_model(), &Outliner_Model::signal_editorRequestedFor,
                     this, &Project_Widget::slot_editorRequestedFor);

    m_scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    m_layout->addWidget(m_outliner.get(), 1);
    m_layout->addWidget(m_scroll_area.get(), 3);
    setLayout(m_layout.get());

    open_editor(m_root_elementid);
}
Saklib::Qtlib::Project_Widget::~Project_Widget()
{
    // Must do this to stop double-deletes
    m_project_manager.prepare_to_die();

    // Break all parenting so the Uptr can clean them up without double deletes
    //if (m_outliner_model) m_outliner_model->setParent(nullptr);
    //if (m_outliner_delegate) m_outliner_delegate->setParent(nullptr);
    if (m_outliner) m_outliner->setParent(nullptr);
    if (m_scroll_area)
    {
        m_scroll_area->setParent(nullptr);
        m_scroll_area->setWidget(nullptr);
    }
    //if (m_layout) m_layout->setParent(nullptr);
}


// Interface
//============================================================

Saklib::Path const& Saklib::Qtlib::Project_Widget::filepath() const
{
    //emit signal_toConsole("Project_Widget::filepath()");

    return m_project_manager.attribute_type_cast<Path>(m_root_filepath)->get();
}
void Saklib::Qtlib::Project_Widget::set_filepath(Path const& filepath)
{
    m_project_manager.set_attribute_type<Path>(m_root_filepath, filepath);
    m_project_manager.set_element_name(m_root_elementid, Saklib::to_String(filepath.filename()));
    // if there is an editor for this element, update its name label
}

void Saklib::Qtlib::Project_Widget::save() const
{
    //emit signal_toConsole("Project_Widget::save()");

    //serialiseProjectToFile(m_project, m_filepath);
    emit signal_unsavedEdits(false);
}
void Saklib::Qtlib::Project_Widget::save_as(Path const& filepath)
{
    set_filepath(filepath);
    save();
}

//void Saklib::Qtlib::Project_Widget::reload();

// Open an Element_Widget for this Element
void Saklib::Qtlib::Project_Widget::open_editor(ElementID elementid)
{
    // Get the currently set editor
    auto old_editor = dynamic_cast<Element_Widget*>(m_scroll_area->widget());


    // if the editor is nullptr or not for the same ElementID
    if (old_editor == nullptr
        || old_editor->elementid() != elementid)
    {
        // break the ownership
        old_editor = dynamic_cast<Element_Widget*>(m_scroll_area->takeWidget());

        // change the editor
        auto new_editor = m_project_manager.widget(elementid);

        m_scroll_area->setWidget(new_editor);
        m_scroll_area->setWidgetResizable(true);
    }
}




// Slots
//============================================================
void Saklib::Qtlib::Project_Widget::slot_editorRequestedFor(ElementID elementid)
{
    open_editor(elementid);
}
/*
void Saklib::Qtlib::Project_Widget::slot_unsavedEdits(bool state) const
{
    QString message{"Project_Widget::slot_unsavedEdits( "};
    message.append(state ? "true" : "false");
    message.append(" )");
    emit signal_toConsole(message);

    emit signal_unsavedEdits(state);
}
*/
