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
#include "../fixed_settings.h"
#include <QFileDialog>


//---------------------------------------------------------------------------
// New_Project_Dialog
//---------------------------------------------------------------------------

// Internal constants and implementation
//============================================================
namespace
{
    QString const c_title{"New Project"};
    QString const c_text_description{"Create a new project:"};
    QString const c_text_name{"Name"};
    QString const c_text_location{"Location:"};
    QString const c_text_location_browse{"Browse..."};
    QString const c_text_finish_button{"Finish"};
    QString const c_text_cancel_button{"Cancel"};

    QString const c_title_browse{"Select Location Directory"};

    // Seems like these classes could be templates?
    class Project_Name_Entry :
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

    class Project_Location_Entry :
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
}

// Pimpl Data
//============================================================
class sak::New_Project_Dialog::Data
{
public:
    std::unique_ptr<QVBoxLayout> m_layout;
    std::unique_ptr<QLabel> m_description;
    std::unique_ptr<QFormLayout> m_entry_layout;
    std::unique_ptr<Project_Name_Entry> m_name_entry;
    std::unique_ptr<QHBoxLayout> m_location_layout;
    std::unique_ptr<Project_Location_Entry> m_location_entry;
    std::unique_ptr<QPushButton> m_location_browse;
    std::unique_ptr<QHBoxLayout> m_button_layout;
    std::unique_ptr<QPushButton> m_finish_button;
    std::unique_ptr<QPushButton> m_cancel_button;

    Data():
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
    {}

};


// Special 6
//============================================================
sak::New_Project_Dialog::New_Project_Dialog(QWidget* a_parent) :
    QDialog(a_parent),
    m_data{std::make_unique<Data>()}
{
    this->setWindowTitle(c_title);
    this->setFixedSize(512,256);

    data().m_layout->addWidget(data().m_description.get());

    data().m_entry_layout->addRow(c_text_name, data().m_name_entry.get());
    data().m_location_layout->addWidget(data().m_location_entry.get());
    data().m_location_layout->addWidget(data().m_location_browse.get());

    data().m_entry_layout->addRow(c_text_location, data().m_location_layout.get());

    data().m_layout->addLayout(data().m_entry_layout.get());

    data().m_button_layout->addStretch();
    data().m_button_layout->addWidget(data().m_finish_button.get());
    data().m_button_layout->addWidget(data().m_cancel_button.get());

    data().m_layout->addLayout(data().m_button_layout.get());

    this->setLayout(data().m_layout.get());

    QObject::connect(data().m_cancel_button.get(), &QPushButton::clicked, [=](){this->reject();});
    QObject::connect(data().m_finish_button.get(), &QPushButton::clicked, [=](){this->accept();});

    QObject::connect(data().m_location_browse.get(), &QPushButton::clicked, this, &New_Project_Dialog::browse);

    QObject::connect(data().m_name_entry.get(), &Project_Name_Entry::state_changed, [=](){this->update_finish_button();});
    QObject::connect(data().m_location_entry.get(), &Project_Location_Entry::state_changed, [=](){this->update_finish_button();});


    data().m_name_entry->setText(Fixed_Settings::default_project_name());
    data().m_location_entry->setText(Fixed_Settings::default_project_location());

    update_finish_button();
}

sak::New_Project_Dialog::New_Project_Dialog(QString const& a_name, QString const& a_location, QWidget* a_parent):
    New_Project_Dialog(a_parent)
{
    data().m_name_entry->setText(a_name);
    data().m_location_entry->setText(a_location);
}

sak::New_Project_Dialog::~New_Project_Dialog() = default;


// Interface
//============================================================
// Access the data we make this class to get.
QString sak::New_Project_Dialog::name() const
{
    return cdata().m_name_entry->text();
}

QString sak::New_Project_Dialog::location() const
{
    return cdata().m_location_entry->text();
}

// Internal Interface
//============================================================
// Slot for the browse for location directory button.
void sak::New_Project_Dialog::browse()
{
    QString l_result{};
    l_result = QFileDialog::getExistingDirectory(this, c_title_browse,
                                    location(),
                                    QFileDialog::ShowDirsOnly
                                    | QFileDialog::DontResolveSymlinks);
    if (!l_result.isEmpty())
    {
        data().m_location_entry->setText(l_result);
    }
}

// Slot for the entry widgets to inform that they're changed state.
void sak::New_Project_Dialog::update_finish_button()
{
    data().m_finish_button->setEnabled(data().m_name_entry->is_valid() && data().m_location_entry->is_valid());
}
