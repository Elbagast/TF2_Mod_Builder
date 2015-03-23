#ifndef WINDOWTITLE_H
#define WINDOWTITLE_H
/*
WindowTitle
============================================================
Class dedicated to managing the title of a QMainWindow. It encapsulates everything needed to
keep the title up to date and changes the title of the supplied window only when there is a
need to change it.

Call setUnsavedEdits when the state of edits changes and setVariableTitle when the variable
part of the title changes (e.g. filename / path) and clearVariableTitle when there is no
file open.

The functionality to update the window title is done via the given QMainWindow*, this could
be done with a signal but that seems like overkill given this class has no reason to exist
without there being a window to affect.

Call hasUnsavedEdits when you need the edit state.

Title format:

variableTitle is empty: [fixedTitle]
no unsaved edits:       [variableTitle][spacer][fixedTitle]
has unsaved edits:      [editsMarker][variableTitle][spacer][fixedTitle]

*/
#include <QPointer>
#include <QString>
class QMainWindow;

namespace Saklib
{
    namespace Qtlib
    {
        class WindowTitle
        {
        public:
            // Special 6
            //============================================================
            WindowTitle(QMainWindow* window,
                        QString const& fixedTitle,
                        QString const& editsMarker = QString("*"),
                        QString const& spacer = QString(" - "),
                        QString const& variableTitle = QString() );

            // Interface
            //============================================================
            // Set the various components, the full titles and the title for the associated
            // window are changed if necessary.
            void set_window(QMainWindow* window);
            void set_fixed_title(QString const& fixedTitle);
            void set_edits_marker(QString const& editsMarker);
            void set_spacer(QString const& spacer);
            void set_variable_title(QString const& variable);
            void set_unsaved_edits(bool state);

            // Equivalent to setVariableTitle(QString());
            void clear_variable_title();

            // Access the current edit state for use elsewhere
            bool has_unsaved_edits() const;
            // Get the currently appropriate title
            QString const& full_title() const;

        private:
            // Rebuild the stored full titles
            void update_full_titles();
            // Update the title of the window with what is appropriate
            void update_window_title();

            QPointer<QMainWindow> m_window;
            QString m_fixedTitle;
            QString m_editsMarker;
            QString m_spacer;
            QString m_variableTitle;
            bool m_unsavedEdits;

            // The two full titles are stored pre-built
            QString m_fullTitle;
            QString m_fullTitleUnsavedEdits;
        };

    } // namespace Qtlib
} // namespace Saklib

#endif // WINDOWTITLE_H
