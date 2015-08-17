#ifndef SMART_HANDLE_MANAGER_H
#define SMART_HANDLE_MANAGER_H

#include "handle.h"
#include "handle_factory.h"
#include "smart_handle.h"

namespace datalib
{
    template <typename T>
    class Example_Handle_Factory
    {
    public:
        // Typedefs
        //============================================================
        using handle_type = Handle<T>;

        // Interface
        //============================================================
        handle_type make_null_handle() const;
        handle_type make_new_handle();
        void revoke_handle(handle_type const& handle);
    };

    template <typename H, typename T>
    class Example_Data_Storage
    {
    public:
        // Typedefs
        //============================================================
        using handle_type = H;
        using data_type = T;

        using data_stored_type = T;
        using data_return_type = T&;
        using data_const_return_type = T const&;
        using reference_count_type = std::size_t;

        // Interface
        //============================================================
        void emplace_data(handle_type const& handle, data_stored_type&& data);
        bool is_null(handle_type const& handle) const;
        bool is_valid(handle_type const& handle) const;
        bool has_data(handle_type const& handle) const;
        data_return_type data(handle_type const& handle);
        data_const_return_type cdata(handle_type const& handle) const;
        reference_count_type reference_count(handle_type const& handle) const;
        void increment_reference_count(handle_type const& handle);
        bool decrement_reference_count(handle_type const& handle);

        static reference_count_type reference_count_zero();
    };



    template <typename T,
              template <typename> class Member_Handle_Factory,
              template <typename, typename> class Member_Data_Storage,
              typename Pre_Destructor>
    class Smart_Handle_Manager
    {
    public:
        // Typedefs
        //============================================================
        using data_type = T;
        using handle_type = Handle<data_type>;

        using handle_factory_type = Member_Handle_Factory<data_type>;

        using data_storage_type = Member_Data_Storage<data_type, Pre_Destructor>;

        using data_stored_type = typename data_storage_type::data_stored_type;
        using data_return_type = typename data_storage_type::data_return_type;
        using data_const_return_type = typename data_storage_type::data_const_return_type;
        using reference_count_type = typename data_storage_type::reference_count_type;

        using smart_handle_type = typename Smart_Handle < Smart_Handle_Manager >;

        ~Smart_Handle_Manager()
        {
            //std::cout << "manager destructor" << std::endl;
        }


        // Interface
        //============================================================
        smart_handle_type make_null_handle()
        {
            return smart_handle_type(this, m_id_factory.make_null_handle());
        }

        smart_handle_type emplace_data(data_stored_type&& data)
        {
            handle_type new_handle = m_id_factory.make_new_handle();
            m_storage.emplace_data(new_handle, std::forward<data_stored_type>(data));
            return smart_handle_type(this, new_handle);
        }

        bool has_data(handle_type const& handle) const
        {
            return m_storage.has_data(handle);
        }

        data_return_type data(handle_type const& handle)
        {
            return m_storage.data(handle);
        }

        data_const_return_type cdata(handle_type const& handle) const
        {
            return m_storage.cdata(handle);
        }

        reference_count_type reference_count(handle_type const& handle) const
        {
            return m_storage.reference_count(handle);
        }

        bool is_null(handle_type const& handle) const
        {
            return m_storage.is_null(handle);
        }

        bool is_valid(handle_type const& handle) const
        {
            return m_storage.has_data(handle);
        }

        void increment_reference_count(handle_type const& handle)
        {
            return m_storage.increment_reference_count(handle);
        }

        void decrement_reference_count(handle_type const& handle)
        {
            //std::cout << "decrement: H=" << handle.underlying_value() << " RC=" << reference_count(handle) << std::endl;
            if (m_storage.decrement_reference_count(handle))
            {
                m_id_factory.revoke_handle(handle);
            }
            //std::cout << "decrement end: H=" << handle.underlying_value() << " RC=" << reference_count(handle) << std::endl<< std::endl;
        }

        //constexpr
        static reference_count_type reference_count_max()
        {
            return data_storage_type::reference_count_max();
        }

        //constexpr
        static reference_count_type reference_count_zero()
        {
            return data_storage_type::reference_count_zero();
        }

    private:
        data_storage_type m_storage;
        handle_factory_type m_id_factory;
    };

} // namespace datalib

#endif // SMART_HANDLE_MANAGER_H

