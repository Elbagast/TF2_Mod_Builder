#ifndef SAK_SECTION_OUTLINER_ITEMS_HPP
#define SAK_SECTION_OUTLINER_ITEMS_HPP

#ifndef SAK_SECTION_OUTLINER_ITEMS_FWD_HPP
#include "section_outliner_items_fwd.hpp"
#endif

#ifndef SAK_PROJECT_OUTLINER_ITEMS_FWD_HPP
#include "project_outliner_items_fwd.hpp"
#endif

#ifndef SAK_PROJECT_DATA_FWD_HPP
#include "project_data_fwd.hpp"
#endif

#ifndef SAK_SECTION_HANDLE_HPP
#include "section_handle.hpp"
#endif

#ifndef SAK_SECTION_DATA_HPP
#include "section_data.hpp"
#endif

#ifndef SAK_ABSTRACT_OUTLINER_BRANCH_ITEM_HPP
#include "abstract_outliner_branch_item.hpp"
#endif

#ifndef SAK_ABSTRACT_OUTLINER_LEAF_ITEM_HPP
#include "abstract_outliner_leaf_item.hpp"
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Section_Outliner_Item<T>
  //---------------------------------------------------------------------------

  // For a single instance of the template declaration.
  namespace internal
  {
    template <typename T>
    using Section_Outliner_Item_Base =
    Abstract_Outliner_Leaf_Item<Section_Outliner_Header_Item<T>>;
  }


  template <typename T>
  class Section_Outliner_Item :
      public internal::Section_Outliner_Item_Base<T>
  {
    using Inherited_Type = internal::Section_Outliner_Item_Base<T>;
  public:
    using Data_Type = T;
    using Handle_Type = Section_Handle<Data_Type>;

    // Special 6
    //============================================================
    Section_Outliner_Item(Parent_Item_Type* a_parent, Handle_Type const& a_handle);
    ~Section_Outliner_Item() override final;

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
    Project_Data& get_project();
    Project_Data const& cget_project() const;
    Handle_Type const& cget_handle() const;
    QString cget_name() const;
    void set_name(QString const& a_name);

    QString cget_description() const;

  private:
    Handle_Type m_handle;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Section_Outliner_Header_Item<T>
  //---------------------------------------------------------------------------

  // For a single instance of the template declaration.
  namespace internal
  {
    template <typename T>
    using Section_Outliner_Header_Item_Base =
    Abstract_Outliner_Readonly_Branch_Item<Project_Outliner_Project_Item, Section_Outliner_Item<T>>;
  }

  template <typename T>
  class Section_Outliner_Header_Item :
      public internal::Section_Outliner_Header_Item_Base<T>
  {
    using Inherited_Type = internal::Section_Outliner_Header_Item_Base<T>;
  public:
    // Typedefs
    //============================================================
    using Data_Type = T;
    using Handle_Type = Section_Handle<Data_Type>;

    // Special 6
    //============================================================
    explicit Section_Outliner_Header_Item(Parent_Item_Type* a_parent, bool a_read_files = true);
    ~Section_Outliner_Header_Item() override final;

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
    Project_Data& get_project();
    Project_Data const& cget_project() const;
    // What index is the File_Item that holds this File_Handle reside at?
    // Returns get_child_count() if it is not found.
    std::size_t index_of(Handle_Type const& a_handle) const;
    // What File_Item holds this File_Handle? Returns nullptr if not found.
    Child_Item_Type* item_of(Handle_Type const& a_handle) const;

    // When a File has had its name changed, this is called.
    void name_changed(Handle_Type const& a_handle);
    // When a File has been added, this is called.
    void added(Handle_Type const& a_handle);
    // When a File has been removed, this is called.
    void removed(Handle_Type const& a_handle);
  };
}

#endif // SAK_SECTION_OUTLINER_ITEMS_HPP
