#ifndef IOBJECT_HANDLE_H
#define IOBJECT_HANDLE_H

namespace saklib
{
    /*
    IObject_Handle_R<T>
    ====================================================================================================
    Interface for access to an Object's name, read only access
    */
    template <typename T>
    class IObject_Handle_R
    {
    public:
        using handle_type = T;

        virtual ~IObject_Handle_R() = default;

        handle_type const& name() const              { return v_name(); }
    protected:
        virtual handle_type const& v_name() const = 0;
    };

    /*
    IObject_Handle_RW<T>
    ====================================================================================================
    Interface for access to an Object's name, read and write access
    */
    template <typename T>
    class IObject_Handle_RW :
            public virtual IObject_Handle_R<T>
    {
    public:
        using handle_type = typename IObject_Handle_R<T>::handle_type;

        ~IObject_Handle_RW() override = default;

        void set_handle(handle_type const& a_handle)   { v_set_handle(a_handle); }
    protected:
        virtual void v_set_handle(handle_type const& a_handle) = 0;
    };

} // namespace saklib


#endif // I_OBJECT_HANDLE_H

