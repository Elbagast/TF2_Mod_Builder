#ifndef SAK_OUTLINER_PROJECT_ITEM_HPP
#define SAK_OUTLINER_PROJECT_ITEM_HPP

#include <qtlib/outliner/multitrunk_item.hpp>
#include <sak/shared/outliner_item.hpp>
#include <memory>
//#include "root_item.hpp"

namespace sak
{
  class Project;

  namespace outliner
  {
    class root_item;

    //------------------------------------------------------------------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------
    // sak::outliner::Project_Item
    //---------------------------------------------------------------------------
    // Outliner item that represents a Project. It's data is the Project's name.
    // It's children are the section headers which may or may not be present.

    class project_item :
            public qtlib::outliner::Readonly_Multitrunk_Item<root_item, file::outliner::header_item>
    {
        using inherited_type = qtlib::outliner::Readonly_Multitrunk_Item<root_item, file::outliner::header_item>;
    public:

        // Special 6
        //============================================================
        explicit project_item(parent_type* a_parent);
        ~project_item() override;

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

        file::outliner::header_item* file_header_item() const;

        void initialise_files(bool a_read_files);
        void close_files();
    };
  }
}
#endif // SAK_OUTLINER_PROJECT_ITEM_HPP
