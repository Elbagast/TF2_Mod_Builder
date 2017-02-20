#include "common_data_widget.h"

#include <QString>

QString sak::internal::common_data_widget_name_title()
{
    static QString const s_name_title{u8"Name"};
    return s_name_title;
}

QString sak::internal::common_data_widget_description_title()

{
    static QString const s_description_title{u8"Description"};
    return s_description_title;
}
