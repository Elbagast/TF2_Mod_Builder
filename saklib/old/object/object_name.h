#ifndef SAKLIB_OBJECT_NAME_H
#define SAKLIB_OBJECT_NAME_H

#include "iobject_name.h"

namespace saklib
{
    namespace local
    {
        /*
        Object_Name_R
        ====================================================================================================
        Implementation of a locally stored Object name
        */
        class Object_Name_R :
                public virtual IObject_Name_R
        {
        public:
            // Special 6
            //============================================================
            explicit Object_Name_R(String const& a_name):
                IObject_Name_R(),
                m_name(a_name)
            {}
            ~Object_Name_R() override = default;

        protected:
             String const& v_name() const override              { return m_name; }
        private:
             String m_name;
        };

        /*
        Object_Name_RW
        ====================================================================================================
        Implementation of a locally stored Object name
        */
        class Object_Name_RW :
                public virtual IObject_Name_RW
        {
        public:
            // Special 6
            //============================================================
            Object_Name_RW():
                IObject_Name_RW(),
                m_name()
            {}
            explicit Object_Name_RW(String const& a_name):
                IObject_Name_RW(),
                m_name(a_name)
            {}
            ~Object_Name_RW() override = default;

        protected:
             String const& v_name() const override              { return m_name; }
             void v_set_name(String const& a_name) override     { m_name = a_name; }
        private:
             String m_name;
        };

    } // namespace local


    namespace remote
    {
        /*
        Object_Name_R
        ====================================================================================================
        Implementation of a remotely stored Object name
        */
        class Object_Name_R :
                public virtual IObject_Name_R
        {
        public:
            // Special 6
            //============================================================
           explicit  Object_Name_R(IObject_Name_R const& a_interface):
                IObject_Name_R(),
                mr_interface(a_interface)
            {}
            ~Object_Name_R() override = default;

        protected:
             String const& v_name() const override              { return mr_interface.name(); }
        private:
             IObject_Name_R const& mr_interface;
        };

        /*
        Object_Name_RW
        ====================================================================================================
        Implementation of a remotely stored Object name
        */
        class Object_Name_RW :
                public virtual IObject_Name_RW
        {
        public:
            // Special 6
            //============================================================
            explicit Object_Name_RW(IObject_Name_RW& a_interface):
                IObject_Name_RW(),
                mr_interface(a_interface)
            {}
            ~Object_Name_RW() override = default;

        protected:
             String const& v_name() const override              { return mr_interface.name(); }
             void v_set_name(String const& a_name) override     { mr_interface.set_name(a_name); }
        private:
             IObject_Name_RW& mr_interface;
        };

    } // namespace remote

} // namespace saklib

#endif // SAKLIB_OBJECT_NAME_H

