#ifndef SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_SHARED_DATA
#define SAKLIB_INTERNAL_ATTRIBUTE_DATA_HANDLE_SHARED_DATA


#ifndef INCLUDE_STD_CSTDDEF
#define INCLUDE_STD_CSTDDEF
#include <cstddef>
#endif

namespace saklib
{
    namespace internal
    {
        template <typename M>
        class Attribute_Data_Handle_Shared_Data
        {
        public:
            // Typedefs
            //============================================================
            using manager_type = M;
            using reference_counter_type = typename manager_type::reference_counter_type;
            using handle_type = typename reference_counter_type::handle_type;
            using storage_type = typename reference_counter_type::storage_type;

            // Special 6
            //============================================================
            Attribute_Data_Handle_Shared_Data();
            Attribute_Data_Handle_Shared_Data(manager_type& ar_manager, reference_counter_type const& a_reference_counter, std::size_t a_index);
            Attribute_Data_Handle_Shared_Data(manager_type& ar_manager, reference_counter_type&& a_reference_counter, std::size_t a_index);
            ~Attribute_Data_Handle_Shared_Data();

            Attribute_Data_Handle_Shared_Data(Attribute_Data_Handle_Shared_Data const& other);
            Attribute_Data_Handle_Shared_Data& operator=(Attribute_Data_Handle_Shared_Data const& other);

            Attribute_Data_Handle_Shared_Data(Attribute_Data_Handle_Shared_Data && other);
            Attribute_Data_Handle_Shared_Data& operator=(Attribute_Data_Handle_Shared_Data && other);

            // Interface
            //============================================================
            bool is_valid() const;
            bool is_null() const;

            handle_type cget_element_handle() const;
            std::size_t cget_element_reference_count() const;

            std::size_t cget_attribute_index() const;

            manager_type& get_manager();
            manager_type const& cget_manager() const;

            // Comparison Operators
            //============================================================
            bool operator==(Attribute_Data_Handle const& rhs);
            bool operator!=(Attribute_Data_Handle const& rhs);
            bool operator<(Attribute_Data_Handle const& rhs);
            bool operator>(Attribute_Data_Handle const& rhs);
            bool operator<=(Attribute_Data_Handle const& rhs);
            bool operator>=(Attribute_Data_Handle const& rhs);

            // Comparison Operators for compare to the null handle
            //============================================================
            bool operator==(Null_Handle_Type const& rhs);
            bool operator!=(Null_Handle_Type const& rhs);

        private:
            // Data Members
            //============================================================
            manager_type* mp_manager;
            reference_counter_type m_reference_counter;
            std::size_t m_attribute_index;
        };
    } // namespace internal
} // namespace saklib


#endif // ATTRIBUTE_DATA_HANDLE_SHARED_DATA

