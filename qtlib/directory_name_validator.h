#ifndef DIRECTORY_NAME_VALIDATOR_H
#define DIRECTORY_NAME_VALIDATOR_H

#include <QValidator>

namespace qtlib
{
    //---------------------------------------------------------------------------
    // Directory_Name_Validator
    //---------------------------------------------------------------------------
    // Determines whether a QString is a valid directory name or not.

    class Directory_Name_Validator :
            public QValidator
    {
    public:
        // Special 6
        //============================================================
        ~Directory_Name_Validator() override;

        // QValidator overrides
        //============================================================
        //void fixup(QString& a_input) const override;

        QValidator::State validate(QString& a_input, int& a_position) const override;
    };
}


#endif // DIRECTORY_NAME_VALIDATOR_H
