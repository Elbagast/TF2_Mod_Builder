#ifndef SAKLIB_INTERNAL_PROPERTY_H
#define SAKLIB_INTERNAL_PROPERTY_H

#ifndef SAKLIB_INTERNAL_PROPERTY__FWD_H
#include "property__fwd.h"
#endif

namespace saklib
{
    namespace internal
    {
        enum class Location
        {
            Local,
            Remote
        };

        enum class Access
        {
            Read,
            Write
        };


        template <typename T>
        class Property_Name
        {
        public:
            using string_type = T;
            using return_type = T const&;

            return_type operator()() const
            {
                static string_type const s_data{ "Property_Name" };
                return s_data;
            }
        };

        template <typename F_Name, typename T, typename T_Arg, typename T_Return>
        class Property <F_Name, Location::Local, Access::Read, T>
        {
        public:
            using name_type = F_Name;
            using name_string_type = typename name_type::string_type;
            using name_return_type = typename name_type::name_return_type;
            using data_type = T;
            using data_arg_type = T_Arg;
            using data_return_type = T_Return;

            Property();
            Property(data_arg_type a_data);

            name_return_type cget_name() const;

            data_return_type cget_data() const;

        private:
            name_type m_name;
            data_type m_data;
        };

        template <typename F_Name, typename T, typename T_Arg, typename T_Return>
        class Property <F_Name, Location::Local, Access::Write, T>
        {
        public:
            using name_type = F_Name;
            using name_string_type = typename name_type::string_type;
            using name_return_type = typename name_type::name_return_type;
            using data_type = T;
            using data_arg_type = T_Arg;
            using data_return_type = T_Return;

            Property();
            explicit Property(data_arg_type a_data);

            name_return_type cget_name() const;

            data_return_type cget_data() const;
            void set_data(data_arg_type a_data) const;

        private:
            name_type m_name;
            data_type m_data;
        };

        template <typename F_Name, typename T, typename T_Arg, typename T_Return>
        class Property <F_Name, Location::Remote, Access::Read, T>
        {
        public:
            using name_type = F_Name;
            using name_string_type = typename name_type::string_type;
            using name_return_type = typename name_type::name_return_type;
            using data_type = T;
            using data_arg_type = T_Arg;
            using data_return_type = T_Return;

            explicit Property(Property <F_Name, Location::Local, Access::Read, T> const& ar_local_read);
            explicit Property(Property <F_Name, Location::Local, Access::Write, T> const& ar_local_write);
            explicit Property(Property <F_Name, Location::Remote, Access::Read, T> const& ar_remote_read);
            explicit Property(Property <F_Name, Location::Remote, Access::Write, T> const& ar_remote_write);

            name_return_type cget_name() const;

            data_return_type cget_data() const;

        private:
            union Reference_Union
            {
                Property <F_Name, Location::Local, Access::Read, T> const& mr_local_read;
                Property <F_Name, Location::Local, Access::Write, T> const& mr_local_write;
                Property <F_Name, Location::Remote, Access::Read, T> const& mr_remote_read;
                Property <F_Name, Location::Remote, Access::Write, T> const& mr_remote_write;
            };
            Reference_Union m_union;
        };

        template <typename F_Name, typename T, typename T_Arg, typename T_Return>
        class Property <F_Name, Location::Local, Access::Write, T>
        {
        public:
            using name_type = F_Name;
            using name_string_type = typename name_type::string_type;
            using name_return_type = typename name_type::name_return_type;
            using data_type = T;
            using data_arg_type = T_Arg;
            using data_return_type = T_Return;

            explicit Property(Property <F_Name, Location::Local, Access::Write, T> const& ar_local_write);
            explicit Property(Property <F_Name, Location::Remote, Access::Write, T> const& ar_remote_write);

            name_return_type cget_name() const;

            data_return_type cget_data() const;
            void set_data(data_arg_type a_data) const;

        private:
            union Reference_Union
            {
                Property <F_Name, Location::Local, Access::Write, T> const& mr_local_write;
                Property <F_Name, Location::Remote, Access::Write, T> const& mr_remote_write;
            };
            Reference_Union m_union;
        };

    } // namespace internal
} // namespace saklib


#ifndef SAKLIB_INTERNAL_PROPERTY__INLINE_H
#include "property__inline.h"
#endif

#endif // SAKLIB_INTERNAL_PROPERTY_H

