#ifndef SAK_GUI_EXISTING_DIRECTORY_VALIDATOR_HPP
#define SAK_GUI_EXISTING_DIRECTORY_VALIDATOR_HPP

#include <QValidator>

namespace sak
{
  namespace gui
  {
    //---------------------------------------------------------------------------
    // Existing_Directory_Validator
    //---------------------------------------------------------------------------
    // Determines whether a QString is currently existing directory or not.

    class Existing_Directory_Validator :
        public QValidator
    {
    public:
      // Special 6
      //============================================================
      ~Existing_Directory_Validator() override;

      // QValidator overrides
      //============================================================
      //void fixup(QString& a_input) const override;

      QValidator::State validate(QString& a_input, int& a_position) const override;
    };
  }
}

#endif // SAK_GUI_EXISTING_DIRECTORY_VALIDATOR_HPP
