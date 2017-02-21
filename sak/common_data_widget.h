#ifndef COMMON_DATA_WIDGET_H
#define COMMON_DATA_WIDGET_H

#include <memory>
#include <QWidget>
class QLabel;
class QLineEdit;
class QFormLayout;
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

#endif // COMMON_DATA_WIDGET_H
