#ifndef FILE_H
#define FILE_H

#include "fwd_file.h"
#include "common_data.h"

namespace sak
{
    //---------------------------------------------------------------------------
    // File
    //---------------------------------------------------------------------------
    //

    class File
    {
    public:
        File();
        explicit File(QString const& a_name, QString const& a_description = QString());

        Common_Data& get_common_data();
        Common_Data const& cget_common_data() const;
    private:
        Common_Data m_common_data;
    };
}
#endif // FILE_H
