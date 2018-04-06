#ifndef SAK_GUI_LINE_EDIT_HPP
#define SAK_GUI_LINE_EDIT_HPP

#include <QLineEdit>

namespace sak
{
  namespace gui
  {
    //---------------------------------------------------------------------------
    // Line_Edit
    //---------------------------------------------------------------------------
    // Line edit widget emits one additional signal - when it looses focus. This
    // allows you to check its value if focus was lost while the data was invalid
    // i.e. when losing focus while the contents are QValidator::Intermediate

    class Line_Edit :
        public QLineEdit
    {
      Q_OBJECT
    public:
      // Special 6
      //============================================================
      // Construct without a validator or a state changer.
      explicit Line_Edit(QWidget* a_parent = nullptr);
      explicit Line_Edit(QString const& a_contents, QWidget* a_parent = nullptr);

      ~Line_Edit() override;

      Line_Edit(Line_Edit const&) = delete;
      Line_Edit& operator=(Line_Edit const&) = delete;

      Line_Edit(Line_Edit &&) = delete;
      Line_Edit& operator=(Line_Edit &&) = delete;

      // Virtuals
      //============================================================
    protected:
      void focusOutEvent(QFocusEvent* a_event) override;

    signals:
      void lostFocus();
      void editingFailed();
    };
  }
}

#endif // SAK_GUI_LINE_EDIT_HPP
