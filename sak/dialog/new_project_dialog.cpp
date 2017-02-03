#include "new_project_dialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include "../../qtlib/validating_line_edit.h"
#include "../../qtlib/text_colour_state_changer.h"
#include "../../qtlib/directory_name_validator.h"
#include "../../qtlib/existing_directory_validator.h"
#include <QFileDialog>

namespace
{
    QString const c_title{"New Project"};
    QString const c_text_description{"Create a new project:"};
    QString const c_text_name{"Name"};
    QString const c_text_location{"Location:"};
    QString const c_text_location_browse{"Browse..."};
    QString const c_text_finish_button{"Finish"};
    QString const c_text_cancel_button{"Cancel"};
}

// Seems like these classes could be templates?
class sak::Project_Name_Entry :
        public qtlib::Validating_Line_Edit
{
public:
    explicit Project_Name_Entry(QWidget* a_parent = nullptr):
        Validating_Line_Edit(a_parent),
        m_val{},
        m_sc{Qt::blue, Qt::red}
    {
        this->set_validator(&m_val);
        this->set_state_changer(&m_sc);
    }
    ~Project_Name_Entry() override = default;
private:
    qtlib::Directory_Name_Validator m_val;
    qtlib::Text_Colour_State_Changer m_sc;
};

class sak::Project_Location_Entry :
        public qtlib::Validating_Line_Edit
{
public:
    explicit Project_Location_Entry(QWidget* a_parent = nullptr):
        Validating_Line_Edit(a_parent),
        m_val{},
        m_sc{Qt::blue, Qt::red}
    {
        this->set_validator(&m_val);
        this->set_state_changer(&m_sc);
    }
    ~Project_Location_Entry() override = default;
private:
    qtlib::Existing_Directory_Validator m_val;
    qtlib::Text_Colour_State_Changer m_sc;
};

// Special 6
//============================================================
sak::New_Project_Dialog::New_Project_Dialog(QWidget* a_parent) :
    QDialog(a_parent),
    m_layout{std::make_unique<QVBoxLayout>()},
    m_description{std::make_unique<QLabel>(c_text_description)},
    m_entry_layout{std::make_unique<QFormLayout>()},
    m_name_entry{std::make_unique<Project_Name_Entry>()},
    m_location_layout{std::make_unique<QHBoxLayout>()},
    m_location_entry{std::make_unique<Project_Location_Entry>()},
    m_location_browse{std::make_unique<QPushButton>(c_text_location_browse)},
    m_button_layout{std::make_unique<QHBoxLayout>()},
    m_finish_button{std::make_unique<QPushButton>(c_text_finish_button)},
    m_cancel_button{std::make_unique<QPushButton>(c_text_cancel_button)}
{
    this->setWindowTitle(c_title);
    this->setFixedSize(512,256);

    m_layout->addWidget(m_description.get());

    m_entry_layout->addRow(c_text_name, m_name_entry.get());
    m_location_layout->addWidget(m_location_entry.get());
    m_location_layout->addWidget(m_location_browse.get());

    m_entry_layout->addRow(c_text_location, m_location_layout.get());

    m_layout->addLayout(m_entry_layout.get());

    m_button_layout->addStretch();
    m_button_layout->addWidget(m_finish_button.get());
    m_button_layout->addWidget(m_cancel_button.get());

    m_layout->addLayout(m_button_layout.get());

    this->setLayout(m_layout.get());

    QObject::connect(m_cancel_button.get(), &QPushButton::clicked, [=](){this->reject();});
    QObject::connect(m_finish_button.get(), &QPushButton::clicked, [=](){this->accept();});

    QObject::connect(m_location_browse.get(), &QPushButton::clicked, this, &New_Project_Dialog::browse);

    QObject::connect(m_name_entry.get(), &Project_Name_Entry::state_changed, [=](){this->update_finish_button();});
    QObject::connect(m_location_entry.get(), &Project_Location_Entry::state_changed, [=](){this->update_finish_button();});

    update_finish_button();
}

sak::New_Project_Dialog::New_Project_Dialog(QString const& a_name, QString const& a_location, QWidget* a_parent):
    New_Project_Dialog(a_parent)
{
    m_name_entry->setText(a_name);
    m_location_entry->setText(a_location);
}

sak::New_Project_Dialog::~New_Project_Dialog() = default;

// Access the data we make this class to get.
QString sak::New_Project_Dialog::name() const
{
    return m_name_entry->text();
}

QString sak::New_Project_Dialog::location() const
{
    return m_location_entry->text();
}

// Slot for the browse for location directory button.
void sak::New_Project_Dialog::browse()
{
    QString l_result{};
    l_result = QFileDialog::getExistingDirectory(this, tr("Select Location Directory"),
                                    location(),
                                    QFileDialog::ShowDirsOnly
                                    | QFileDialog::DontResolveSymlinks);
    if (!l_result.isEmpty())
    {
        m_location_entry->setText(l_result);
    }
}

// Slot for the entry widgets to inform that they're changed state.
void sak::New_Project_Dialog::update_finish_button()
{
    m_finish_button->setEnabled(m_name_entry->is_valid() && m_location_entry->is_valid());
}
