#include "consoledialog.h"
#include "ui_consoledialog.h"

Saklib::Qtlib::ConsoleDialog::ConsoleDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::ConsoleDialog)
{
    m_ui->setupUi(this);

}

Saklib::Qtlib::ConsoleDialog::~ConsoleDialog() = default;

void Saklib::Qtlib::ConsoleDialog::slot_append(QString toAppend)
{
    m_ui->textEdit->append(toAppend);
}
