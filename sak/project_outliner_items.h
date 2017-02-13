#ifndef PROJECT_OUTLINER_ITEMS_H
#define PROJECT_OUTLINER_ITEMS_H

#include "../qtlib/outliner/outliner_abstract_root_item.h"
#include "../qtlib/outliner/outliner_abstract_readonly_item.h"
#include "../qtlib/outliner/outliner_branch_item.h"
#include <memory>

namespace sak
{
    class Project;

    namespace outliner
    {
        class Root_Item;
        class Project_Item;
        class File_Header_Item;
        class File_Item;
        class Texture_Header_Item;
        class Texture_Item;

        class Header_Item;
        class Component_Item;

        //---------------------------------------------------------------------------
        // sak::outliner::Root_Item
        //---------------------------------------------------------------------------
        // Outliner root item for a single project. This item is invisible and
        // defines the default context menu.

        class Root_Item :
                public qtlib::outliner::abstract::Root_Item
        {
        public:
            // Special 6
            //============================================================
            explicit Root_Item(Project& a_project);
            ~Root_Item() override;

            // Virtual Interface
            //============================================================
            // Does this item have any child items?
            bool has_children() const override final;
            // The number of children this item has
            int get_child_count() const override final;

            // Does this item have a child item at this index?
            bool has_child_at(int a_index) const override final;
            // Get the child at a given row, return nullptr if there is no child at row
            item_type* get_child_at(int a_index) const override final;
            // Other
            //----------------------------------------
            // Make and act on the context menu for this item. Need the model pointer here so that
            // actions can call functions in it for editing
            void do_custom_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_point) override final;

            // Additional Interface
            //============================================================
            Project& get_project();
            Project const& cget_project() const;
        private:
            Project& m_project;
            std::unique_ptr<Project_Item> m_child;
        };


        class Header_Item :
                public qtlib::outliner::abstract::Readonly_Item
        {
        };

        //---------------------------------------------------------------------------
        // sak::outliner::Project_Item
        //---------------------------------------------------------------------------
        // Outliner item that represents a Project. It's data is the Project's name.
        // It's children are the section headers which

        class Project_Item :
                public qtlib::outliner::Readonly_Branch_Item<Root_Item, Header_Item>
        {
        public:

            // Special 6
            //============================================================
            explicit Project_Item(Root_Item* a_parent);
            ~Project_Item() override;

            // Virtual Interface
            //============================================================
            /*
            // Does this item have a parent item?
            bool has_parent() const override final;
            // Get the item that is the parent of this
            item_type* get_parent() const override final;
            // Get the item at the root of the structure
            item_type* get_root() const override final;

            // Does this item have any child items?
            bool has_children() const override final;
            // The number of children this item has
            int get_child_count() const override final;

            // Does this item have a child item at this index?
            bool has_child_at(int a_index) const override final;
            // Get the child at a given row, return nullptr if there is no child at row
            item_type* get_child_at(int a_row) const override final;

            // The row that this item is in relative to the parent e.g. if the parent has
            // 5 children, and this is the third, then row is 2. If this has no parent
            // then -1 is returned.
            int index_in_parent() const override final;
*/
            // Underlying data access
            //----------------------------------------
            // Get the item data for a given column and role
            QVariant get_data(int a_role = Qt::DisplayRole) const override final;

            // Other
            //----------------------------------------
            // Make and act on the context menu for this item. Need the model pointer here so that
            // actions can call functions in it for editing
            void do_custom_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_point) override final;

            // Additional Interface
            //============================================================
            Project& get_project();
            Project const& cget_project() const;
        private:
            //Root_Item* m_parent;
            //std::unique_ptr<Header_Item> m_headers;
        };

        class Component_Item :
                public qtlib::outliner::abstract::Item
        {
        };



        class File_Item : public qtlib::outliner::abstract::Item {};

        class File_Header_Item :
                public qtlib::outliner::Readonly_Branch_Item<Project_Item, File_Item>
        {
        public:
            using model_type = Header_Item::model_type;

            // Special 6
            //============================================================
            explicit File_Header_Item(parent_type* a_parent);
            ~File_Header_Item() override;

            // Virtual Interface
            //============================================================
            // Underlying data access
            //----------------------------------------
            // Get the item data for a given column and role
            QVariant get_data(int a_role = Qt::DisplayRole) const override final;
            // Other
            //----------------------------------------
            // Make and act on the context menu for this item. Need the model pointer here so that
            // actions can call functions in it for editing
            void do_custom_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_point) override final;

            // Additional Interface
            //============================================================
            Project& get_project();
            Project const& cget_project() const;
        };


        class Texture_Header_Item{};
        class Texture_Item{};
    }
}

#endif // PROJECT_OUTLINER_ITEMS_H
