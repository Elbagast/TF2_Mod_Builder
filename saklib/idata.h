#ifndef IDATA_H
#define IDATA_H

#include "types.h"
#include "nodeid.h"
#include "all_type_traits.h"

namespace Saklib
{
    /*
    IData
    ====================================================================================================
    Class which describes the interface for asking questions about a data value
    */
    class IData
    {
    public:
        // Special 6
        //============================================================
        virtual ~IData() = 0;

        // Virtual Interface
        //============================================================
        virtual Type_Enum type_enum() const = 0;
        virtual String type_string() const = 0;
        virtual bool user_can_set_data() const = 0;
        virtual void set_user_can_set_data(bool state) = 0;
    };

} // namespace Saklib

Saklib::IData::~IData() = default;

#endif // IDATA_H

