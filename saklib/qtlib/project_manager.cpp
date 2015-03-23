#include "project_manager.h"
#include "element_widget.h"
#include "outliner/outliner_model.h"

// Special 6
//============================================================
Saklib::Qtlib::Project_Manager::Project_Manager(Command_History& command_history):
    m_data_manager(),
    m_widget_manager(),
    m_outliner_model(new Outliner_Model(command_history, *this))
{}
Saklib::Qtlib::Project_Manager::~Project_Manager() = default;

// Interface
//============================================================

// Lifetime
//------------------------------------------------------------
// Make a new Element and return all info about it
Saklib::ElementID Saklib::Qtlib::Project_Manager::make_element(Command_History& command_history, String const& type)
{
    // make an element
    ElementID newid = m_data_manager.make_element(type);
    // make a widget
    Element_Widget* new_widget = m_widget_manager.make_widget(command_history, *this, newid);

    return newid;
}

// Destory an Element and everything associated with it
void Saklib::Qtlib::Project_Manager::destroy_element(ElementID elementid)
{
    m_data_manager.destroy_element(elementid);
    m_widget_manager.destroy_widget(elementid);
    //m_proxy_manager.destroy_proxy(elementid);
}

// Disconnect all Qt classes to prevent double-deletes
void Saklib::Qtlib::Project_Manager::prepare_to_die()
{
    m_widget_manager.nullify_all_parents();
}

// Does this refer to something in this? - rename these to has(blah) ?
bool Saklib::Qtlib::Project_Manager::is_valid(ElementID elementid) const
{
    return m_data_manager.is_valid(elementid);
}
bool Saklib::Qtlib::Project_Manager::is_valid(AttributeID attributeid) const
{
    return m_data_manager.is_valid(attributeid);
}
bool Saklib::Qtlib::Project_Manager::is_valid(ProxyID proxyid) const
{
    return m_data_manager.is_valid(proxyid.elementid());
}

// Data Access
//------------------------------------------------------------
//Element& element(ElementID elementid);
Saklib::Element const& Saklib::Qtlib::Project_Manager::element(ElementID elementid) const
{
    return m_data_manager.element(elementid);
}

Saklib::String const& Saklib::Qtlib::Project_Manager::element_name(ElementID elementid) const
{
    return m_data_manager.element(elementid).name();
}
Saklib::String const& Saklib::Qtlib::Project_Manager::element_type(ElementID elementid) const
{
    return m_data_manager.element(elementid).type();
}
Saklib::AttributeID Saklib::Qtlib::Project_Manager::element_parent(ElementID elementid) const
{
     return m_data_manager.parent(elementid);
}

//Saklib::Attribute *const Saklib::Qtlib::Project_Manager::attribute(AttributeID attributeid) const;
//Saklib::Attribute *const Saklib::Qtlib::Project_Manager::attribute(ElementID elementid, size_type attribute_index) const;
//Saklib::Attribute *const Saklib::Qtlib::Project_Manager::attribute(ElementID elementid, String const& attribute_name) const;

Saklib::Attribute const*const Saklib::Qtlib::Project_Manager::attribute(AttributeID attributeid) const
{
    return m_data_manager.attribute(attributeid);
}
Saklib::Attribute const*const Saklib::Qtlib::Project_Manager::attribute(ElementID elementid, size_type attribute_index) const
{
    return m_data_manager.attribute(elementid, attribute_index);
}
Saklib::Attribute const*const Saklib::Qtlib::Project_Manager::attribute(ElementID elementid, String const& attribute_name) const
{
    return m_data_manager.attribute(elementid, attribute_name);
}

Saklib::String const& Saklib::Qtlib::Project_Manager::attribute_name(AttributeID attributeid) const
{
    return m_data_manager.attribute(attributeid)->name();
}
Saklib::Type_Enum Saklib::Qtlib::Project_Manager::attribute_type_enum(AttributeID attributeid) const
{
    return m_data_manager.attribute(attributeid)->type_enum();
}
Saklib::String Saklib::Qtlib::Project_Manager::attribute_type_string(AttributeID attributeid) const
{
    return m_data_manager.attribute(attributeid)->type_string();
}

Saklib::Qtlib::Element_Widget*const Saklib::Qtlib::Project_Manager::widget(ElementID elementid) const
{
    return m_widget_manager.widget(elementid);
}
Saklib::Qtlib::Element_Widget*const Saklib::Qtlib::Project_Manager::widget(ProxyID proxyid) const
{
    return m_widget_manager.widget(proxyid.elementid());
}


// Convert ID Types
//------------------------------------------------------------
Saklib::AttributeID Saklib::Qtlib::Project_Manager::attributeid(ElementID elementid, String const& attribute_name) const
{
    return m_data_manager.attributeid(elementid, attribute_name);
}


// Flat Access
//------------------------------------------------------------
Saklib::Vector_ElementID Saklib::Qtlib::Project_Manager::all_elementids() const
{
    return m_data_manager.all_elementids();
}
Saklib::Vector_ElementID Saklib::Qtlib::Project_Manager::root_elementids() const
{
    return m_data_manager.root_elementids();
}

// Model Interface
//============================================================
// So that views can use it
Saklib::Qtlib::Outliner_Model*const Saklib::Qtlib::Project_Manager::outliner_model() const
{
    return m_outliner_model.get();
}

// What are this item's children?
Saklib::Vector_AttributeID Saklib::Qtlib::Project_Manager::outliner_children(ElementID elementid) const
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
Saklib::Vector_ElementID Saklib::Qtlib::Project_Manager::outliner_children(AttributeID attributeid) const
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
        ElementID held_elementid = attribute_enum_cast<Type_Enum::ElementID>(attributeid)->get();
        if (held_elementid.is_valid())
        {
            results.push_back(held_elementid);
        }
    }
    else if (type == Type_Enum::Vector_ElementID)
    {
        // For each stored ElementID
        auto const& elementid_vector = attribute_enum_cast<Type_Enum::Vector_ElementID>(attributeid)->vector();
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
Saklib::AttributeID Saklib::Qtlib::Project_Manager::outliner_child_at_row(ElementID elementid, int row) const
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
Saklib::ElementID Saklib::Qtlib::Project_Manager::outliner_child_at_row(AttributeID attributeid, int row) const
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
int Saklib::Qtlib::Project_Manager::outliner_row_count_root() const
{
    return root_elementids().size();
}
int Saklib::Qtlib::Project_Manager::outliner_row_count(ElementID elementid) const
{
    return outliner_children(elementid).size();
}
int Saklib::Qtlib::Project_Manager::outliner_row_count(AttributeID attributeid) const
{
    return outliner_children(attributeid).size();
}

// What is the parent of this item?
Saklib::AttributeID Saklib::Qtlib::Project_Manager::parent_of(ElementID elementid) const
{
    return m_data_manager.parent(elementid);
}
Saklib::ElementID Saklib::Qtlib::Project_Manager::parent_of(AttributeID attributeid) const
{
    return attributeid.elementid();
}

// What row is this in its parent as far as the model is concerned?
int Saklib::Qtlib::Project_Manager::outliner_row_in_parent(ElementID elementid) const
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
int Saklib::Qtlib::Project_Manager::outliner_row_in_parent(AttributeID attributeid) const
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
//============================================================
// You must only set data though these in order to keep everything in sync

void Saklib::Qtlib::Project_Manager::set_element_name(ElementID elementid, String const& value)
{
    m_data_manager.element(elementid).set_name(value);
    update_widget(elementid);
    update_model(elementid);
}

// Internal
//============================================================
void Saklib::Qtlib::Project_Manager::update_widget(ElementID elementid)
{
    m_widget_manager.widget(elementid)->refresh_data();
}
void Saklib::Qtlib::Project_Manager::update_widget(AttributeID attributeid)
{
    m_widget_manager.widget(attributeid.elementid())->refresh_data(attributeid.index());
}

void Saklib::Qtlib::Project_Manager::update_model(ElementID elementid)
{
    m_outliner_model->update_item(elementid);
}
void Saklib::Qtlib::Project_Manager::update_model(AttributeID attributeid)
{
    m_outliner_model->update_item(attributeid);
}
