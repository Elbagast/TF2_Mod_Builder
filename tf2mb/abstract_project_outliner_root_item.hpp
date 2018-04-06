#ifndef SAK_ABSTRACT_PROJECT_OUTLINER_ROOT_ITEM_HPP
#define SAK_ABSTRACT_PROJECT_OUTLINER_ROOT_ITEM_HPP

#ifndef SAK_ABSTRACT_PROJECT_OUTLINER_ROOT_ITEM_FWD_HPP
#include "outliner_project_root_item_fwd.hpp"
#endif

#ifndef SAK_PROJECT_FWD_HPP
#include "project_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_OUTLINER_ITEM_HPP
#include "abstract_outliner_item.hpp"
#endif

#ifndef SAK_ENTITY_ID_FWD_HPP
#include <sak/entity_id_fwd.hpp>
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Abstract_Outliner_Project_Root_Item
  //---------------------------------------------------------------------------
  // In order to allow the outliner to show the data in different ways that
  // allow it to not care about the specific item types. This means the outliner
  // widget sends changes to this which then handles how things update.

  class Abstract_Outliner_Project_Root_Item :
      public Abstract_Outliner_Root_Item
  {
  private:
    // Data Members
    //============================================================
    Project* m_project;

  public:
    // Special 6
    //============================================================
    explicit Abstract_Outliner_Project_Root_Item(Project* a_project);
    ~Abstract_Outliner_Project_Root_Item() override;

    // Virtual Interface
    //============================================================

    // Children
    //----------------------------------------
    // Does this item have any child items?
    bool has_children() const override = 0;
    // The number of children this item has
    int get_child_count() const override = 0;
    // Does this item have a child item at this index?
    bool has_child_at(int a_index) const override = 0;
    // Get the child at a given row, return nullptr if there is no child at row
    Abstract_Outliner_Item* get_child_at(int a_row) const override = 0;

    // Other
    //----------------------------------------
    // Make and act on the context menu for this item. Need the model pointer here so that
    // actions can call functions in it for editing.  Position is the position in terms of
    // the widget rather than the window. Use a_view->viewport()->mapToGlobal(a_position)
    // to get the position relative to the window for a properly placed menu.
    void do_context_menu(QAbstractItemView* a_view, Outliner_Model* a_model, QPoint const& a_position) override = 0;
    // Do whatever we want when an item has been double clicked on.
    void do_double_clicked(QAbstractItemView* a_view, Outliner_Model* a_model) override = 0;

    // Project Stuff
    //----------------------------------------
    Project* project();
    Project const* cproject() const;

    // Update the outliner item tree as a result of these actions.
    virtual void added(Entity_ID a_id) = 0;
    virtual void removed(Entity_ID a_id) = 0;
    virtual void name_changed(Entity_ID a_id) = 0;
  };

  class Dummy_Outliner_Project_Root_Item :
      public Abstract_Outliner_Project_Root_Item
  {
  public:
    // Special 6
    //============================================================
    explicit Dummy_Outliner_Project_Root_Item(Project* a_project);
    ~Dummy_Outliner_Project_Root_Item() override final;

    // Virtual Interface
    //============================================================

    // Children
    //----------------------------------------
    // Does this item have any child items?
    bool has_children() const override final { return false; }
    // The number of children this item has
    int get_child_count() const override final { return 0; }
    // Does this item have a child item at this index?
    bool has_child_at(int a_index) const override final { return false; }
    // Get the child at a given row, return nullptr if there is no child at row
    Abstract_Outliner_Item* get_child_at(int a_row) const override final { return nullptr; }

    // Other
    //----------------------------------------
    // Make and act on the context menu for this item. Need the model pointer here so that
    // actions can call functions in it for editing.  Position is the position in terms of
    // the widget rather than the window. Use a_view->viewport()->mapToGlobal(a_position)
    // to get the position relative to the window for a properly placed menu.
    void do_context_menu(QAbstractItemView* a_view, Outliner_Model* a_model, QPoint const& a_position) override final {}
    // Do whatever we want when an item has been double clicked on.
    void do_double_clicked(QAbstractItemView* a_view, Outliner_Model* a_model) override final  {}

    // Project Stuff
    //----------------------------------------
    // Update the outliner item tree as a result of these actions.
    void added(Entity_ID a_id) override final {}
    void removed(Entity_ID a_id) override final {}
    void name_changed(Entity_ID a_id) override final {}
  };

}

#endif // SAK_ABSTRACT_PROJECT_OUTLINER_ROOT_ITEM_HPP
