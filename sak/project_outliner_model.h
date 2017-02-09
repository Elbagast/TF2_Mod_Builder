#ifndef PROJECT_OUTLINER_MODEL_H
#define PROJECT_OUTLINER_MODEL_H

#include <memory>
#include <QAbstractItemModel>

namespace sak
{
    class Project;

    //---------------------------------------------------------------------------
    // Project
    //---------------------------------------------------------------------------
    /*
    The outliner is a tree that looks like this:

    - Project name -> always present
        - Files -> absent if none
            - Files[0] name
            ...
            - Files[n] name
        - Textures -> absent if none
            - Textures[0] name
            ...
            - Textures[n] name
        - Materials -> absent if none
            - Materials[0] name
            ...
            - Materials[n] name
        - Models -> absent if none
            - Models[0] name
            ...
            - Models[n] name
        - Packages -> absent if none
            - Packages[0] name
            ...
            - Packages[n] name
        - Releases -> absent if none
            - Releases[0] name
            ...
            - Releases[n] name

    Thus:
    - outliner has 1 column at any given time
    - outliner row count is dependent on project content
    - outliner tree depth is never greater than 3
    i.e. for the above
    using QMI = QModelIndex;
    QMI(-1,-1) -> invalid = root
        QMI(0,0) -> top project
            QMI(0,0) -> Files header
                QMI(0,0) -> Files[0]
                ...
                QMI(n,0) -> Files[n]
            QMI(1,0) -> Textures header
                QMI(0,0) -> Textures[0]
                ...
                QMI(n,0) -> Textures[n]
            etc.
    */

    class Project_Outliner_Model :
            public QAbstractItemModel
    {
        Q_OBJECT
    public:
        // Special 6
        //============================================================
        explicit Project_Outliner_Model(Project& a_project, QObject* a_parent = nullptr);
        ~Project_Outliner_Model() override;

        // Virtual Overrides
        //============================================================
        // Read functions
        //----------------------------------------
        // Get the flags for the given QModelIndex.
        Qt::ItemFlags flags(QModelIndex const& index) const override;
        // Get the data for the given QModelIndex.
        QVariant data(QModelIndex const& index, int role) const override;
        // Get the header data for a given section and orientation
        //QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
        // The number of rows (children) the item at a given QModelIndex has.
        int rowCount(QModelIndex const& parent = QModelIndex()) const override;
        // Always returns 1
        int columnCount(QModelIndex const& parent = QModelIndex()) const override;

        // Write functions
        //----------------------------------------
        // Set the data at a given index with value, using role
        bool setData (QModelIndex const& index, QVariant const& value, int role = Qt::EditRole ) override;
        //bool setHeaderData ( int section, Qt::Orientation orientation, QVariant const& value, int role = Qt::EditRole ) override;

        // these are the inbuilt functions for this, but it isn't clear how they would be used in this case...
        //bool insertRows(int row, int count, QModelIndex const& parent = QModelIndex() ) override;
        //bool removeRows(int row, int count, QModelIndex const& parent = QModelIndex() ) override;

        // Indexing
        //----------------------------------------
        // Get the index of the item at the given position
        QModelIndex index(int row, int column, QModelIndex const& parent = QModelIndex()) const override;
        // Get the index of the parent of the item at a given index
        QModelIndex parent(QModelIndex const& index) const override;

        // Custom Access
        //============================================================
        /*
        // Make a QModelIndex of this item by searching through the model until a postition is found that matches this
        QModelIndex make_index_of(ElementID const& elementid) const;
        QModelIndex make_index_of(AttributeID const& attributeid) const;
        QModelIndex make_index_of(ProxyID const& proxyid) const;
        QModelIndex make_index_of(QModelIndex const& parent, size_type proxyid_value) const;

        void child_indexes(std::vector<QModelIndex>& results, QModelIndex const& parent) const;
        std::vector<QModelIndex> all_indexes() const;

        // Return true if make_index_of returns a valid, non-root QModelIndex
        bool has_index_of(ElementID const& elementid) const;
        bool has_index_of(AttributeID const& attributeid) const;
        bool has_index_of(ProxyID const& proxyid) const;

        // Reset the entire model
        void update_all();

        // Update the data for a specific item
        void update_item(ElementID const& elementid);
        void update_item(AttributeID const& attributeid);

        // Update the data for a specific item's children
        void update_children(ElementID const& elementid);
        void update_children(AttributeID const& attributeid);

        // Add or remove rows from Attributes
        void add_row(AttributeID const& attributeid, int row);
        void remove_row(AttributeID const& attributeid, int row);

        // Request for a context menu by view at index and position
        void custom_context_menu(QAbstractItemView* view, QModelIndex const& index, QPoint position);

        // Allow a view to request an editor for a given index
        void request_editor(QModelIndex const& index);

        // Forward this request to the Project_Manager
        void request_editor(ElementID const& elementid);

        void begin_model_reset();
        void end_model_reset();
        */
    private:
        // Pimpl Data
        //============================================================
        class Implementation;
        std::unique_ptr<Implementation> m_data;

        Implementation& imp()                { return *m_data; }
        Implementation const& cimp() const   { return *m_data; }
    };

}

#endif // PROJECT_OUTLINER_MODEL_H
