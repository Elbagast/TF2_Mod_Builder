#ifndef SAK_SHARED_OUTLINER_HEADER_ITEM_HPP
#define SAK_SHARED_OUTLINER_HEADER_ITEM_HPP

#include "fwd/header_item.hpp"
#include "item.hpp"
#include <sak/project/outliner/fwd/project_item.hpp>
#include <sak/project/fwd/object.hpp>

#include <sak/shared/fwd/object.hpp>
#include <sak/shared/fwd/extended_manager.hpp>

#include <qtlib/outliner/branch_item.hpp>

namespace sak
{
  namespace shared
  {
    namespace outliner
    {
      //---------------------------------------------------------------------------
      // shared::outliner::header_item<T>
      //---------------------------------------------------------------------------
      template <typename T>
      class header_item :
          public qtlib::outliner::Readonly_Branch_Item<project::outliner::project_item, item<T>>
      {
        using inherited_type = qtlib::outliner::Readonly_Branch_Item<project::outliner::project_item, item<T>>;
      public:
        // Typedefs
        //============================================================
        using object_type = T;
        using extended_handle_type = extended_handle<object_type>;

        // Special 6
        //============================================================
        explicit header_item(parent_type* a_parent, bool a_read_files = true);
        ~header_item() override final;

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
        project::object& get_project();
        project::object const& cget_project() const;
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
    }
  }
}

#endif // SAK_SHARED_OUTLINER_HEADER_ITEM_HPP
