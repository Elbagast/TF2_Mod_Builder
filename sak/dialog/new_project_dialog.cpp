#include "new_project_dialog.hpp"

#include "../fixed_settings.hpp"

#include <gui/validating_line_edit.hpp>
#include <gui/text_colour_state_changer.hpp>
#include <gui/directory_name_validator.hpp>
#include <gui/existing_directory_validator.hpp>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
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
  QString const c_text_name{"Name:"};
  QString const c_text_location{"Location:"};
  QString const c_text_location_browse{"Browse..."};
  QString const c_text_finish_button{"Finish"};
  QString const c_text_cancel_button{"Cancel"};

  QString const c_title_browse{"Select Location Directory"};

  // Seems like these classes could be templates?
  class Project_Name_Entry :
        public sak::gui::Validating_Line_Edit
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

    QString first_error() const
    {
        return m_val.first_error(this->text());
    }
  private:
    sak::gui::Directory_Name_Validator m_val;
    sak::gui::Text_Colour_State_Changer m_sc;
  };

  class Project_Location_Entry :
          public sak::gui::Validating_Line_Edit
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
    sak::gui::Existing_Directory_Validator m_val;
    sak::gui::Text_Colour_State_Changer m_sc;
  };


}

// Pimpl Data
//============================================================
class sak::New_Project_Dialog::Implementation
{
public:
  std::unique_ptr<QVBoxLayout> m_layout;
  std::unique_ptr<QLabel> m_description;
  std::unique_ptr<QFormLayout> m_entry_layout;
  std::unique_ptr<Project_Name_Entry> m_name_entry;
  std::unique_ptr<QHBoxLayout> m_location_layout;
  std::unique_ptr<Project_Location_Entry> m_location_entry;
  std::unique_ptr<QPushButton> m_browse_button;
  std::unique_ptr<QLabel> m_warning;
  std::unique_ptr<QHBoxLayout> m_button_layout;
  std::unique_ptr<QPushButton> m_finish_button;
  std::unique_ptr<QPushButton> m_cancel_button;

  Implementation():
    m_layout{std::make_unique<QVBoxLayout>()},
    m_description{std::make_unique<QLabel>(c_text_description)},
    m_entry_layout{std::make_unique<QFormLayout>()},
    m_name_entry{std::make_unique<Project_Name_Entry>()},
    m_location_layout{std::make_unique<QHBoxLayout>()},
    m_location_entry{std::make_unique<Project_Location_Entry>()},
    m_browse_button{std::make_unique<QPushButton>(c_text_location_browse)},
    m_warning{std::make_unique<QLabel>()},
    m_button_layout{std::make_unique<QHBoxLayout>()},
    m_finish_button{std::make_unique<QPushButton>(c_text_finish_button)},
    m_cancel_button{std::make_unique<QPushButton>(c_text_cancel_button)}
  {}

};


// Special 6
//============================================================
sak::New_Project_Dialog::New_Project_Dialog(QWidget* a_parent) :
    QDialog(a_parent),
    m_data{std::make_unique<Implementation>()}
{
    // Window setup
    this->setWindowTitle(c_title);
    this->setFixedSize(512,256);

    // No default buttons (default one is what pressing enter will activate)
    imp().m_browse_button->setDefault(false);
    imp().m_finish_button->setDefault(false);
    imp().m_cancel_button->setDefault(false);

    // Build the ui
    imp().m_layout->addWidget(imp().m_description.get());

    imp().m_entry_layout->addRow(c_text_name, imp().m_name_entry.get());
    imp().m_location_layout->addWidget(imp().m_location_entry.get());
    imp().m_location_layout->addWidget(imp().m_browse_button.get());

    imp().m_entry_layout->addRow(c_text_location, imp().m_location_layout.get());

    imp().m_layout->addLayout(imp().m_entry_layout.get());
    imp().m_layout->addWidget(imp().m_warning.get());

    imp().m_button_layout->addStretch();
    imp().m_button_layout->addWidget(imp().m_finish_button.get());
    imp().m_button_layout->addWidget(imp().m_cancel_button.get());

    imp().m_layout->addLayout(imp().m_button_layout.get());

    this->setLayout(imp().m_layout.get());

    // Connect the signals
    QObject::connect(imp().m_cancel_button.get(), &QPushButton::clicked, [this](){this->reject();});
    QObject::connect(imp().m_finish_button.get(), &QPushButton::clicked, [this](){this->accept();});

    QObject::connect(imp().m_browse_button.get(), &QPushButton::clicked, this, &New_Project_Dialog::browse);

    QObject::connect(imp().m_name_entry.get(), &Project_Name_Entry::state_changed, [this](){this->update();});
    QObject::connect(imp().m_location_entry.get(), &Project_Location_Entry::state_changed, [this](){this->update();});

    // Load the starting data
    imp().m_name_entry->setText(Fixed_Settings::default_project_name());
    imp().m_location_entry->setText(Fixed_Settings::default_project_location());

    // update the dialog
    update();
}

sak::New_Project_Dialog::New_Project_Dialog(QString const& a_name, QString const& a_location, QWidget* a_parent):
    New_Project_Dialog(a_parent)
{
    imp().m_name_entry->setText(a_name);
    imp().m_location_entry->setText(a_location);
}

sak::New_Project_Dialog::~New_Project_Dialog() = default;


// Interface
//============================================================
// Access the data we make this class to get.
QString sak::New_Project_Dialog::name() const
{
    return cimp().m_name_entry->text();
}

QString sak::New_Project_Dialog::location() const
{
    return cimp().m_location_entry->text();
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
    imp().m_location_entry->setText(l_result);
  }
}

// Slot for the entry widgets to inform that they're changed state.
void sak::New_Project_Dialog::update()
{
  if (imp().m_name_entry->is_valid())
  {
    if (imp().m_location_entry->is_valid())
    {
      QDir l_dir{location()};
      if (l_dir.cd(name()) && (QFileInfo(l_dir.filePath(name() + Fixed_Settings::project_file_extension())).exists()))
      {
        imp().m_finish_button->setEnabled(false);
        imp().m_warning->setText(u8"Cannot create a project here because one of this name already exists.");
      }
      else
      {
        imp().m_finish_button->setEnabled(true);
        imp().m_warning->setText(u8"");
      }
    }
    else
    {
      imp().m_finish_button->setEnabled(false);
      imp().m_warning->setText(u8"Location is not a valid existing directory.");
    }
  }
  else
  {
    imp().m_finish_button->setEnabled(false);
    imp().m_warning->setText(imp().m_name_entry->first_error());
  }
}
