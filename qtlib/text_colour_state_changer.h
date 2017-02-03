#ifndef TEXT_COLOUR_STATE_CHANGER_H
#define TEXT_COLOUR_STATE_CHANGER_H

#include "state_changer.h"
#include <QColor>
class QLineEdit;

namespace qtlib
{
    //---------------------------------------------------------------------------
    // Text_Colour_State_Changer
    //---------------------------------------------------------------------------
    // Change the text colour of a QLineEdit between valid and invalid input colours.
    class Text_Colour_State_Changer :
            public abstract::State_Changer<QLineEdit>
    {
    public:
        Text_Colour_State_Changer(QColor a_valid, QColor a_invalid);
        ~Text_Colour_State_Changer() override;

        QColor valid_text_colour() const;
        QColor invalid_text_color() const;

        void set_to_valid(QLineEdit& a_line_edit) override;
        void set_to_invalid(QLineEdit& a_line_edit) override;

    private:
        QColor m_valid_colour;
        QColor m_invalid_colour;
    };
}

#endif // TEXT_COLOUR_STATE_CHANGER_H
