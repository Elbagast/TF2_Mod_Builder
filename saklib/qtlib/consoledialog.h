#ifndef CONSOLEDIALOG_H
#define CONSOLEDIALOG_H
/*
ConsoleDialog
============================================================
An extremely simple dialog for catching depug information.
Connect a signal to the slot append and emit it when you want to output info
to this dialog.
*/
#include "../types.h"
#include <QDialog>
#include <memory>

namespace Ui {
class ConsoleDialog;
}

namespace Saklib
{
    namespace Qtlib
    {
        class ConsoleDialog :
                public QDialog
        {
            Q_OBJECT

        public:
            // Special 6
            //============================================================
            explicit ConsoleDialog(QWidget *parent = nullptr);
            ~ConsoleDialog() override;

        public slots:
            void slot_append(QString toAppend);

        private:
            // Data Members
            //============================================================
            Uptr<Ui::ConsoleDialog> m_ui;
        };
    } // namespace Qtlib
} // namespace Saklib

#endif // CONSOLEDIALOG_H
