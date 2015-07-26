#ifndef IDATA_ACCESS_H
#define IDATA_ACCESS_H

namespace Saklib
{
    class IData_Access
    {
    public:
        virtual ~IData_Access() = 0;

        // Virtual Interface
        //============================================================
        virtual Type_Enum type_enum() const = 0;
        virtual String type_string() const = 0;
        virtual bool user_can_set_data() const = 0;
        virtual void set_user_can_set_data(bool state) = 0;
    };

} // namespace Saklib

Saklib::IData_Access::~IData_Access() = default;

#endif // IDATA_ACCESS_H

