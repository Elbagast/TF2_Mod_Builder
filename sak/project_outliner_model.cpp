#include "project_outliner_model.h"

#include <QModelIndex>
#include <QString>
#include <cassert>
#include <vector>
#include "project.h"
#include <QDebug>
#include <cstring>

namespace
{
    enum class Location : char
    {
        Invalid = 0,
        Root,
        Project,
        Header,
        Component
    };

    enum class Component : char
    {
        Invalid = 0,
        File,
        Texture,
        Material,
        Model,
        Package,
        Release,
    };

    class Proxy
    {
    public:
        // stuff this into a void* and also extract it from one
        static std::uintptr_t pack(Proxy const& a_proxy)
        {
            std::uintptr_t l_result{0};
            std::memcpy(static_cast<void*>(&l_result), static_cast<void const*>(&a_proxy), sizeof(Proxy));
            return l_result;
        }

        static std::uintptr_t pack(Location a_location, Component a_type)
        {
            Proxy l_temp{a_location, a_type};
            std::uintptr_t l_result{0};
            std::memcpy(static_cast<void*>(&l_result), static_cast<void const*>(&l_temp), sizeof(Proxy));
            return l_result;
        }

        static Proxy unpack(std::uintptr_t a_uint)
        {
            Proxy l_result{};
            std::memcpy(static_cast<void*>(&l_result),static_cast<void const*>(&a_uint), sizeof(Proxy));
            return l_result;
        }

        Proxy():
            m_location{Location::Invalid},
            m_type{Component::Invalid}
        {}
        Proxy(Location a_location, Component a_type):
            m_location{a_location},
            m_type{a_type}
        {}

        bool is_valid() const { return m_location != Location::Invalid && m_type != Component::Invalid; }

        Location location() const { return m_location; }
        Component type() const { return m_type; }

    private:
        Location m_location;
        Component m_type;
        char m_padding[sizeof(std::uintptr_t) - sizeof(Location) - sizeof(Component)];
    };
    static_assert(sizeof(Proxy) == sizeof(std::uintptr_t),  "bad proxy size");



    Location index_location(QModelIndex const& a_index)
    {
        if (a_index.isValid())
        {
            auto l_proxy{Proxy::unpack(a_index.internalId())};
            return l_proxy.location();
        }
        else
        {
            return Location::Invalid;
        }
    }

    Component index_type(QModelIndex const& a_index)
    {
        if (a_index.isValid())
        {
            auto l_proxy{Proxy::unpack(a_index.internalId())};
            return l_proxy.type();
        }
        else
        {
            return Component::Invalid;
        }
    }


    QString header_string(Component a_type)
    {
        switch(a_type)
        {
        case Component::File:       return QString("Files");
        case Component::Texture:    return QString("Textures");
        case Component::Material:   return QString("Materials");
        case Component::Model:      return QString("Models");
        case Component::Package:    return QString("Packages");
        case Component::Release:    return QString("Releases");
        default:                    return QString("FUCK IT BROKE");
        }
    }

}

// Pimpl Data
//============================================================
class sak::Project_Outliner_Model::Implementation
{
public:
    Project& m_project;

    int project_count() const                   { return 1; }
    QString project_name_at(int /*a_row*/) const    { return m_project.name(); }

    // How many sections are active right now?
    int header_count() const                    { return 6; }

    std::vector<Component> active_headers() const
    {
        std::vector<Component> l_result{};
        l_result.reserve(6);
        //if (file_count() != 0)
            l_result.push_back(Component::File);
        //if (texture_count() != 0)
            l_result.push_back(Component::Texture);
        //if (material_count() != 0)
            l_result.push_back(Component::Material);
        //if (model_count() != 0)
            l_result.push_back(Component::Model);
        //if (package_count() != 0)
            l_result.push_back(Component::Package);
        //if (release_count() != 0)
            l_result.push_back(Component::Release);
        return l_result;
    }


    // What header is at this row?
    QString header_name_at(int a_row) const
    {
        switch(a_row)
        {
        case 0: return QString::fromUtf8(u8"Files");
        case 1: return QString::fromUtf8(u8"Textures");
        case 2: return QString::fromUtf8(u8"Materials");
        case 3: return QString::fromUtf8(u8"Models");
        case 4: return QString::fromUtf8(u8"Packages");
        case 5: return QString::fromUtf8(u8"Releases");
        default: return QString::fromUtf8(u8"FUCK IT BROKE");
        }
    }

    Component header_type_at(int a_row) const
    {
        switch(a_row)
        {
        case 0: return Component::File;
        case 1: return Component::Texture;
        case 2: return Component::Material;
        case 3: return Component::Model;
        case 4: return Component::Package;
        case 5: return Component::Release;
        default: return Component::Invalid;
        }
    }

    // What row is this header at?
    int header_row(Component a_type) const
    {
        int l_result{0};
        for (auto l_type : active_headers())
        {
            if (a_type == l_type)
            {
                return l_result;
            }
            ++l_result;
        }
        return -1;
    }

    // How many of a given component is active?
    int component_count(Component a_type) const
    {
        switch(a_type)
        {
        case Component::File:       return file_count();
        case Component::Texture:    return texture_count();
        case Component::Material:   return material_count();
        case Component::Model:      return model_count();
        case Component::Package:    return package_count();
        case Component::Release:    return release_count();
        default:                    return 0;
        }
    }

    // How many of each component are there right now?
    int file_count() const
    {
        return 3;
    }
    int texture_count() const
    {
        return 3;
    }
    int material_count() const
    {
        return 3;
    }
    int model_count() const
    {
        return 3;
    }
    int package_count() const
    {
        return 3;
    }
    int release_count() const
    {
        return 3;
    }

    // What is the name of the component at this row?
    QString component_name_at(Component a_type, int a_row) const
    {
        switch(a_type)
        {
        case Component::File:       return file_name_at(a_row);
        case Component::Texture:    return texture_name_at(a_row);
        case Component::Material:   return material_name_at(a_row);
        case Component::Model:      return model_name_at(a_row);
        case Component::Package:    return package_name_at(a_row);
        case Component::Release:    return release_name_at(a_row);
        default:                    return QString();
        }
    }

    QString file_name_at(int a_row) const
    {
        return QString("File").append(QString::number(a_row));
    }
    QString texture_name_at(int a_row) const
    {
        return QString("Texture").append(QString::number(a_row));
    }
    QString material_name_at(int a_row) const
    {
        return QString("Material").append(QString::number(a_row));
    }
    QString model_name_at(int a_row) const
    {
        return QString("Model").append(QString::number(a_row));
    }
    QString package_name_at(int a_row) const
    {
        return QString("Package").append(QString::number(a_row));
    }
    QString release_name_at(int a_row) const
    {
        return QString("Release").append(QString::number(a_row));
    }

    Implementation(Project& a_project):
        m_project{a_project}
    {
    }
};

// Special 6
//============================================================
sak::Project_Outliner_Model::Project_Outliner_Model(Project& a_project, QObject* a_parent):
    QAbstractItemModel(a_parent),
    m_data{ std::make_unique<Implementation>(a_project) }
{
}
sak::Project_Outliner_Model::~Project_Outliner_Model() = default;


// Virtual Overrides
//============================================================
// Read functions
//----------------------------------------
// Get the flags for a given QModelIndex.
Qt::ItemFlags sak::Project_Outliner_Model::flags(QModelIndex const& a_index) const
{
    // If the index is invalid it is treated as the root index, thus it has no flags
    if (!a_index.isValid())
    {
        return Qt::NoItemFlags;
    }

    // find out where we are and act appropiately.
    // Since the max depth is 4 items we just chain ifs.

    switch(index_location(a_index))
    {
    case Location::Root:        return Qt::NoItemFlags;
    case Location::Project:     return Qt::NoItemFlags | Qt::ItemIsSelectable;
    case Location::Header:      return Qt::NoItemFlags | Qt::ItemIsSelectable;
    case Location::Component:   return Qt::NoItemFlags | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    default:                    return Qt::NoItemFlags;
    }
}
// Get the data for the Outliner_Item at a given QModelIndex.
QVariant sak::Project_Outliner_Model::data(QModelIndex const& a_index, int role) const
{
    // if index is valid
    if (a_index.isValid()
        && role == Qt::DisplayRole
        && a_index.column() == 0)
    {
        auto l_proxy{Proxy::unpack(a_index.internalId())};

        switch(l_proxy.location())
        {
        case Location::Project:     return QVariant(cimp().m_project.name());
        case Location::Header:      return QVariant(cimp().header_name_at(a_index.row()));
        case Location::Component:   return QVariant(cimp().component_name_at(l_proxy.type(), a_index.row()));
        default:                    return QVariant();
        }
    }
    else
    {
        return QVariant();
    }
}
// The number of rows (children) the ProxyID at a given QModelIndex has.
int sak::Project_Outliner_Model::rowCount(QModelIndex const& a_index) const
{
    qDebug() << "rowCount";
    // If the index is invalid it is treated as the root index, thus it has 1 row
    if (!a_index.isValid())
    {
        return 1;
    }
    // since the index is valid here, it has a proxy in it.
    auto l_proxy{Proxy::unpack(a_index.internalId())};

    switch(l_proxy.location())
    {
    case Location::Project:     return cimp().header_count(); // number of headers active
    case Location::Header:      return cimp().component_count(l_proxy.type()); // number of components under this header
    default:                    return 0; // nothing else has children
    }
}
// The number of columns (children) the item at a given QModelIndex has,
// but this just returns 1 as there is only one column.
int sak::Project_Outliner_Model::columnCount(QModelIndex const& /*parent*/) const
{
    qDebug() << "columnCount";
    return 1;
}

// Write functions
// This is used to edit the data structure with or without a delegate installed.
bool sak::Project_Outliner_Model::setData(QModelIndex const& a_index, QVariant const& a_value, int a_role)
{
    // if index is valid and the role is editing, edit the data and return true
    if (a_index.isValid() && a_role == Qt::EditRole)
    {
        auto l_proxy{Proxy::unpack(a_index.internalId())};

        if (l_proxy.location() == Location::Component)
        {
            bool l_edited{false};
            switch(l_proxy.type())
            {
            case Component::File:
                {
                    // set the name
                    l_edited = true;
                    break;
                }
            case Component::Texture:
                {
                    // set the name
                    l_edited = true;
                    break;
                }
            case Component::Material:
                {
                    // set the name
                    l_edited = true;
                    break;
                }
            case Component::Model:
                {
                    // set the name
                    l_edited = true;
                    break;
                }
            case Component::Package:
                {
                    // set the name
                    l_edited = true;
                    break;
                }
            case Component::Release:
                {
                    // set the name
                    l_edited = true;
                    break;
                }
            default: break;
            }
            if(l_edited)
            {
                // Emit a signal to tell attatched views that the data has changed at this index
                emit QAbstractItemModel::dataChanged(a_index, a_index);
                return true;
            }
        }
    }

    // edit conditions not met so return false
    return false;
}

/*
bool sak::Project_Outliner_Model::insertRows(int row, int count, QModelIndex const& parent)
{
    if (parent.isValid())
    {
        emit beginInsertRows(parent, row, row+count);
        // do stuff
        emit endInsertRows();
        return true;
    }
    else
        return false;
}
bool sak::Project_Outliner_Model::removeRows(int row, int count, QModelIndex const& parent)
{
    if (parent.isValid())
    {
        emit beginRemoveRows(parent, row, row+count);
        // do stuff
        emit endInsertRows();
        return true;
    }
    else
        return false;
}
*/
// Indexing
//----------------------------------------
// Get the index of the item at the given position

QModelIndex sak::Project_Outliner_Model::index(int a_row, int a_column, QModelIndex const& a_parent) const
{
    qDebug() << "index: "<< a_row << " " << a_column << " " << a_parent;

    // this asks it a_parent has enough rows and columns to exist
    if (!hasIndex(a_row, a_column, a_parent))
    {
        qDebug() << "index doesn't exist";
        return QModelIndex();
    }

    if (!a_parent.isValid())
    {
        qDebug() << "parent is invalid thus this is a project";
        // Then this index represents a Project
        if (a_row == 0 && a_column == 0)
        {
            qDebug() << "pack proxy";
            auto l_proxy{Proxy::pack(Location::Project, Component::Invalid)};
            qDebug() << "make project qmodelindex";
            return QAbstractItemModel::createIndex(a_row, 0, l_proxy);
        }
        else
        {
            qDebug() << "BROKE";
            return QModelIndex();
        }
    }


    // since parent is valid it should have a proxy in it.
    auto l_parent_proxy{Proxy::unpack(a_parent.internalId())};
    auto l_parent_location{l_parent_proxy.location()};
    auto l_parent_type{l_parent_proxy.type()};

    switch(l_parent_location)
    {
    case Location::Header:
        {
            qDebug() << "header";
            if (a_row < cimp().header_count() && a_column == 0)
            {
                qDebug() << "pack proxy";
                auto l_proxy{Proxy::pack(Location::Header, cimp().header_type_at(a_row))};
                qDebug() << "make project qmodelindex of header";
                return QAbstractItemModel::createIndex(a_row, 0, l_proxy);
            }
            else
            {
                qDebug() << "BROKE";
                return QModelIndex();
            }
        }
    case Location::Component:
        {
            qDebug() << "component";
            if (a_row < cimp().component_count(l_parent_type) && a_column == 0)
            {
                qDebug() << "pack proxy";
                auto l_proxy{Proxy::pack(Location::Project, l_parent_type)};
                qDebug() << "make project qmodelindex of header";
                return QAbstractItemModel::createIndex(a_row, 0, l_proxy);
            }
            else
            {
                qDebug() << "BROKE";
                return QModelIndex();
            }
        }
    default: return QModelIndex();

    }

    // if parent is the root
    if (!l_parent_proxy.is_valid())
    {
        qDebug() << "parent is invalid thus this is a project";
        // Then this index represents a Project
        if (a_row == 0 && a_column == 0)
        {
            qDebug() << "pack proxy";
            auto l_proxy{Proxy::pack(Location::Project, Component::Invalid)};
            qDebug() << "make project qmodelindex";
            return QAbstractItemModel::createIndex(a_row, 0, l_proxy);
        }
    }

    // No conditions were met
    return QModelIndex();
}
// Get the index of the parent of the item at a given index
QModelIndex sak::Project_Outliner_Model::parent(QModelIndex const& a_index) const
{
    qDebug() << "parent of: "<< a_index;

    // if the index is nonsense the return the root
    if (!a_index.isValid())
    {
        return QModelIndex();
    }

    Proxy l_proxy{ Proxy::unpack(a_index.internalId()) };
    assert(a_index.internalId() == Proxy::pack(l_proxy));

    auto l_index_location{l_proxy.location()};
    auto l_index_type{l_proxy.type()};

    // if the indexid is root
    if (!l_proxy.is_valid())
    {
        // then return a root index as the parent
        return QModelIndex();
    }
    else
    {
        switch(l_index_location)
        {
        case Location::Project:     return QModelIndex();
        case Location::Header:      return QAbstractItemModel::createIndex(0, 0, Proxy::pack(Location::Project, Component::Invalid));
        case Location::Component:   return QAbstractItemModel::createIndex(cimp().header_row(l_proxy.type()), 0, Proxy::pack(Location::Header, l_index_type));
        default:                    return QModelIndex();
        }
    }

    return QModelIndex();
}
/*
// Custom Access
//============================================================
// Make a QModelIndex of this item by searching through the model until a postition is found that matches this
QModelIndex sak::Project_Outliner_Model::make_index_of(ElementID const& elementid) const
{
    return make_index_of(ProxyID(elementid));
}
QModelIndex sak::Project_Outliner_Model::make_index_of(AttributeID const& attributeid) const
{
    return make_index_of(ProxyID(attributeid));
}
QModelIndex sak::Project_Outliner_Model::make_index_of(ProxyID const& proxyid) const
{
    size_type target_match{ProxyID::pack(proxyid)};

    // if supplied with an invalid input, return a root index
    if (!proxyid.is_valid())
    {
        return QModelIndex();
    }
    // This is going to be slooooooooow
    QModelIndex root_index{};
    return make_index_of(root_index, target_match);

    // This is a candidate for another way of doing this -> maybe make a list of ProxyID that form an ownership chain to the target?
}
QModelIndex sak::Project_Outliner_Model::make_index_of(QModelIndex const& parent, size_type proxyid_value) const
{
    for (int row = 0, end = rowCount(parent); row != end; ++row)
    {
        QModelIndex next_index{index(row, 0, parent)};
        assert(next_index.isValid());
        if (next_index.internalId() == proxyid_value)
        {
            return next_index;
        }
        else
        {
            // recurse through children
            return make_index_of(next_index, proxyid_value);
        }
    }

    auto proxyid = ProxyID::unpack(proxyid_value);
    if (proxyid.is_element())
        qDebug() << "Project_Outliner_Model::make_index_of -> ElementID not found: " << proxyid.elementid_value();
    else if (proxyid.is_element())
        qDebug() << "Project_Outliner_Model::make_index_of -> AttributeID not found: " << proxyid.elementid_value() << ":" << proxyid.attribute_index();

    return QModelIndex();
}

void sak::Project_Outliner_Model::child_indexes(std::vector<QModelIndex>& results, QModelIndex const& parent) const
{
    int row_count = this->rowCount(parent);
    for (int row = 0; row != row_count; ++row)
    {
        auto child_index = this->index(row,0,parent);
        results.push_back(child_index);
        if (this->rowCount(child_index) > 0)
            child_indexes(results, child_index);
    }
}

std::vector<QModelIndex> sak::Project_Outliner_Model::all_indexes() const
{
    std::vector<QModelIndex> result{};
    child_indexes(result, QModelIndex());
    return result;
}

// Return true if make_index_of returns a valid, non-root QModelIndex
bool sak::Project_Outliner_Model::has_index_of(ElementID const& elementid) const
{
    return make_index_of(elementid) != QModelIndex();
}
bool sak::Project_Outliner_Model::has_index_of(AttributeID const& attributeid) const
{
    return make_index_of(attributeid) != QModelIndex();
}
bool sak::Project_Outliner_Model::has_index_of(ProxyID const& proxyid) const
{
    return make_index_of(proxyid) != QModelIndex();
}

// Reset the entire model
void sak::Project_Outliner_Model::update_all()
{
    beginResetModel();
    endResetModel();
}

// Update the data for a specific item
void sak::Project_Outliner_Model::update_item(ElementID const& elementid)
{
    auto index = make_index_of(elementid);
    emit QAbstractItemModel::dataChanged(index, index);
}
void sak::Project_Outliner_Model::update_item(AttributeID const& attributeid)
{
    // This just updates the text in this index...
    auto index = make_index_of(attributeid);
    emit QAbstractItemModel::dataChanged(index, index);
}

// Update the data for a specific item's children
void sak::Project_Outliner_Model::update_children(ElementID const& elementid)
{
    auto child_count = mp_project_widget->project_manager().celement(elementid)->attribute_count();
    if (child_count > 0)
    {
        auto first_child = make_index_of(AttributeID(elementid, 0));
        auto last_child = make_index_of(AttributeID(elementid, child_count - 1));
        // Emit a signal to tell attatched views that the data has changed at this index
        emit QAbstractItemModel::dataChanged(first_child, last_child);
    }
}
void sak::Project_Outliner_Model::update_children(AttributeID const& attributeid)
{
    auto type = mp_project_widget->project_manager().attribute_type_enum(attributeid);
    if (type == Type_Enum::ElementID)
    {
        auto child_elementid = mp_project_widget->project_manager().attribute_value<ElementID>(attributeid);
        if (child_elementid.is_valid())
        {
            auto child_index = make_index_of(child_elementid);
            //assert(child_index.isValid());
            // Emit a signal to tell attatched views that the data has changed at this index
            emit QAbstractItemModel::dataChanged(child_index, child_index);
        }
    }
    else if (type == Type_Enum::Vector_ElementID)
    {
        auto const& children = mp_project_widget->project_manager().attribute_vector_vector<ElementID>(attributeid);

        if (!children.empty())
        {
            auto first_child = make_index_of(children.front());
            auto last_child = make_index_of(children.back());
            assert(first_child.isValid() && last_child.isValid());
            // Emit a signal to tell attatched views that the data has changed at this index
            emit QAbstractItemModel::dataChanged(first_child, last_child);
        }
    }
}

// Add or remove rows from Attributes
void sak::Project_Outliner_Model::add_row(AttributeID const& attributeid, int row)
{
    auto index = make_index_of(attributeid);
    this->beginInsertRows(index, row, row);
    this->endInsertRows();
}

void sak::Project_Outliner_Model::remove_row(AttributeID const& attributeid, int row)
{
    auto index = make_index_of(attributeid);
    this->beginRemoveRows(index, row, row);
    this->endRemoveRows();
}


// Request for a context menu by view at index and position
void sak::Project_Outliner_Model::custom_context_menu(QAbstractItemView* view, QModelIndex const& index, QPoint position)
{
    // indexid will be the id in the index but starts invalid
    ProxyID indexid{};

    // if the index is valid then get the id from it
    if (index.isValid())
    {
        // indexid is the id in the index
        indexid = ProxyID::unpack(index.internalId());
        assert(index.internalId() == ProxyID::pack(indexid));
    }

    // start the context menu
    QMenu menu{};
    // now fill it dependent on what this index represents

    // if the indexid is root
    if (!indexid.is_valid())
    {
        // then do the general context menu
        menu.addAction("Root Context Menu")->setEnabled(false);
        menu.addSeparator();
    }
    // else it's an Element
    else if (indexid.is_element())
    {
        auto index_elementid = indexid.elementid();
        auto menu_title = mp_project_widget->project_manager().element_name(index_elementid);

        menu.addAction(menu_title.c_str())->setEnabled(false);
        menu.addSeparator();

        // Rename this Element
        auto rename_action = menu.addAction("Rename");
        // connect the action to a lambda that calls edit in the view
        QObject::connect(rename_action, &QAction::triggered,
                         [view, &index](){ view->edit(index); });

        // Open the editor widget for this Element
        auto edit_action = menu.addAction("Edit");
        QObject::connect(edit_action, &QAction::triggered,
                         [this, index_elementid](){ this->request_editor(index_elementid); });

    }
    // else it's an Attribute
    else if (indexid.is_attribute())
    {
        auto index_attributeid = indexid.attributeid();
        auto index_elementid = index_attributeid.elementid();

        auto menu_title = mp_project_widget->project_manager().element_name(index_elementid)
                          + " : "
                          + mp_project_widget->project_manager().attribute_name(index_attributeid);

        menu.addAction(menu_title.c_str())->setEnabled(false);
        menu.addSeparator();

        // Open the editor widget for the Attribute's Element
        auto edit_action = menu.addAction("Edit");
        QObject::connect(edit_action, &QAction::triggered,
                         [this, index_elementid](){ this->request_editor(index_elementid); });

    }
    else
    {
        menu.addAction("Bad context menu request.")->setEnabled(false);
    }

    menu.exec(position);
    // Assembling the context menu is going to need some thought.
}

// Allow a view to request an editor for a given index
void sak::Project_Outliner_Model::request_editor(QModelIndex const& index)
{
    // indexid will be the id in the index but starts invalid
    ProxyID indexid{};

    // if the index is valid then get the id from it
    if (index.isValid())
    {
        // indexid is the id in the index
        indexid = ProxyID::unpack(index.internalId());
        assert(index.internalId() == ProxyID::pack(indexid));
    }

    // if the indexid is root
    if (!indexid.is_valid())
    {
        // nothing
    }
    // else it's an Element
    else if (indexid.is_element())
    {
        request_editor(indexid.elementid());
    }
    // else it's an Attribute
    else if (indexid.is_attribute())
    {
        request_editor(indexid.elementid());
    }
    else
    {
        // nothing
    }
}

// Forward this request to the Project_Manager
void sak::Project_Outliner_Model::request_editor(ElementID const& elementid)
{
    mp_project_widget->open_editor(elementid);
}

void sak::Project_Outliner_Model::begin_model_reset()
{
    this->beginResetModel();
}

void sak::Project_Outliner_Model::end_model_reset()
{
    this->endResetModel();
}
*/
