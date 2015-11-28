#ifndef SAKLIB_IATTRIBUTE_MAKER_H
#define SAKLIB_IATTRIBUTE_MAKER_H

#include <memory>

namespace saklib
{
    class IAttribute_Base;
    /*
    IAttribute_Maker
    ====================================================================================================
    The base interface for Attribute objects that will be stored as IAttribute pointers.
    */
    class IAttribute_Maker
    {
    public:
        virtual ~IAttribute_Maker() = default;

        std::unique_ptr<IAttribute_Base> make_attribute() const { return v_make_attribute(); }
    protected:
        virtual std::unique_ptr<IAttribute_Base> v_make_attribute() const = 0;
    };

} // namespace saklib

#endif // SAKLIB_IATTRIBUTE_MAKER_H

