#include "text_colour_state_changer.hpp"
#include <QLineEdit>

//---------------------------------------------------------------------------
// Text_Colour_State_Changer
//---------------------------------------------------------------------------
// Change the text colour of a QLineEdit between valid and invalid input colours.
qtlib::Text_Colour_State_Changer::Text_Colour_State_Changer(QColor a_valid, QColor a_invalid):
    abstract::State_Changer<QLineEdit>(),
    m_valid_colour{a_valid},
    m_invalid_colour{a_invalid}
{}

qtlib::Text_Colour_State_Changer::~Text_Colour_State_Changer() = default;

QColor qtlib::Text_Colour_State_Changer::valid_text_colour() const
{
    return m_valid_colour;
}

QColor qtlib::Text_Colour_State_Changer::invalid_text_color() const
{
    return m_invalid_colour;
}

void qtlib::Text_Colour_State_Changer::set_to_valid(QLineEdit& a_line_edit)
{
    auto l_palette = a_line_edit.palette();
    l_palette.setColor(QPalette::Text, m_valid_colour);
    a_line_edit.setPalette(l_palette);
}

void qtlib::Text_Colour_State_Changer::set_to_invalid(QLineEdit& a_line_edit)
{
    auto l_palette = a_line_edit.palette();
    l_palette.setColor(QPalette::Text, m_invalid_colour);
    a_line_edit.setPalette(l_palette);
}
