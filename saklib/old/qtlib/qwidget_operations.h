#ifndef QWIDGET_OPERATIONS_H
#define QWIDGET_OPERATIONS_H

#include "../types.h"
#include <QWidget>

class QCheckBox;
class QSpinBox;
class QDoubleSpinBox;
class QLineEdit;

namespace saklib
{
    namespace Qtlib
    {
        /*
        Widget_Traits<T>
        ====================================================================================================
        How do we do what happens in Common_Traits for widgets? How do we setup generic changes (e.g.
        editingFinished() signal) so that they are consistant across all types?

        */

        template <typename T>
        class Widget_Traits
        {
        public:
            using widget_type = QWidget;
        };
    } // namespace Qtlib
} // namespace saklib

#endif // QWIDGET_OPERATIONS_H

