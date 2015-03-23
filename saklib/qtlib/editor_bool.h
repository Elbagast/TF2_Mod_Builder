#ifndef EDITOR_BOOL_H
#define EDITOR_BOOL_H

#include "attribute_editor.h"
#include "../types.h"
#include "../fwd_attribute_type.h"
#include "../command.h"

class QCheckBox;

namespace Saklib
{
    class Command_History;

    namespace Qtlib
    {
        class Editor_Bool :
                public Attribute_Editor
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            Editor_Bool(Attribute_Type<Bool>* attribute_type, Command_History& command_history, QWidget* parent = nullptr);
            ~Editor_Bool() override;

        protected:
            void v_refresh_data();

        private slots:
            // Slot used to capture the signal clicked() from the QCheckBox
            void slot_clicked();

        private:
            // Data Members
            //============================================================
            Attribute_Type<Bool>* mp_attribute_type;
            Command_History& m_command_history;
            Uptr<QCheckBox> m_checkbox;
        };

        class Command_Editor_Set_Attribute_Bool:
                public Command
        {
        public:
            Command_Editor_Set_Attribute_Bool(QCheckBox* editor, Attribute_Type<Bool>* attribute_type);
            ~Command_Editor_Set_Attribute_Bool() override;
        protected:
            void v_execute() override;
            void v_unexecute() override;
        private:
            QCheckBox* mp_editor;
            Attribute_Type<Bool>* mp_attribute_type;
            Bool m_old_value;
            Bool m_new_value;
        };

    } // namespace Qtlib
} // namespace Saklib




#endif // EDITOR_BOOL_H
