#ifndef SAKLIB_IOBJECT_NAME_H
#define SAKLIB_IOBJECT_NAME_H

#include "../types.h"
#include "../common_traits.h"

namespace saklib
{
    /*
    IObject_Name_R
    ====================================================================================================
    Interface for access to an Object's name, read only access
    */
    class IObject_Name_R
    {
    public:
        virtual ~IObject_Name_R() = default;

        String const& name() const              { return v_name(); }
    protected:
        virtual String const& v_name() const = 0;
    };

    /*
    IObject_Name_RW
    ====================================================================================================
    Interface for access to an Object's name, read and write access
    */
    class IObject_Name_RW :
            public virtual IObject_Name_R
    {
    public:
        ~IObject_Name_RW() override = default;

        void set_name(String const& arg_name)   { v_set_name(arg_name); }
    protected:
        virtual void v_set_name(String const& arg_name) = 0;
    };

} // namespace saklib

#endif // SAKLIB_IOBJECT_NAME_H

