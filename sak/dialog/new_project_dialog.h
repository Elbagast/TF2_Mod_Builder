#ifndef NEW_PROJECT_DIALOG_H
#define NEW_PROJECT_DIALOG_H

#include <memory>
#include <QDialog>

namespace sak
{
    // Probably want generalised classes for the entry of names and directories
    //class Project_Name_Entry;
    //class Project_Location_Entry;
    //class Validating_Line_Edit;

    //---------------------------------------------------------------------------
    // New_Project_Dialog
    //---------------------------------------------------------------------------
    // Class that has the user supply the required parameters to create a new project.
    /*
    There are only 2:
     - name
        - must be able to create a valid directory from the input
     - location (directory)
        - directory, existing or new

    Help information:
    - a new directory will be created:
        - location/name
    - a project file will be created inside it:
        - location/name/name.ext
    - subfolders of this directory will be created and managed by the project as needed.

    The finish button will not be activated while the inputs are invalid.

    Going to need to determine whether a project is already present at a given location...
    */
    class New_Project_Dialog :
            public QDialog
    {
        Q_OBJECT
    public:
        // Special 6
        //============================================================
        explicit New_Project_Dialog(QWidget* parent = nullptr);
        New_Project_Dialog(QString const& a_name, QString const& a_location, QWidget* parent = nullptr);
        ~New_Project_Dialog() override;

        // Interface
        //============================================================
        // Access the data we make this class to get.
        QString name() const;
        QString location() const;

    private:
        // Internal Interface
        //============================================================
        // Slot for the browse for location directory button.
        void browse();

        // Slot for the entry widgets to inform that they're changed state.
        void update_finish_button();

        // Pimpl Data
        //============================================================
        class Data;
        std::unique_ptr<Data> m_data;

        Data& data()                { return *m_data; }
        Data const& data() const    { return *m_data; }
        Data const& cdata() const   { return *m_data; }
    };
}


#endif // NEW_PROJECT_DIALOG_H
