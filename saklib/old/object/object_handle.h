#ifndef OBJECT_HANDLE_H
#define OBJECT_HANDLE_H

#include "iobject_handle.h"

namespace saklib
{
    namespace local
    {
        /*
        Object_Handle_R<T>
        ====================================================================================================
        Implementation of a locally stored Object name
        */
        template <typename T>
        class Object_Handle_R :
                public virtual IObject_Handle_R<T>
        {
        public:
            // Special 6
            //============================================================
            explicit Object_Handle_R(handle_type const& a_handle):
                IObject_Handle_R<T>(),
                m_handle(a_handle)
            {}
            ~Object_Handle_R() override = default;

        protected:
             handle_type const& v_handle() const override              { return m_handle; }
        private:
             handle_type m_handle;
        };

        /*
        Object_Handle_RW<T>
        ====================================================================================================
        Implementation of a locally stored Object name
        */
        template <typename T>
        class Object_Handle_RW :
                public virtual IObject_Handle_RW<T>
        {
        public:
            // Special 6
            //============================================================
            Object_Handle_RW():
                IObject_Handle_RW<T>(),
                m_handle()
            {}
            explicit Object_Handle_RW(handle_type const& a_handle):
                IObject_Handle_RW<T>(),
                m_handle(a_name)
            {}
            ~Object_Handle_RW() override = default;

        protected:
             handle_type const& v_handle() const override              { return m_handle; }
             void v_set_handle(handle_type const& a_handle) override     { m_handle = a_handle; }
        private:
             handle_type m_handle;
        };

    } // namespace local


    namespace remote
    {
        /*
        Object_Name_R
        ====================================================================================================
        Implementation of a remotely stored Object name
        */
        template <typename T>
        class Object_Handle_R :
                public virtual IObject_Handle_R<T>
        {
        public:
            // Special 6
            //============================================================
           explicit  Object_Handle_R(IObject_Handle_R<T> const& a_interface):
                IObject_Handle_R<T>(),
                mr_interface(a_interface)
            {}
            ~Object_Handle_R() override = default;

        protected:
             handle_type const& v_handle() const override              { return mr_interface.handle(); }
        private:
             IObject_Handle_R<T> const& mr_interface;
        };

        /*
        Object_Name_RW
        ====================================================================================================
        Implementation of a remotely stored Object name
        */
        template <typename T>
        class Object_Handle_RW :
                public virtual IObject_Handle_RW<T>
        {
        public:
            // Special 6
            //============================================================
            explicit Object_Handle_RW(Object_Handle_RW<T>& a_interface):
                IObject_Handle_RW<T>(),
                mr_interface(a_interface)
            {}
            ~Object_Handle_RW() override = default;

        protected:
             handle_type const& v_handle() const override              { return mr_interface.handle(); }
             void v_set_handle(handle_type const& a_handle) override     { mr_interface.set_handle(a_handle); }
        private:
             Object_Handle_RW<T>& mr_interface;
        };

    } // namespace remote

} // namespace saklib

#endif // OBJECT_HANDLE_H

