#ifndef SAKLIB_IOBJECT_TYPE_H
#define SAKLIB_IOBJECT_TYPE_H

#include "../types.h"
#include "../common_traits.h"

namespace saklib
{
    /*
    IObject_Type_R
    ====================================================================================================
    Interface for access to an Object's type, read only access
    */
    class IObject_Type_R
    {
    public:
        virtual ~IObject_Type_R() = default;

        String const& type() const              { return v_type(); }
    protected:
        virtual String const& v_type() const = 0;
    };

    /*
    IObject_Type_RW
    ====================================================================================================
    Interface for access to an Object's type, read and write access
    */
    class IObject_Type_RW :
            public virtual IObject_Type_R
    {
    public:
        ~IObject_Type_RW() override = default;

        void set_type(String const& arg_type)   { v_set_type(arg_type); }
    protected:
        virtual void v_set_type(String const& arg_type) = 0;
    };

} // namespace saklib

#endif // SAKLIB_IOBJECT_TYPE_H

