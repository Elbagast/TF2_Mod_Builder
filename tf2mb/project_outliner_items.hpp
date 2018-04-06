#ifndef SAK_PROJECT_OUTLINER_ITEMS_HPP
#define SAK_PROJECT_OUTLINER_ITEMS_HPP

#ifndef SAK_PROJECT_OUTLINER_ITEMS_FWD_HPP
#include "project_outliner_items_fwd.hpp"
#endif

#ifndef SAK_PROJECT_FWD_HPP
#include "project_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_OUTLINER_TRUNK_ITEM_HPP
#include "abstract_outliner_trunk_item.hpp"
#endif

#ifndef SAK_ABSTRACT_OUTLINER_LEAF_ITEM_HPP
#include "abstract_outliner_leaf_item.hpp"
#endif

#ifndef SAK_ENTITY_ID_HPP
#include <sak/entity_id.hpp>
#endif
/*
namespace sak
{
  //---------------------------------------------------------------------------
  // Outliner_Root_Item
  //---------------------------------------------------------------------------
  // Outliner root item for a single project. This item is invisible and
  // defines the default context menu.

  // For a single instance of the template declaration.
  namespace internal
  {
    using Outliner_Project_Item_Base =
    Abstract_Outliner_Root_Trunk_Item<Outliner_Project_Item>;
  }

  class Outliner_Root_Item :
      public internal::Outliner_Project_Item_Base
  {
  private:
    // Member Data
    //============================================================
    Project* m_project;

  public:
    // Special 6
    //============================================================
    explicit Outliner_Root_Item(Project* a_project);
    ~Outliner_Root_Item() override final;

    // Virtual Interface
    //============================================================
    // Other
    //----------------------------------------
    // Make and act on the context menu for this item. Need the model pointer here so that
    // actions can call functions in it for editing.  Position is the position in terms of
    // the widget rather than the window. Use a_view->viewport()->mapToGlobal(a_position)
    // to get the position relative to the window for a properly placed menu.
    void do_context_menu(QAbstractItemView* a_view, Outliner_Model* a_model, QPoint const& a_position) override final;
    // Do whatever we want when an item has been double clicked on.
    void do_double_clicked(QAbstractItemView* a_view, Outliner_Model* a_model) override final;

    // Additional Interface
    //============================================================
    Project* project();
    Project const* cproject() const;



    Outliner_Project_Item* get_project_item() const;
    Outliner_Entity_Item* entity_item(int a_index) const;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Outliner_Project_Item
  //---------------------------------------------------------------------------
  // Outliner item that represents a Project. It's data is the Project's name.
  // It's children are the section headers which may or may not be present.

  // For a single instance of the template declaration.
  namespace internal
  {
    using Outliner_Project_Item_Base =
    Abstract_Outliner_Readonly_Trunk_Item<Outliner_Root_Item, Outliner_Entity_Item>;
  }

  class Outliner_Project_Item :
      public internal::Outliner_Project_Item_Base
  {
  public:
    // Special 6
    //============================================================
    explicit Outliner_Project_Item(Parent_Item_Type* a_parent);
    ~Outliner_Project_Item() override final;

    // Virtual Interface
    //============================================================
    // Underlying data access
    //----------------------------------------
    // Get the item data for a given column and role
    QVariant get_data(int a_role = Qt::DisplayRole) const override final;

    // Other
    //----------------------------------------
    // Get the flags for this item
    Qt::ItemFlags get_flags() const override final;
    // Make and act on the context menu for this item. Need the model pointer here so that
    // actions can call functions in it for editing.  Position is the position in terms of
    // the widget rather than the window. Use a_view->viewport()->mapToGlobal(a_position)
    // to get the position relative to the window for a properly placed menu.
    void do_context_menu(QAbstractItemView* a_view, Outliner_Model* a_model, QPoint const& a_position) override final;
    // Do whatever we want when an item has been double clicked on.
    void do_double_clicked(QAbstractItemView* a_view, Outliner_Model* a_model) override final;

    // Additional Interface
    //============================================================
    Project* get_project();
    Project const* cget_project() const;

    Outliner_Entity_Item* entity_item(int a_index) const;
    void initialise();

    // What index is the Entity item that holds this id reside at?
    // Returns get_child_count() if it is not found.
    std::size_t index_of(Entity_ID a_id) const;
    // What Entity item holds this id? Returns nullptr if not found.
    Child_Item_Type* item_of(Entity_ID a_id) const;

    // When an Entity has had its name changed, this is called.
    void name_changed(Entity_ID a_id);
    // When an Entity has been added, this is called.
    void added(Entity_ID a_id);
    // When an Entity has been removed, this is called.
    void removed(Entity_ID a_id);
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Outliner_Entity_Item
  //---------------------------------------------------------------------------
  // Outliner item that represents a Project. It's data is the Project's name.
  // It's children are the section headers which may or may not be present.

  // For a single instance of the template declaration.
  namespace internal
  {
    using Outliner_Entity_Item_Base =
    Abstract_Outliner_Leaf_Item<Outliner_Project_Item>;
  }

  class Outliner_Entity_Item :
      public internal::Outliner_Project_Item_Base
  {
  private:
    // Member Data
    //============================================================
    Entity_ID m_id;

  public:
    // Special 6
    //============================================================
    explicit Outliner_Entity_Item(Parent_Item_Type* a_parent);
    ~Outliner_Entity_Item() override final;

    // Virtual Interface
    //============================================================
    // Underlying data access
    //----------------------------------------
    // Get the item data for a given column and role
    QVariant get_data(int a_role = Qt::DisplayRole) const override final;
    // Set the data in item with the given value
    void set_data(QVariant const& a_value) override final;

    // Editors
    //----------------------------------------
    // Make the appropriate editor for this item, parenting it to parent
    QWidget* get_editor(QWidget* a_parent) override final;
    // Set the data in the editor to the value in the item
    void set_editor_data(QWidget* a_editor) override final;
    // Get the data in the editor and return it
    QVariant get_editor_data(QWidget* a_editor) override final;

    // Other
    //----------------------------------------
    // Get the flags for this item
    Qt::ItemFlags get_flags() const override final;
    // Make and act on the context menu for this item. Need the model pointer here so that
    // actions can call functions in it for editing.  Position is the position in terms of
    // the widget rather than the window. Use a_view->viewport()->mapToGlobal(a_position)
    // to get the position relative to the window for a properly placed menu.
    void do_context_menu(QAbstractItemView* a_view, Outliner_Model* a_model, QPoint const& a_position) override final;
    // Do whatever we want when an item has been double clicked on.
    void do_double_clicked(QAbstractItemView* a_view, Outliner_Model* a_model) override final;

    // Additional Interface
    //============================================================
    Project* get_project();
    Project const* cget_project() const;

    Entity_ID id() const;
    void set_name(QString const& a_name);
  };
}
*/
#endif // SAK_PROJECT_OUTLINER_ITEMS_HPP
