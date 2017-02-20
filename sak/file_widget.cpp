#include "file_widget.h"

#include "file_manager.h"
#include <QString>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include "common_data_widget.h"

//---------------------------------------------------------------------------
// File_Widget
//---------------------------------------------------------------------------
// Internal constants and implementation
//============================================================
namespace sak
{
    namespace
    {

        // dummy for now
        class File_Data_Widget :
                public QLabel
        {
        public:
            explicit File_Data_Widget(File_Handle& a_file, QWidget* a_parent = nullptr):
                QLabel(u8"This is the File_Data_Widget", a_parent),
                m_file{a_file}
            {}
            ~File_Data_Widget() override = default;
            void update() {}
            void update_at(std::size_t) {}
        private:
            File_Handle& m_file;
        };

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
