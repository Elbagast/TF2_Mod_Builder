#include "validating_line_edit.h"

#include <QValidator>
#include "state_changer.h"

//---------------------------------------------------------------------------
// Validating_Line_Edit
//---------------------------------------------------------------------------
// Line edit widget that accepts all inputs. If it is supplied with a QValidator
// it will test the input with that QValidator and emit signals when the input
// changes state between valid and invalid.
//
// This is different behaviour to using QLineEdit directly, as that will use
// the QValidator to prevent the user from even entering invalid text.
//
// If supplied with a State_Changer it will use that to change the state of
// the base class QLineEdit to match the detected state.

// Special 6
//============================================================
// Construct without a validator or a state changer.
qtlib::Validating_Line_Edit::Validating_Line_Edit(QWidget* a_parent):
    QLineEdit(a_parent),
    m_validity_state{true},
    m_validator{nullptr},
    m_state_changer{nullptr}
{
    QObject::connect(this, &QLineEdit::textChanged, this, &Validating_Line_Edit::update_state);
}

// Construct wtih a validator and state changer.
qtlib::Validating_Line_Edit::Validating_Line_Edit(QValidator* a_validator, abstract::State_Changer<QLineEdit>* a_state_changer, QWidget* a_parent):
    Validating_Line_Edit(a_parent)
{
    set_validator(a_validator);
    set_state_changer(a_state_changer);
}


qtlib::Validating_Line_Edit::~Validating_Line_Edit() = default;

// Interface
//============================================================
// Access the current validator. Returns nullptr if there isn't one.
QValidator* qtlib::Validating_Line_Edit::get_validator() const
{
    return m_validator;
}

// Set the validator. If nullptr, the current one is removed. If it not nullptr,
// the internal state changer is replaced. In both cases update_state is then
// called. Does not take ownership of the state changer.
void qtlib::Validating_Line_Edit::set_validator(QValidator* a_validator)
{
    m_validator = a_validator;
    update_state(this->text());
}

// Access the current state changer. Returns nullptr if there isn't one.
qtlib::abstract::State_Changer<QLineEdit>* qtlib::Validating_Line_Edit::get_state_changer() const
{
    return m_state_changer;
}

// Set the state changer. If nullptr, the current one is removed and this is
// is left in the last state that was set. If it not nullptr, the internal
// state changer is replaced and and then update_state is called. Does not
// take ownership of the state changer.
void qtlib::Validating_Line_Edit::set_state_changer(abstract::State_Changer<QLineEdit>* a_state_changer)
{
    m_state_changer = a_state_changer;
    update_state(this->text());
}

// Is the current text valid? This is the value determined the last time
// the text changed by any means.
bool qtlib::Validating_Line_Edit::is_valid() const
{
    return m_validity_state;
}

// QLineEdit::textChanged is linked to this slot to make the local state changes.
void qtlib::Validating_Line_Edit::update_state(QString const& a_new_text)
{
    bool l_old_state{m_validity_state};
    // if we have a validator, validate the input.
    if (m_validator)
    {
        QString l_text{a_new_text};
        int l_pos{0};
        if (m_validator->validate(l_text,l_pos) == QValidator::Acceptable)
        {
            m_validity_state = true;

        }
        else
        {
            m_validity_state = false;
        }
    }
    // else its assumed to be valid.
    else
    {
        m_validity_state = true;
    }

    // if we have a state changer, change the state.
    if (m_state_changer)
    {
        if (m_validity_state)
        {
            m_state_changer->set_to_valid(*this);
        }
        else
        {
            m_state_changer->set_to_invalid(*this);
        }
    }
    // Emit the new state
    emit state_changed(m_validity_state);

    // If the state changed emit the signal.
    if (l_old_state != m_validity_state)
    {
        emit state_flipped(m_validity_state);
    }

}

