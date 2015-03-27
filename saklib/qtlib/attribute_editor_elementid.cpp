#include "attribute_editor_elementid.h"
#include "project_widget.h"
#include "qstring_operations.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor_ElementID::Attribute_Editor_ElementID(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, parent),
    m_elementid(this->project_widget()->attribute_type_cast<ElementID>(this->attributeid())->value()),
    m_layout(std::make_unique<QHBoxLayout>()),
    m_button(std::make_unique<QPushButton>(this->button_text())),
    m_name_label(std::make_unique<QLabel>(this->name_label_text())),
    m_type_label(std::make_unique<QLabel>(this->type_label_text()))
{
    QObject::connect(m_button.get(), &QPushButton::clicked,
                     this, &Attribute_Editor_ElementID::slot_clicked);

    m_layout->addWidget(m_button.get());
    m_layout->addWidget(m_name_label.get());
    m_layout->addWidget(m_type_label.get());

    m_layout->setContentsMargins(0,0,0,0);
    this->setLayout(m_layout.get());
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}
Saklib::Qtlib::Attribute_Editor_ElementID::~Attribute_Editor_ElementID() = default;


void Saklib::Qtlib::Attribute_Editor_ElementID::v_refresh_data()
{
    auto const data_value = this->project_widget()->attribute_type_cast<ElementID>(this->attributeid())->value();
    if (m_elementid != data_value)
    {
        //refresh the representation
        m_elementid = data_value;
        m_button->setText(button_text());
        m_name_label->setText(name_label_text());
        m_type_label->setText(type_label_text());
    }
}

void Saklib::Qtlib::Attribute_Editor_ElementID::slot_clicked()
{
    if (m_elementid.is_valid() && project_widget()->is_valid(m_elementid))
    {
       this->project_widget()->open_editor(m_elementid);
    }
    else
    {
        // this would mean it wants you to replace the element...
    }
}


// Internal
//============================================================
QString Saklib::Qtlib::Attribute_Editor_ElementID::button_text() const
{
    if (m_elementid.is_valid() && project_widget()->is_valid(m_elementid))
    {
       return QString("Edit");
    }
    else
    {
        return QString("Make Element");
    }
}
QString Saklib::Qtlib::Attribute_Editor_ElementID::name_label_text() const
{
    static QString const label_front{"Name: "};
    if (m_elementid.is_valid() && project_widget()->is_valid(m_elementid))
    {
        return label_front + to_QString(project_widget()->element_name(m_elementid));
    }
    else
    {
        return QString();
    }
}
QString Saklib::Qtlib::Attribute_Editor_ElementID::type_label_text() const
{
    static QString const label_front{"Type: "};
    if (m_elementid.is_valid() && project_widget()->is_valid(m_elementid))
    {
        return label_front + to_QString(project_widget()->element_type(m_elementid));
    }
    else
    {
        return QString();
    }
}
