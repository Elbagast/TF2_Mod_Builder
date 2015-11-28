#ifndef SAKLIB_OBJECT_TYPE_H
#define SAKLIB_OBJECT_TYPE_H

#include "iobject_type.h"

namespace saklib
{
    namespace local
    {
        /*
        Object_Type_R
        ====================================================================================================
        Implementation of a locally stored Object type
        */
        class Object_Type_R :
                public virtual IObject_Type_R
        {
        public:
            // Special 6
            //============================================================
            explicit Object_Type_R(String const& a_type):
                IObject_Type_R(),
                m_type(a_type)
            {}
            ~Object_Type_R() override = default;

        protected:
             String const& v_type() const override              { return m_type; }
        private:
             String m_type;
        };

        /*
        Object_Type_RW
        ====================================================================================================
        Implementation of a locally stored Object type
        */
        class Object_Type_RW :
                public virtual IObject_Type_RW
        {
        public:
            // Special 6
            //============================================================
            Object_Type_RW():
                IObject_Type_RW(),
                m_type()
            {}
            explicit Object_Type_RW(String const& a_type):
                IObject_Type_RW(),
                m_type(a_type)
            {}
            ~Object_Type_RW() override = default;

        protected:
             String const& v_type() const override              { return m_type; }
             void v_set_type(String const& a_type) override     { m_type = a_type; }
        private:
             String m_type;
        };

    } // namespace local


    namespace remote
    {
        /*
        Object_Type_R
        ====================================================================================================
        Implementation of a remotely stored Object type
        */
        class Object_Type_R :
                public virtual IObject_Type_R
        {
        public:
            // Special 6
            //============================================================
           explicit  Object_Type_R(IObject_Type_R const& a_interface):
                IObject_Type_R(),
                mr_interface(a_interface)
            {}
            ~Object_Type_R() override = default;

        protected:
             String const& v_type() const override              { return mr_interface.type(); }
        private:
             IObject_Type_R const& mr_interface;
        };

        /*
        Object_Type_RW
        ====================================================================================================
        Implementation of a remotely stored Object type
        */
        class Object_Type_RW :
                public virtual IObject_Type_RW
        {
        public:
            // Special 6
            //============================================================
            explicit Object_Type_RW(IObject_Type_RW& a_interface):
                IObject_Type_RW(),
                mr_interface(a_interface)
            {}
            ~Object_Type_RW() override = default;

        protected:
             String const& v_type() const override              { return mr_interface.type(); }
             void v_set_type(String const& a_type) override     { mr_interface.set_type(a_type); }
        private:
             IObject_Type_RW& mr_interface;
        };

    } // namespace remote

} // namespace saklib

#endif // SAKLIB_OBJECT_TYPE_H

