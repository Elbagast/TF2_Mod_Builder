#ifndef SAKLIB_IOBJECT_POINTER_STORAGE_H
#define SAKLIB_IOBJECT_POINTER_STORAGE_H

#include "../types.h"

namespace saklib
{
    /*
    IObject_Pointer_Storage<T>
    ====================================================================================================
    */
    template <typename T>
    class IObject_Pointer_Storage_R
    {
    public:
        // Typedefs
        //============================================================
        using stored_type = std::unique_ptr<T>;
        using storage_type = std::vector<stored_type>;
        using pointer = T*;
        using const_pointer = T const*;

        // Special 6
        //============================================================
        virtual ~IObject_Pointer_Storage_R() = default;

        // Interface
        //============================================================
        size_type size() const                              { return v_size(); }
        bool empty() const                                  { return v_empty(); }
        bool has_index(size_type index) const               { return v_has_index(index); }

        pointer at(size_type index)                         { return v_at(index); }
        const_pointer cat(size_type index) const            { return v_cat(index); }

    protected:
        // Virtuals
        //============================================================
        virtual size_type v_size() const = 0;
        virtual bool v_empty() const = 0;
        virtual bool v_has_index(size_type index) const = 0;
        virtual pointer v_at(size_type index) = 0;
        virtual const_pointer v_cat(size_type index) const = 0;
    };


    /*
    IObject_Pointer_Storage_RW<T>
    ====================================================================================================
    */
    template <typename T>
    class IObject_Pointer_Storage_RW:
            public virtual IObject_Pointer_Storage_R<T>
    {
    public:
        // Typedefs
        //============================================================
        using stored_type = typename IObject_Pointer_Storage_R<T>::stored_type;
        using storage_type = typename IObject_Pointer_Storage_R<T>::storage_type;
        using pointer = typename IObject_Pointer_Storage_R<T>::pointer;
        using const_pointer = typename IObject_Pointer_Storage_R<T>::const_pointer;

        // Special 6
        //============================================================
        ~IObject_Pointer_Storage_RW() override = default;

        // Interface
        //============================================================
        void push_back(stored_type& a_pointer)     { v_push_back(a_pointer); }
        void push_back(stored_type&& a_pointer)    { v_push_back(std::forward<std::unique_ptr<stored_type>>(a_pointer)); }
        //void push_back(pointer a_pointer)                           { v_push_back(a_pointer); }
        void clear()                                                { v_clear(); }
    protected:
        // Virtuals
        //============================================================
        virtual void v_push_back(stored_type& a_pointer) = 0;
        virtual void v_push_back(stored_type&& a_pointer) = 0;
        //virtual void v_push_back(pointer a_pointer) = 0;
        virtual void v_clear() = 0;
    };


} // namespace saklib

#endif // IOBJECT_POINTER_STORAGE_H

