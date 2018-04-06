#include "text_colour_state_changer.hpp"
#include <QLineEdit>

//---------------------------------------------------------------------------
// Text_Colour_State_Changer
//---------------------------------------------------------------------------
// Change the text colour of a QLineEdit between valid and invalid input colours.
sak::gui::Text_Colour_State_Changer::Text_Colour_State_Changer(QColor a_valid, QColor a_invalid):
    Abstract_State_Changer<QLineEdit>(),
    m_valid_colour{a_valid},
    m_invalid_colour{a_invalid}
{}

sak::gui::Text_Colour_State_Changer::~Text_Colour_State_Changer() = default;

QColor sak::gui::Text_Colour_State_Changer::valid_text_colour() const
{
    return m_valid_colour;
}

QColor sak::gui::Text_Colour_State_Changer::invalid_text_color() const
{
    return m_invalid_colour;
}

void sak::gui::Text_Colour_State_Changer::set_to_valid(QLineEdit& a_line_edit)
{
    auto l_palette = a_line_edit.palette();
    l_palette.setColor(QPalette::Text, m_valid_colour);
    a_line_edit.setPalette(l_palette);
}

void sak::gui::Text_Colour_State_Changer::set_to_invalid(QLineEdit& a_line_edit)
{
    auto l_palette = a_line_edit.palette();
    l_palette.setColor(QPalette::Text, m_invalid_colour);
    a_line_edit.setPalette(l_palette);
}
