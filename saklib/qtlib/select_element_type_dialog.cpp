#include "select_element_type_dialog.h"
#include "ui_select_element_type_dialog.h"
#include "qstring_operations.h"

// Special 6
//============================================================
Saklib::Qtlib::Select_Element_Type_Dialog::Select_Element_Type_Dialog(Vector_String const& element_types, QWidget* parent) :
    QDialog(parent),
    m_ui(std::make_unique<Ui::Select_Element_Type_Dialog>()),
    m_element_types(element_types)
{
    m_ui->setupUi(this);

    //populate the comboBox
    for (auto const& type : m_element_types)
    {
        m_ui->comboBox->addItem(to_QString(type));
    }
}

Saklib::Qtlib::Select_Element_Type_Dialog::~Select_Element_Type_Dialog() = default;


// Interface
//============================================================
Saklib::String const& Saklib::Qtlib::Select_Element_Type_Dialog::selected_element_type() const
{
    return m_element_types.at(m_ui->comboBox->currentIndex());
}

