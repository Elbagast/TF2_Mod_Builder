#include "new_project_dialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>

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

class sak::Project_Name_Entry :
        public QLineEdit
{
public:
    explicit Project_Name_Entry(QWidget* a_parent = nullptr):
        QLineEdit(a_parent)
    {}
    ~Project_Name_Entry() override = default;
};

class sak::Project_Location_Entry :
        public QLineEdit
{
public:
    explicit Project_Location_Entry(QWidget* a_parent = nullptr):
        QLineEdit(a_parent)
    {}
    ~Project_Location_Entry() override = default;
};


sak::New_Project_Dialog::New_Project_Dialog(QWidget *parent) :
    QDialog(parent),
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

    m_finish_button->setEnabled(false);
}

sak::New_Project_Dialog::~New_Project_Dialog() = default;
