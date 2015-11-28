#ifndef SELECT_ELEMENT_TYPE_DIALOG_H
#define SELECT_ELEMENT_TYPE_DIALOG_H

#include "../types.h"
#include <QDialog>

namespace Ui
{
    class Select_Element_Type_Dialog;
}

namespace saklib
{
    namespace Qtlib
    {
        /*
        Select_Element_Type_Dialog
        ====================================================================================================
        Dialog that asks the user to select an Element type from a limited selection of them.
        */

        class Select_Element_Type_Dialog :
                public QDialog
        {
            Q_OBJECT

        public:
            // Special 6
            //============================================================
            explicit Select_Element_Type_Dialog(std::vector<String> const& element_types, QWidget* parent = nullptr);
            ~Select_Element_Type_Dialog() override;

            // Interface
            //============================================================
            String const& selected_element_type() const;

        private:
            // Data Members
            //============================================================
            std::unique_ptr<Ui::Select_Element_Type_Dialog> m_ui;

            std::vector<String> m_element_types;
        };

    } // namespace Qtlib
}  // namespace saklib

#endif // SELECT_ELEMENT_TYPE_DIALOG_H
