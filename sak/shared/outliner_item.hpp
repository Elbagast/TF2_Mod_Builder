#ifndef SAK_SHARED_OUTLINER_ITEM_HPP
#define SAK_SHARED_OUTLINER_ITEM_HPP

#include "fwd/outliner_item.hpp"
#include "object.hpp"
#include "extended_manager.hpp"
#include <qtlib/outliner/branch_item.hpp>
#include <qtlib/outliner/leaf_item.hpp>

namespace sak
{
  namespace outliner
  {
    class root_item;
    class project_item;
  }

  namespace shared
  {
    namespace outliner
    {
      //---------------------------------------------------------------------------
      // shared::outliner::header_item<T>
      //---------------------------------------------------------------------------
      template <typename T>
      class header_item :
          public qtlib::outliner::Readonly_Branch_Item<sak::outliner::project_item, item<T>>
      {
        using inherited_type = qtlib::outliner::Readonly_Branch_Item<sak::outliner::project_item, item<T>>;
      public:
        // Typedefs
        //============================================================
        using object_type = T;
        using extended_handle_type = extended_handle<object_type>;

        // Special 6
        //============================================================
        explicit header_item(parent_type* a_parent, bool a_read_files = true);
        ~header_item() override;

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
        Project& get_project();
        Project const& cget_project() const;
        // What index is the File_Item that holds this File_Handle reside at?
        // Returns get_child_count() if it is not found.
        std::size_t index_of(extended_handle_type const& a_ehandle) const;
        // What File_Item holds this File_Handle? Returns nullptr if not found.
        child_type* item_of(extended_handle_type const& a_ehandle) const;

        // When a File has had its name changed, this is called.
        void name_changed(extended_handle_type const& a_ehandle);
        // When a File has been added, this is called.
        void added(extended_handle_type const& a_ehandle);
        // When a File has been removed, this is called.
        void removed(extended_handle_type const& a_ehandle);
      };

      //---------------------------------------------------------------------------
      // shared::outliner::item<T>
      //---------------------------------------------------------------------------

      template <typename T>
      class item :
          public qtlib::outliner::Leaf_Item<header_item<T>>
      {
        using inherited_type = qtlib::outliner::Leaf_Item<header_item<T>>;
      //template <typename T, typename...Ms>
      //class item<object<T,Ms...>> :
      //    public qtlib::outliner::Leaf_Item<header_item<object<T,Ms...>>>
      //{
      //  using inherited_type = qtlib::outliner::Leaf_Item<header_item<object<T,Ms...>>>;
      public:
        //using object_type = object<T,Ms...>;
        using object_type = T;
        using extended_handle_type = extended_handle<object_type>;

        // Special 6
        //============================================================
        item(parent_type* a_parent, extended_handle_type const& a_ehandle);
        ~item() override;

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
        void do_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_position) override final;
        // Do whatever we want when an item has been double clicked on.
        void do_double_clicked(QAbstractItemView* a_view, model_type* a_model) override final;


        // Additional Interface
        //============================================================
        Project& get_project();
        Project const& cget_project() const;
        extended_handle_type const& cget_ehandle() const;
        QString cget_name() const;
        void set_name(QString const& a_name);

        QString cget_description() const;

      private:
        extended_handle_type m_ehandle;
      };
    }
  }
}

#endif // SAK_SHARED_OUTLINER_ITEM_HPP
