#ifndef SAK_PROJECT_OUTLINER_ITEMS_HPP
#define SAK_PROJECT_OUTLINER_ITEMS_HPP

#ifndef SAK_PROJECT_OUTLINER_ITEMS_FWD_HPP
#include "project_outliner_items_fwd.hpp"
#endif

#ifndef SAK_PROJECT_DATA_FWD_HPP
#include "project_data_fwd.hpp"
#endif

#include "section_outliner_items.hpp"

#include <qtlib/outliner/root_trunk_item.hpp>
#include <qtlib/outliner/multitrunk_item.hpp>

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif


namespace sak
{
  //---------------------------------------------------------------------------
  // sak::Project_Outliner_Root_Item
  //---------------------------------------------------------------------------
  // Outliner root item for a single project. This item is invisible and
  // defines the default context menu.

  // For a single instance of the template declaration.
  namespace internal
  {
    using Project_Outliner_Root_Item_Base =
    qtlib::outliner::Root_Trunk_Item<Project_Outliner_Project_Item>;
  }

  class Project_Outliner_Root_Item :
      public internal::Project_Outliner_Root_Item_Base
  {
  public:
    // Special 6
    //============================================================
    explicit Project_Outliner_Root_Item(Project_Data& a_project);
    ~Project_Outliner_Root_Item() override;

    // Virtual Interface
    //============================================================
    // Other
    //----------------------------------------
    // Make and act on the context menu for this item. Need the model pointer here so that
    // actions can call functions in it for editing.  Position is the position in terms of
    // the widget rather than the window. Use a_view->viewport()->mapToGlobal(a_position)
    // to get the position relative to the window for a properly placed menu.
    void do_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_position) override final;
    // Do whatever we want when an item has been double clicked on.
    void do_double_clicked(QAbstractItemView* a_view, model_type* a_model) override final;

    // Additional Interface
    //============================================================
    Project_Data& get_project();
    Project_Data const& cget_project() const;

    Project_Outliner_Project_Item* get_project_item() const;
    File_Outliner_Header_Item* file_header_item() const;
    Texture_Outliner_Header_Item* texture_header_item() const;

  private:
    Project_Data& m_project;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // sak::Project_Outliner_Project_Item
  //---------------------------------------------------------------------------
  // Outliner item that represents a Project. It's data is the Project's name.
  // It's children are the section headers which may or may not be present.

  // For a single instance of the template declaration.
  namespace internal
  {
    using Project_Outliner_Project_Item_Base =
    qtlib::outliner::Readonly_Multitrunk_Item<Project_Outliner_Root_Item, File_Outliner_Header_Item, Texture_Outliner_Header_Item>;
  }

  class Project_Outliner_Project_Item :
      public internal::Project_Outliner_Project_Item_Base
  {
  public:

    // Special 6
    //============================================================
    explicit Project_Outliner_Project_Item(parent_type* a_parent);
    ~Project_Outliner_Project_Item() override;

    // Virtual Interface
    //============================================================
    // Underlying data access
    //----------------------------------------
    // Get the item data for a given column and role
    QVariant get_data(int a_role = Qt::DisplayRole) const override final;

    // Other
    //----------------------------------------
    // Make and act on the context menu for this item. Need the model pointer here so that
    // actions can call functions in it for editing.  Position is the position in terms of
    // the widget rather than the window. Use a_view->viewport()->mapToGlobal(a_position)
    // to get the position relative to the window for a properly placed menu.
    void do_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_position) override final;
    // Do whatever we want when an item has been double clicked on.
    void do_double_clicked(QAbstractItemView* a_view, model_type* a_model) override final;

    // Additional Interface
    //============================================================
    Project_Data& get_project();
    Project_Data const& cget_project() const;

    File_Outliner_Header_Item* file_header_item() const;
    void initialise_files(bool a_read);
    void close_files();

    Texture_Outliner_Header_Item* texture_header_item() const;
    void initialise_textures(bool a_read);
    void close_textures();
  };
}

#endif // SAK_PROJECT_OUTLINER_ITEMS_HPP
