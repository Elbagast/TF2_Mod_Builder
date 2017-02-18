#ifndef PROJECT_OUTLINER_ITEMS_H
#define PROJECT_OUTLINER_ITEMS_H

#include "../qtlib/outliner/outliner_abstract_root_item.h"
#include "../qtlib/outliner/outliner_abstract_readonly_item.h"
#include "../qtlib/outliner/outliner_branch_item.h"
#include "../qtlib/outliner/outliner_leaf_item.h"
#include "../qtlib/outliner/outliner_root_trunk_item.h"
#include "../qtlib/outliner/outliner_multitrunk_item.h"
#include <memory>
#include "file_manager.h"

namespace sak
{
    class Project;

    namespace outliner
    {
        class Root_Item;
        class Project_Item;
        class File_Header_Item;
        class File_Item;

        //------------------------------------------------------------------------------------------------------------------------------------------------------
        //---------------------------------------------------------------------------
        // sak::outliner::Root_Item
        //---------------------------------------------------------------------------
        // Outliner root item for a single project. This item is invisible and
        // defines the default context menu.

        class Root_Item :
                public qtlib::outliner::Root_Trunk_Item<Project_Item>
        {
            using inherited_type = qtlib::outliner::Root_Trunk_Item<Project_Item>;
        public:
            // Special 6
            //============================================================
            explicit Root_Item(Project& a_project);
            ~Root_Item() override;

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

            Project_Item* project_item() const;
            File_Header_Item* file_header_item() const;

        private:
            Project& m_project;
        };

        //------------------------------------------------------------------------------------------------------------------------------------------------------
        //---------------------------------------------------------------------------
        // sak::outliner::Project_Item
        //---------------------------------------------------------------------------
        // Outliner item that represents a Project. It's data is the Project's name.
        // It's children are the section headers which may or may not be present.

        class Project_Item :
                public qtlib::outliner::Readonly_Multitrunk_item<Root_Item, File_Header_Item>
        {
            using inherited_type = qtlib::outliner::Readonly_Multitrunk_item<Root_Item, File_Header_Item>;
        public:

            // Special 6
            //============================================================
            explicit Project_Item(parent_type* a_parent);
            ~Project_Item() override;

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

            File_Header_Item* file_header_item() const;

            void initialise_files(bool a_read_files);
            void close_files();
        };

        //------------------------------------------------------------------------------------------------------------------------------------------------------
        //---------------------------------------------------------------------------
        // sak::outliner::File_Header_Item
        //---------------------------------------------------------------------------
        // Outliner item that represents the File container of a Project. It's children
        // are all the Files present in the Project.

        class File_Header_Item :
                public qtlib::outliner::Readonly_Branch_Item<Project_Item, File_Item>
        {
            using inherited_type = qtlib::outliner::Readonly_Branch_Item<Project_Item, File_Item>;
        public:
            // Special 6
            //============================================================
            explicit File_Header_Item(parent_type* a_parent, bool a_read_files = true);
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
            std::size_t index_of_file(File_Handle const& a_file) const;
            // What File_Item holds this File_Handle? Returns nullptr if not found.
            File_Item* item_of_file(File_Handle const& a_file) const;

            // When a File has had its name changed, this is called.
            void name_changed(File_Handle const& a_file);
            // When a File has been added, this is called.
            void added(File_Handle const& a_file);
            // When a File has been removed, this is called.
            void removed(File_Handle const& a_file);
        };

        //------------------------------------------------------------------------------------------------------------------------------------------------------
        //---------------------------------------------------------------------------
        // sak::outliner::File_Item
        //---------------------------------------------------------------------------
        // Outliner item that represents a File of a Project.

        class File_Item :
                public qtlib::outliner::Leaf_Item<File_Header_Item>
        {
            using inherited_type = qtlib::outliner::Leaf_Item<File_Header_Item>;
        public:
            // Special 6
            //============================================================
            File_Item(parent_type* a_parent, File_Handle const& a_file);
            ~File_Item() override;

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
            File_Handle const& cget_file() const;
            QString cget_file_name() const;
            void set_file_name(QString const& a_name);

        private:
            File_Handle m_file;
        };
    }
}

#endif // PROJECT_OUTLINER_ITEMS_H