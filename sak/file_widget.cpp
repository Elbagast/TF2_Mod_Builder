#include "file_widget.h"

#include "file_manager.h"
#include <QString>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>

//---------------------------------------------------------------------------
// File_Widget
//---------------------------------------------------------------------------
// Internal constants and implementation
//============================================================
namespace
{
    QString const c_title_name{u8"Name"};
    QString const c_title_description{u8"Description"};
}
// Pimpl Data
//============================================================
namespace sak
{
    class File_Widget::Implementation
    {
    public:
        File_Handle m_file;

        std::unique_ptr<QFormLayout> m_layout;
        std::unique_ptr<QLabel> m_name_label;
        std::unique_ptr<QLineEdit> m_name_edit;
        std::unique_ptr<QLabel> m_description_label;
        std::unique_ptr<QLineEdit> m_description_edit;

        explicit Implementation(File_Handle const& a_file):
            m_file{a_file},
            m_layout{ std::make_unique<QFormLayout>(nullptr)},
            m_name_label{ std::make_unique<QLabel>(c_title_name,nullptr)},
            m_name_edit{ std::make_unique<QLineEdit>(nullptr)},
            m_description_label{ std::make_unique<QLabel>(c_title_description,nullptr)},
            m_description_edit{ std::make_unique<QLineEdit>(nullptr)}
        {
            m_layout->addRow(m_name_label.get(), m_name_edit.get());
            m_layout->addRow(m_description_label.get(), m_description_edit.get());

            // When the user has finished inputting, send the data to the handle.
            // The data change should come back to here as an update call, which means
            // if the name had to be changed the data in the line edit should be changed
            // to the final value.
            QObject::connect(m_name_edit.get(), &QLineEdit::editingFinished, [this]()
            {
                this->m_file.get().set_name(this->m_name_edit->text());
            });

            // When the user has finished inputting, send the data to the handle.
            QObject::connect(m_description_edit.get(), &QLineEdit::editingFinished, [this]()
            {
                this->m_file.get().set_description(this->m_description_edit->text());
            });
            update();
        }

        void update()
        {
            m_name_edit->setText(m_file.cget().cget_name());
            m_description_edit->setText(m_file.cget().cget_description());
        }
    };
}
// Special 6
//============================================================
sak::File_Widget::File_Widget(File_Handle const& a_file, QWidget* a_parent):
    QWidget(a_parent),
    m_data{std::make_unique<Implementation>(a_file)}
{
    this->setLayout(imp().m_layout.get());
}
sak::File_Widget::~File_Widget() = default;

// Interface
//============================================================
sak::File_Handle& sak::File_Widget::get_file()
{
    return imp().m_file;
}

sak::File_Handle const& sak::File_Widget::cget_file() const
{
    return cimp().m_file;
}

// update all the data to match the handle.
void sak::File_Widget::update()
{
    imp().update();
}


bool sak::File_Widget_Less_By_Name::operator()(std::unique_ptr<File_Widget> const& a_lhs, std::unique_ptr<File_Widget> const& a_rhs) const
{
    return File_Handle_Less_By_Name()(a_lhs->cget_file(),a_rhs->cget_file());
}


sak::File_Widget_Equals_Handle::File_Widget_Equals_Handle(File_Handle const& a_file):
    m_file{a_file}
{}

bool sak::File_Widget_Equals_Handle::operator()(std::unique_ptr<File_Widget> const& a_widget) const
{
    return m_file == a_widget->cget_file();
}
