#ifndef VALIDATING_LINE_EDIT_H
#define VALIDATING_LINE_EDIT_H

#include <QLineEdit>
#include "state_changer.h"

namespace qtlib
{
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

    class Validating_Line_Edit :
            public QLineEdit
    {
        Q_OBJECT
    public:
        // Special 6
        //============================================================
        // Construct without a validator or a state changer.
        explicit Validating_Line_Edit(QWidget* a_parent = nullptr);

        // Construct wtih a validator and state changer.
        Validating_Line_Edit(QValidator* a_validator, abstract::State_Changer<QLineEdit>* a_state_changer, QWidget* a_parent = nullptr);

        ~Validating_Line_Edit() override;

        // Interface
        //============================================================
        // Access the current validator. Returns nullptr if there isn't one.
        QValidator* get_validator() const;

        // Set the validator. If nullptr, the current one is removed. If it not nullptr,
        // the internal state changer is replaced. In both cases update_state is then
        // called. Does not take ownership of the state changer.
        void set_validator(QValidator* a_validator);

        // Access the current state changer. Returns nullptr if there isn't one.
        abstract::State_Changer<QLineEdit>* get_state_changer() const;

        // Set the state changer. If nullptr, the current one is removed and this is
        // is left in the last state that was set. If it not nullptr, the internal
        // state changer is replaced and and then update_state is called. Does not
        // take ownership of the state changer.
        void set_state_changer(abstract::State_Changer<QLineEdit>* a_state_changer);

        // Is the current text valid? This is the value determined the last time
        // the text changed by any means.
        bool is_valid() const;

    signals:
        // Whenever QLineEdit::textChanged is emitted, the text is tested for validity.
        // This results in two signals being emitted:

        // Any time text is changed the state is emitted.
        void state_changed(bool a_new_state);

        // Any time the state actuallly changes - regardless of how many times text
        // has been changed for this to happen - this is emitted.
        void state_flipped(bool a_new_state);

    private slots:
        // QLineEdit::textChanged is linked to this slot to make the local state changes.
        void update_state(QString const& a_new_text);

    private:
        // Hide QLineEdit public interface that no longer makes sense.
        using QLineEdit::validator;
        using QLineEdit::setValidator;

        // Data Members
        //============================================================
        bool m_validity_state;
        QValidator* m_validator;
        abstract::State_Changer<QLineEdit>* m_state_changer;
    };
}

#endif // VALIDATING_LINE_EDIT_H
