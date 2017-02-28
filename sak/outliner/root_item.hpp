#ifndef SAK_OUTLINER_ROOT_ITEM_HPP
#define SAK_OUTLINER_ROOT_ITEM_HPP

#include <qtlib/outliner/root_trunk_item.hpp>
#include <sak/shared/fwd/outliner_item.hpp>
#include <memory>

namespace sak
{
  class Project;

  namespace outliner
  {
    class project_item;

    //------------------------------------------------------------------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------
    // sak::outliner::Root_Item
    //---------------------------------------------------------------------------
    // Outliner root item for a single project. This item is invisible and
    // defines the default context menu.

    class root_item :
          public qtlib::outliner::Root_Trunk_Item<project_item>
    {
      using inherited_type = qtlib::outliner::Root_Trunk_Item<project_item>;
    public:
      // Special 6
      //============================================================
      explicit root_item(Project& a_project);
      ~root_item() override;

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
      Project& get_project();
      Project const& cget_project() const;

      project_item* get_project_item() const;
      file::outliner::header_item* file_header_item() const;

    private:
      Project& m_project;
    };
  }
}

#endif // SAK_OUTLINER_ROOT_ITEM_HPP
