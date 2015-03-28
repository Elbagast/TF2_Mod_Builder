#include "project_widget.h"

#include "../element.h"
#include "../attribute_type.h"

#include "element_widget.h"

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
Saklib::ElementID Saklib::Qtlib::Project_Widget::make_Project(Element_Manager& element_manager)
{
    static bool was_run{false};
    if (!was_run)
    {
        register_all_internal_definitions();
        was_run = true;
    }
    ElementID result{element_manager.make_element("Project")};
    assert(element_manager.is_valid(result));
    element_manager.element(result).set_name("Default_Project_Name");
    return result;
}


// Special 6
//============================================================
Saklib::Qtlib::Project_Widget::Project_Widget(Path const& filepath, QWidget* parent) :
    QWidget(parent),
    m_element_manager{},
    m_command_history{},

    m_outliner_model(new Outliner_Model(this)),
    m_outliner_delegate(new Outliner_Delegate(this)),

    m_project_elementid{make_Project(m_element_manager)},
    m_project_filepath{m_element_manager.attributeid(m_project_elementid, "Filepath")},

    m_outliner(new Outliner_Treeview(this)),
    m_scroll_area(new QScrollArea(this)),
    m_editor(nullptr),

    m_layout(new QHBoxLayout(this))
{
    // Store the filename in this attribute
    set_project_filepath(filepath);

    m_outliner->setModel(m_outliner_model.get());
    m_outliner->setItemDelegate(m_outliner_delegate.get());

    // TESTING LINES
    m_element_manager.make_element("File");
    m_element_manager.make_element("SingleInt");
    auto test_child =  this->make_element("SingleInt");
    auto parent_attribute = this->attributeid(m_project_elementid, "TestElement");
    attribute_set_value(parent_attribute, test_child);



    // Does this need to be a signal?
    //QObject::connect(m_outliner_model.get, &Outliner_Model::signal_editorRequestedFor,
     //                this, &Project_Widget::slot_editorRequestedFor);

    m_scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    m_layout->addWidget(m_outliner.get(), 1);
    m_layout->addWidget(m_scroll_area.get(), 3);
    setLayout(m_layout.get());

    open_editor(m_project_elementid);
}
Saklib::Qtlib::Project_Widget::~Project_Widget()
{
    // Break all parenting so the Uptr can clean them up without double deletes
    //if (m_outliner_model) m_outliner_model->setParent(nullptr);
    //if (m_outliner_delegate) m_outliner_delegate->setParent(nullptr);
    if (m_outliner) m_outliner->setParent(nullptr);
    if (m_scroll_area)
    {
        m_scroll_area->setParent(nullptr);
        m_scroll_area->setWidget(nullptr);
    }
    if (m_editor) m_editor->setParent(nullptr);
    //if (m_layout) m_layout->setParent(nullptr);
}



// Interface
//============================================================

// Lifetime
//------------------------------------------------------------
// Make a new Element and return all info about it
Saklib::ElementID Saklib::Qtlib::Project_Widget::make_element(String const& type)
{
    // make an element
    ElementID newid = m_element_manager.make_element(type);
    return newid;
}

// Destory an Element and everything associated with it
void Saklib::Qtlib::Project_Widget::destroy_element(ElementID elementid)
{
    m_element_manager.destroy_element(elementid);
    if (m_editor && m_editor->elementid() == elementid)
    {
        m_editor.reset();
    }
}

// Does this refer to something in this? - rename these to has(blah) ?
bool Saklib::Qtlib::Project_Widget::is_valid(ElementID elementid) const
{
    return m_element_manager.is_valid(elementid);
}
bool Saklib::Qtlib::Project_Widget::is_valid(AttributeID attributeid) const
{
    return m_element_manager.is_valid(attributeid);
}
bool Saklib::Qtlib::Project_Widget::is_valid(ProxyID proxyid) const
{
    return m_element_manager.is_valid(proxyid.elementid());
}

// Data Access
//------------------------------------------------------------
Saklib::Element const& Saklib::Qtlib::Project_Widget::element(ElementID elementid) const
{
    return m_element_manager.element(elementid);
}

Saklib::String const& Saklib::Qtlib::Project_Widget::element_name(ElementID elementid) const
{
    return m_element_manager.element(elementid).name();
}
Saklib::String const& Saklib::Qtlib::Project_Widget::element_type(ElementID elementid) const
{
    return m_element_manager.element(elementid).type();
}
Saklib::AttributeID Saklib::Qtlib::Project_Widget::element_parent(ElementID elementid) const
{
     return m_element_manager.parent(elementid);
}

Saklib::Attribute const*const Saklib::Qtlib::Project_Widget::attribute(AttributeID attributeid) const
{
    return m_element_manager.attribute(attributeid);
}
Saklib::Attribute const*const Saklib::Qtlib::Project_Widget::attribute(ElementID elementid, size_type attribute_index) const
{
    return m_element_manager.attribute(elementid, attribute_index);
}
Saklib::Attribute const*const Saklib::Qtlib::Project_Widget::attribute(ElementID elementid, String const& attribute_name) const
{
    return m_element_manager.attribute(elementid, attribute_name);
}

Saklib::String const& Saklib::Qtlib::Project_Widget::attribute_name(AttributeID attributeid) const
{
    return m_element_manager.attribute(attributeid)->name();
}
Saklib::Type_Enum Saklib::Qtlib::Project_Widget::attribute_type_enum(AttributeID attributeid) const
{
    return m_element_manager.attribute(attributeid)->type_enum();
}
Saklib::String Saklib::Qtlib::Project_Widget::attribute_type_string(AttributeID attributeid) const
{
    return m_element_manager.attribute(attributeid)->type_string();
}

// if the attribute is a vector, return it's size, otherwise 0
Saklib::size_type Saklib::Qtlib::Project_Widget::attribute_vector_size(AttributeID attributeid) const
{
    auto attribute_type = attribute_type_enum(attributeid);
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        return attribute_type_cast<Vector_Bool>(attributeid)->size();
    case Type_Enum::Vector_Int:         return attribute_type_cast<Vector_Int>(attributeid)->size();
    case Type_Enum::Vector_Double:      return attribute_type_cast<Vector_Double>(attributeid)->size();
    case Type_Enum::Vector_String:      return attribute_type_cast<Vector_String>(attributeid)->size();
    case Type_Enum::Vector_Path:        return attribute_type_cast<Vector_Path>(attributeid)->size();
    case Type_Enum::Vector_ElementID:   return attribute_type_cast<Vector_ElementID>(attributeid)->size();
    default: return 0;
    }
}

// Convert ID Types
//------------------------------------------------------------
Saklib::AttributeID Saklib::Qtlib::Project_Widget::attributeid(ElementID elementid, String const& attribute_name) const
{
    return m_element_manager.attributeid(elementid, attribute_name);
}


// Flat Access
//------------------------------------------------------------
Saklib::Vector_ElementID Saklib::Qtlib::Project_Widget::all_elementids() const
{
    return m_element_manager.all_elementids();
}
Saklib::Vector_ElementID Saklib::Qtlib::Project_Widget::root_elementids() const
{
    return m_element_manager.root_elementids();
}

// Model Interface
//------------------------------------------------------------
// Functions that provide data to the outliner model

// What are this item's children?
Saklib::Vector_AttributeID Saklib::Qtlib::Project_Widget::outliner_children(ElementID elementid) const
{
    // Assuming a valid ElementID...
    Vector_AttributeID results{};

    // For each Attribute by index
    auto const& attributes = element(elementid).attributes();
    for(size_type index = 0, end = attributes.size(); index != end; ++index)
    {
        // If the type is of interest
        Type_Enum type{attributes.at(index)->type_enum()};
        if (type == Type_Enum::ElementID || type == Type_Enum::Vector_ElementID)
        {
            results.push_back(AttributeID(elementid, index));
        }
    }

    return results;
}
Saklib::Vector_ElementID Saklib::Qtlib::Project_Widget::outliner_children(AttributeID attributeid) const
{
    // Assuming a valid AttributeID...
    Vector_ElementID results{};

    // If invalid get the root children
    if (!attributeid.is_valid())
    {
        return root_elementids();
    }

    Type_Enum type{attribute_type_enum(attributeid)};
    if (type == Type_Enum::ElementID)
    {
        // Get the ElementID held
        ElementID held_elementid = attribute_type_cast<ElementID>(attributeid)->value();
        if (held_elementid.is_valid())
        {
            results.push_back(held_elementid);
        }
    }
    else if (type == Type_Enum::Vector_ElementID)
    {
        // For each stored ElementID
        auto const& elementid_vector = attribute_type_cast<Vector_ElementID>(attributeid)->vector();
        for(auto elementid : elementid_vector)
        {
            if (elementid.is_valid())
            {
                results.push_back(elementid);
            }
        }
    }
    else
    {
        // ignore other Attribute types
    }

    return results;
}

// What item is the child at row?
Saklib::AttributeID Saklib::Qtlib::Project_Widget::outliner_child_at_row(ElementID elementid, int row) const
{
    auto children = outliner_children(elementid);
    auto unsigned_row = static_cast<size_type>(row);
    if (row >=0 && unsigned_row < children.size())
    {
        return children.at(unsigned_row);
    }
    else
    {
        return invalid_attributeid();
    }
}
Saklib::ElementID Saklib::Qtlib::Project_Widget::outliner_child_at_row(AttributeID attributeid, int row) const
{
    auto children = outliner_children(attributeid);
    auto unsigned_row = static_cast<size_type>(row);
    if (row >=0 && unsigned_row < children.size())
    {
        return children.at(unsigned_row);
    }
    else
    {
        return invalid_elementid();
    }
}

// How many rows does this item have?
int Saklib::Qtlib::Project_Widget::outliner_row_count_root() const
{
    return root_elementids().size();
}
int Saklib::Qtlib::Project_Widget::outliner_row_count(ElementID elementid) const
{
    return outliner_children(elementid).size();
}
int Saklib::Qtlib::Project_Widget::outliner_row_count(AttributeID attributeid) const
{
    return outliner_children(attributeid).size();
}

// What is the parent of this item?
Saklib::AttributeID Saklib::Qtlib::Project_Widget::parent_of(ElementID elementid) const
{
    return m_element_manager.parent(elementid);
}
Saklib::ElementID Saklib::Qtlib::Project_Widget::parent_of(AttributeID attributeid) const
{
    return attributeid.elementid();
}

// What row is this in its parent as far as the model is concerned?
int Saklib::Qtlib::Project_Widget::outliner_row_in_parent(ElementID elementid) const
{
    auto parent = parent_of(elementid);
    auto siblings = outliner_children(parent);
    int row = 0;
    for (auto sibling : siblings)
    {
        if (sibling == elementid)
        {
            return row;
        }
        ++row;
    }
    return 0;
}
int Saklib::Qtlib::Project_Widget::outliner_row_in_parent(AttributeID attributeid) const
{
    auto parent = parent_of(attributeid);
    auto siblings = outliner_children(parent);
    int row = 0;
    for (auto sibling : siblings)
    {
        if (sibling == attributeid)
        {
            return row;
        }
        ++row;
    }
    return 0;
}

// Data Setters
//------------------------------------------------------------
// You must only set data though these in order to keep everything in sync. These setters will issue
// appropriate commands as necessary and return true if a change was actually made to data.

void Saklib::Qtlib::Project_Widget::element_set_name(ElementID elementid, String const& value)
{
    assert(is_valid(elementid));
    // maintaining unique names should have been done before getting here

    m_element_manager.element(elementid).set_name(value);
    update_widget(elementid);
    update_model(elementid);
    emit signal_unsaved_edits(true);
}

template <>
void Saklib::Qtlib::Project_Widget::attribute_set_value(AttributeID attributeid, ElementID  const& value)
{
    assert(attributeid.is_valid());
    assert(this->attribute_type_enum(attributeid) == Type_Traits<ElementID>::type_enum());
    //assert(this->attribute_type_cast<ElementID>(attributeid)->value() != value);

    ElementID old_value = m_element_manager.element(attributeid.elementid()).attribute_type_cast<ElementID>(attributeid.index())->value();

    m_element_manager.element(attributeid.elementid()).attribute_type_cast<ElementID>(attributeid.index())->set_value(value);

    m_element_manager.set_parent(old_value, invalid_attributeid());
    m_element_manager.set_parent(value, attributeid);

    update_widget(attributeid);
    //update_model(attributeid);

    // need to do the following...

    // if the ElementID changed from invalid to valid,
    if (!old_value.is_valid() && value.is_valid())
    {
        // tell the model that row 0 was added as a child of attributeid
        m_outliner_model->add_row(attributeid, 0);
        //m_outliner->setExpanded(m_outliner_model->make_index_of(value), true);
        //m_outliner->setExpanded(m_outliner_model->make_index_of(attributeid.elementid()), true);
    }
    // else if the ElementID changed from valid to invalid,
    else if (old_value.is_valid() && !value.is_valid())
    {
        // tell the model that row 0 was removed as a child of attributeid
        m_outliner_model->remove_row(attributeid, 0);
        //m_outliner->setExpanded(m_outliner_model->make_index_of(attributeid.elementid()), true);
    }
    else
    {
        // tell the model to update the children of attributeid
        m_outliner_model->update_children(attributeid);
    }

    //m_outliner_model->update_children(attributeid); // doesn't work...

    //m_outliner_model->update_all(); // using this shows everything is there
    emit signal_unsaved_edits(true);
}


void Saklib::Qtlib::Project_Widget::attribute_vector_push_back(AttributeID attributeid, ElementID const& value)
{
    verify_attribute<ElementID>(attributeid);

    auto attribute =  m_element_manager.element(attributeid.elementid()).attribute_type_cast<Vector_ElementID>(attributeid.index());

    auto old_size = attribute->size();

    attribute->push_back(value);
    m_element_manager.set_parent(value, attributeid);

    update_widget(attributeid);
    update_model(attributeid);

    m_outliner_model->add_row(attributeid, old_size);
    emit signal_unsaved_edits(true);
}

void Saklib::Qtlib::Project_Widget::attribute_vector_pop_back_ElementID(AttributeID attributeid)
{
    verify_attribute<ElementID>(attributeid);

    auto attribute =  m_element_manager.element(attributeid.elementid()).attribute_type_cast<Vector_ElementID>(attributeid.index());

    auto removed_value = attribute->back();
    auto old_size = attribute->size();

    attribute->pop_back();
    m_element_manager.set_parent(removed_value, invalid_attributeid());

    update_widget(attributeid);
    update_model(attributeid);

    m_outliner_model->remove_row(attributeid, old_size - 1);
    emit signal_unsaved_edits(true);
}

// Commands - indirect write access
//------------------------------------------------------------
// To support undoing edits use these functions to edit data from the outliner/widgets.

bool Saklib::Qtlib::Project_Widget::undoable_element_set_name(ElementID elementid, String const& value)
{
    // if conditions are right to issue a command
    if(elementid.is_valid()
       && this->is_valid(elementid)
       && this->element_name(elementid) != value)
    {
        // do it. The command should call the update_... function(s) when it is executed/unexecuted
        m_command_history.emplace_execute<PWC_Element_Set_Name>(this, elementid, value);
        command_history_changed();
        return true;
    }
    else
    {
        return false;
    }
}

// Command History
//------------------------------------------------------------
// Provide limited access to the underlying history
//Command_History const& command_history() const;

// Will calling undo do anything?
bool Saklib::Qtlib::Project_Widget::can_undo() const
{
    return m_command_history.can_undo();
}

// Will calling redo do anything?
bool Saklib::Qtlib::Project_Widget::can_redo() const
{
    return m_command_history.can_redo();
}

// How many times can undo() be called()?
Saklib::size_type Saklib::Qtlib::Project_Widget::undo_count() const
{
    return m_command_history.undo_count();
}

// How many times can redo() be called()?
Saklib::size_type Saklib::Qtlib::Project_Widget::redo_count() const
{
    return m_command_history.redo_count();
}

// Call unexecute() in the current command and step back one in the history.
void Saklib::Qtlib::Project_Widget::undo()
{
    m_command_history.undo();
    command_history_changed();
}

// Step forward one in the history and call execute() on that command.
void Saklib::Qtlib::Project_Widget::redo()
{
    m_command_history.redo();
    command_history_changed();
}

// Clear all stored commands.
void Saklib::Qtlib::Project_Widget::clear_history()
{
    m_command_history.clear();
    command_history_changed();
}

// Call whenever commands are issued or called
void Saklib::Qtlib::Project_Widget::command_history_changed()
{
    emit signal_update_undo_actions(m_command_history.undo_count(), m_command_history.redo_count());
}

// Element Widget
//------------------------------------------------------------
// Alter the Element currently being edited

// Make an Element_Widget for this ElementID
void Saklib::Qtlib::Project_Widget::open_editor(ElementID elementid)
{
    // if the editor isn't set or it is and is for a different ElementID
    if (!m_editor || m_editor->elementid() != elementid)
    {
        // Replace it with a new Element_Widget
        m_editor = std::make_unique<Element_Widget>(this, elementid);
        m_scroll_area->setWidget(m_editor.get());
    }
}

// The ElementID of the Element that is currently being edited
Saklib::ElementID Saklib::Qtlib::Project_Widget::currently_open_elementid() const
{
    if (m_editor)
        return m_editor->elementid();
    else
        return invalid_elementid();
}

// Overall Project
//------------------------------------------------------------
Saklib::ElementID Saklib::Qtlib::Project_Widget::project_elementid() const
{
    return m_project_elementid;
}
Saklib::Path const& Saklib::Qtlib::Project_Widget::project_filepath() const
{
    return Saklib::attribute_type_cast<Path>(m_element_manager.attribute(m_project_filepath))->value();
}
void Saklib::Qtlib::Project_Widget::set_project_filepath(Path const& filepath)
{
    m_element_manager.element(m_project_elementid).set_name(Saklib::to_String(filepath.filename()));
    Saklib::attribute_type_cast<Path>(m_element_manager.attribute(m_project_filepath))->set_value(filepath);
}

void Saklib::Qtlib::Project_Widget::save() const
{
    emit signal_unsaved_edits(false);
}
void Saklib::Qtlib::Project_Widget::save_as(Path const& filepath)
{
    set_project_filepath(filepath);
    save();
}


// Internal
//============================================================
void Saklib::Qtlib::Project_Widget::update_widget(ElementID elementid)
{
    // if the ElementID is valid and editor is valid and is for a this ElementID
    if (m_element_manager.is_valid(elementid)
        && m_editor
        && m_editor->elementid() == elementid)
    {
        m_editor->refresh_data();
    }
}
void Saklib::Qtlib::Project_Widget::update_widget(AttributeID attributeid)
{
    // if the AttributeID is valid and editor is valid and is for a this AttributeID's ElementID
    if (m_element_manager.is_valid(attributeid)
        && m_editor
        && m_editor->elementid() == attributeid.elementid())
    {
        m_editor->refresh_data(attributeid.index());
    }
}

void Saklib::Qtlib::Project_Widget::update_model(ElementID elementid)
{
    m_outliner_model->update_item(elementid);
}
void Saklib::Qtlib::Project_Widget::update_model(AttributeID attributeid)
{
    m_outliner_model->update_item(attributeid);
}
