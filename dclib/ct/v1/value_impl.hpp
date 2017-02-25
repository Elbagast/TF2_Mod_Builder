#ifndef DCLIB_CT_V1_VALUE_IMPL_HPP
#define DCLIB_CT_V1_VALUE_IMPL_HPP

namespace dclib
{
  namespace ct
  {
    namespace v1
    {
      //---------------------------------------------------------------------------
      // value_impl<Name, T>
      //---------------------------------------------------------------------------
      // Implementation of standardised access to a stored value or any type.

      template <typename T>
      class value_impl
      {
      public:
        using value_type = T;

        value_impl():
           m_value{}
        {
        }

        explicit value_impl(value_type const& a_value):
          m_value{a_value}
        {
        }

        explicit value_impl(value_type&& a_value):
          m_value{std::move(a_value)}
        {
        }

        value_type& get()
        {
          return m_value;
        }

        value_type const& cget() const
        {
          return m_value;
        }

      private:
        value_type m_value;
      };


    } // namespace v1
  } // namespace ct
} // namespace dclib

#endif // DCLIB_CT_V1_VALUE_IMPL_HPP
