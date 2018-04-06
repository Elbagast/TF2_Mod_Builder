#ifndef SAK_GUI_DIRECTORY_NAME_VALIDATOR_HPP
#define SAK_GUI_DIRECTORY_NAME_VALIDATOR_HPP

#include <QValidator>

namespace sak
{
  namespace gui
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

      // Interface
      //============================================================
      // Produce a string that describes the first error found in string that
      // stops it from being valid. String is empty if no errors.
      static QString first_error(QString const& a_string);
    };
  }
}

#endif // SAK_GUI_DIRECTORY_NAME_VALIDATOR_HPP
