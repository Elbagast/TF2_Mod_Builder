#ifndef COMMON_DATA_WIDGET_H
#define COMMON_DATA_WIDGET_H

#include <memory>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
class QString;

namespace sak
{
    //---------------------------------------------------------------------------
    // Common_Data_Widget<Handle>
    //---------------------------------------------------------------------------
    // This template instantiates a widget that contains name and description
    // display and editing through a handle class.

    namespace internal
    {
        QString common_data_widget_name_title();
        QString common_data_widget_description_title();
    }

    template <typename H>
    class Common_Data_Widget :
            public QWidget
    {
    public:
        using handle_type = H;

        explicit Common_Data_Widget(handle_type& a_handle, QWidget* a_parent = nullptr);
        ~Common_Data_Widget() override;

        void update();
        void update_name();
        void update_description();
    private:
        handle_type& m_handle;
        std::unique_ptr<QFormLayout> m_layout;
        std::unique_ptr<QLabel> m_name_label;
        std::unique_ptr<QLineEdit> m_name_edit;
        std::unique_ptr<QLabel> m_description_label;
        std::unique_ptr<QLineEdit> m_description_edit;
    };
}

template <typename H>
sak::Common_Data_Widget<H>::Common_Data_Widget(handle_type& a_handle, QWidget* a_parent):
    QWidget(a_parent),
    m_handle{a_handle},
    m_layout{ std::make_unique<QFormLayout>(nullptr)},
    m_name_label{ std::make_unique<QLabel>(internal::common_data_widget_name_title(),nullptr)},
    m_name_edit{ std::make_unique<QLineEdit>(nullptr)},
    m_description_label{ std::make_unique<QLabel>(internal::common_data_widget_description_title(),nullptr)},
    m_description_edit{ std::make_unique<QLineEdit>(nullptr)}
{
    m_layout->addRow(m_name_label.get(), m_name_edit.get());
    m_layout->addRow(m_description_label.get(), m_description_edit.get());
    this->setLayout(m_layout.get());

    // When the user has finished inputting, send the data to the handle.
    // The data change should come back to here as an update call, which means
    // if the name had to be changed the data in the line edit should be changed
    // to the final value.
    QObject::connect(m_name_edit.get(), &QLineEdit::editingFinished, [this]()
    {
        this->m_handle.get().set_name(this->m_name_edit->text());
    });

    // When the user has finished inputting, send the data to the handle.
    QObject::connect(m_description_edit.get(), &QLineEdit::editingFinished, [this]()
    {
        this->m_handle.get().set_description(this->m_description_edit->text());
    });
    update();
}

template <typename H>
sak::Common_Data_Widget<H>::~Common_Data_Widget() = default;

template <typename H>
void sak::Common_Data_Widget<H>::update()
{
    update_name();
    update_description();
}

template <typename H>
void sak::Common_Data_Widget<H>::update_name()
{
    m_name_edit->setText(m_handle.cget().cget_name());
}

template <typename H>
void sak::Common_Data_Widget<H>::update_description()
{
    m_description_edit->setText(m_handle.cget().cget_description());
}


#endif // COMMON_DATA_WIDGET_H
