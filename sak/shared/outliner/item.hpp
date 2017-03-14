#ifndef SAK_SHARED_OUTLINER_ITEM_HPP
#define SAK_SHARED_OUTLINER_ITEM_HPP

#include "fwd/item.hpp"
#include "fwd/header_item.hpp"
#include <sak/project/fwd/object.hpp>

#include <sak/shared/object.hpp>
#include <sak/shared/manager.hpp>

#include <qtlib/outliner/leaf_item.hpp>

namespace sak
{
  namespace shared
  {
    namespace outliner
    {
      //---------------------------------------------------------------------------
      // shared::outliner::item<T>
      //---------------------------------------------------------------------------

      template <typename T>
      class item :
          public qtlib::outliner::Leaf_Item<header_item<T>>
      {
        using inherited_type = qtlib::outliner::Leaf_Item<header_item<T>>;
      public:
        using object_type = T;
        using handle_type = handle<object_type>;

        // Special 6
        //============================================================
        item(parent_type* a_parent, handle_type const& a_handle);
        ~item() override final;

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
        project::object& get_project();
        project::object const& cget_project() const;
        handle_type const& cget_handle() const;
        QString cget_name() const;
        void set_name(QString const& a_name);

        QString cget_description() const;

      private:
        handle_type m_handle;
      };
    }
  }
}

#endif // SAK_SHARED_OUTLINER_ITEM_HPP
