#include "file_widget.hpp"

#include "file_manager.hpp"
#include "file_interface.hpp"
#include <QString>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include "common_data_widget.hpp"

//---------------------------------------------------------------------------
// File_Widget
//---------------------------------------------------------------------------
// Internal constants and implementation
//============================================================
namespace
{
    QString const c_buildpath_title{u8"Build Path"};
    QString const c_sourcepath_title{u8"Source File Path"};
}


namespace sak
{
    namespace
    {

        // Temporary
        class File_Data_Widget :
                public QWidget
        {
        public:
            explicit File_Data_Widget(File_Handle& a_handle, QWidget* a_parent = nullptr);
            ~File_Data_Widget() override;
            void update();
            void update_at(std::size_t a_section);
        private:
            File_Handle& m_handle;
            std::unique_ptr<QFormLayout> m_layout;
            std::unique_ptr<QLineEdit> m_buildpath_edit;
            std::unique_ptr<QLineEdit> m_sourcepath_edit;
        };

    }
}

sak::File_Data_Widget::File_Data_Widget(File_Handle& a_handle, QWidget* a_parent):
    QWidget(a_parent),
    m_handle{a_handle},
    m_layout{ std::make_unique<QFormLayout>(nullptr)},
    m_buildpath_edit{ std::make_unique<QLineEdit>(nullptr)},
    m_sourcepath_edit{ std::make_unique<QLineEdit>(nullptr)}
{
    m_layout->addRow(c_buildpath_title, m_buildpath_edit.get());
    m_layout->addRow(c_sourcepath_title, m_sourcepath_edit.get());
    this->setLayout(m_layout.get());

    // When the user has finished inputting, send the data to the handle.
    // The data change should come back to here as an update call, which means
    // if the name had to be changed the data in the line edit should be changed
    // to the final value.
    QObject::connect(m_buildpath_edit.get(), &QLineEdit::editingFinished, [this]()
    {
        this->m_handle.get().set_buildpath(this->m_buildpath_edit->text());
    });

    // When the user has finished inputting, send the data to the handle.
    QObject::connect(m_sourcepath_edit.get(), &QLineEdit::editingFinished, [this]()
    {
        this->m_handle.get().set_sourcepath(this->m_sourcepath_edit->text());
    });
    update();
}
sak::File_Data_Widget::~File_Data_Widget() = default;
void sak::File_Data_Widget::update()
{
    update_at(0);
    update_at(1);
}

void sak::File_Data_Widget::update_at(std::size_t a_section)
{
    switch(a_section)
    {
    case 0: m_buildpath_edit->setText(m_handle.cget().cget_buildpath()); break;
    case 1: m_sourcepath_edit->setText(m_handle.cget().cget_sourcepath()); break;
    default: break;
    }
}


// Pimpl Data
//============================================================
namespace sak
{
    class File_Widget::Implementation
    {
    public:
        File_Handle m_file;

        std::unique_ptr<QVBoxLayout> m_layout;
        std::unique_ptr<Common_Data_Widget<File_Handle>> m_common_data_widget;
        std::unique_ptr<File_Data_Widget> m_file_data_widget;

        explicit Implementation(File_Handle const& a_file):
            m_file{a_file},
            m_layout{ std::make_unique<QVBoxLayout>(nullptr)},
            m_common_data_widget{ std::make_unique<Common_Data_Widget<File_Handle>>(m_file, nullptr) },
            m_file_data_widget{ std::make_unique<File_Data_Widget>(m_file, nullptr) }
        {
            m_layout->addWidget(m_common_data_widget.get());
            m_layout->addWidget(m_file_data_widget.get());
            m_layout->addStretch();
        }

        void update()
        {
            m_common_data_widget->update();
            m_file_data_widget->update();
        }
        void update_name()
        {
            m_common_data_widget->update_name();
        }
        void update_description()
        {
            m_common_data_widget->update_description();
        }
        void update_data()
        {
            m_file_data_widget->update();
        }
        void update_data_at(std::size_t a_section)
        {
            m_file_data_widget->update_at(a_section);
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
void sak::File_Widget::update_name()
{
    imp().update_name();
}

void sak::File_Widget::update_description()
{
    imp().update_description();
}

void sak::File_Widget::update_data()
{
    imp().update_data();
}
void sak::File_Widget::update_data_at(std::size_t a_section)
{
    imp().update_data_at(a_section);
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
