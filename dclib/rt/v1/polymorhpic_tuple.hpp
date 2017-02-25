#ifndef DCLIB_RT_V1_POLYMORHPIC_TUPLE_HPP
#define DCLIB_RT_V1_POLYMORHPIC_TUPLE_HPP

#include <tuple>
#include <memory>
#include <array>
#include <cassert>

namespace dclib
{
  namespace rt
  {
    namespace v1
    {
      // Derived classes are stored in a tuple and runtime access to the base class is
      // provided by an implementation of tuple indexing, which is potentially slow.
      template <typename T_Base, typename... Args>
      class polymorphic_tuple
      {
      public:
        using base_type = T_Base;
        using tuple_type = std::tuple<Args...>;

        template <std::size_t N>
        using derived_type = typename std::tuple_element<N,tuple_type>::type;

        polymorphic_tuple():
          m_tuple{}
        {}

        explicit polymorphic_tuple(tuple_type const& a_tuple):
          m_tuple{a_tuple}
        {}
        ~polymorphic_tuple() = default;

        polymorphic_tuple(polymorphic_tuple const& a_other) = default;
        polymorphic_tuple& operator=(polymorphic_tuple const& a_other) = default;

        polymorphic_tuple(polymorphic_tuple && a_other) = default;
        polymorphic_tuple& operator=(polymorphic_tuple && a_other) = default;

        base_type& get_base_at(std::size_t a_index)
        {
          return Tuple_Index_Binary_Search<>()(m_tuple,a_index);
        }

        base_type const& cget_base_at(std::size_t a_index) const
        {
          return Tuple_Index_Binary_Search_Constant<>()(m_tuple,a_index);
        }

        template <std::size_t I>
        base_type& get_base_at_alt()
        {
          return get_derived_at<I>();
        }

        template <std::size_t I>
        base_type const& cget_base_at_alt() const
        {
          return cget_derived_at<I>();
        }

        template <std::size_t I>
        derived_type<I>& get_derived_at()
        {
          return std::get<I>(m_tuple);
        }

        template <std::size_t I>
        derived_type<I> const& cget_derived_at() const
        {
          return std::get<I>(m_tuple);
        }

        static constexpr std::size_t size()
        {
          return s_end;
        }
      private:
        tuple_type m_tuple;

        static constexpr std::size_t const s_begin{ 0u };
        static constexpr std::size_t const s_end{ std::tuple_size<tuple_type>::value };

        template <std::size_t Index = s_begin, std::size_t End = s_end>
        struct Tuple_Index_Linear_Search
        {
          base_type& operator()(tuple_type& a_tuple, std::size_t a_index) const
          {
            assert(a_index >= s_begin);
            assert(a_index < s_end);
            if (a_index == Index)
            {
              return std::get<Index>(a_tuple);
            }
            else
            {
              return Tuple_Index_Linear_Search_Constant<Index+1>()(a_tuple, a_index);
            }
          }
        };

        template <std::size_t End>
        struct Tuple_Index_Linear_Search<End, End>
        {
          base_type& operator()(tuple_type& , std::size_t ) const
          {
            throw std::range_error("Bad member index.");
          }
        };

        template <std::size_t Index = s_begin, std::size_t End = s_end>
        struct Tuple_Index_Linear_Search_Constant
        {
          base_type const& operator()(tuple_type const& a_tuple, std::size_t a_index) const
          {
            assert(a_index >= s_begin);
            assert(a_index < s_end);
            if (a_index == Index)
            {
              return std::get<Index>(a_tuple);
            }
            else
            {
              return Tuple_Index_Linear_Search_Constant<Index+1>()(a_tuple, a_index);
            }
          }
        };

        template <std::size_t End>
        struct Tuple_Index_Linear_Search_Constant<End, End>
        {
          base_type const& operator()(tuple_type const& , std::size_t ) const
          {
            throw std::range_error("Bad member index.");
          }
        };


        template <std::size_t Min = s_begin, std::size_t Max = s_end>
        struct Tuple_Index_Binary_Search
        {
          template <std::size_t _Min, std::size_t _Max>
          struct Execute_Loop
          {
            base_type& operator()(tuple_type& a_tuple, std::size_t a_index) const
            {
              static constexpr std::size_t const s_mid{ _Min + ((_Max - _Min)/2) + ((_Max - _Min)%2) };
              if (a_index < s_mid)
              {
                static_assert(s_mid != _Max, "Range didn't shrink.");
                static_assert(s_mid < _Max, "Range didn't shrink.");
                return Tuple_Index_Binary_Search<_Min, s_mid>()(a_tuple, a_index);
              }
              else
              {
                static_assert(s_mid != _Min, "Range didn't shrink.");
                static_assert(s_mid > _Min, "Range didn't shrink.");
                return Tuple_Index_Binary_Search<s_mid, _Max>()(a_tuple, a_index);
              }
            }
          };
          template <std::size_t _Min, std::size_t _Max>
          struct Execute_End
          {
            base_type& operator()(tuple_type& a_tuple, std::size_t a_index) const
            {
              assert(a_index >= s_begin);
              assert(a_index < s_end);
              assert(a_index == _Min);
              if (a_index == _Min)
              {
                return static_cast<base_type&>(std::get<_Min>(a_tuple));
              }
              else
              {
                throw std::range_error("Bad member index.");
              }
            }
          };

          base_type& operator()(tuple_type& a_tuple, std::size_t a_index) const
          {
            assert(a_index >= s_begin);
            assert(a_index < s_end);
            // get a new midpoint that is halfway between Min and Max

            return typename std::conditional<Max == Min + 1, Execute_End<Min,Max>, Execute_Loop<Min,Max>>::type()(a_tuple, a_index);
          }
        };

        template <std::size_t Min = s_begin, std::size_t Max = s_end>
        struct Tuple_Index_Binary_Search_Constant
        {
          template <std::size_t _Min, std::size_t _Max>
          struct Execute_Loop
          {
            base_type const& operator()(tuple_type const& a_tuple, std::size_t a_index) const
            {
              static constexpr std::size_t const s_mid{ _Min + ((_Max-_Min)/2) + ((_Max-_Min)%2) };
              if (a_index < s_mid)
              {
                static_assert(s_mid != _Max, "Range didn't shrink.");
                static_assert(s_mid < _Max, "Range didn't shrink.");
                return Tuple_Index_Binary_Search_Constant<_Min, s_mid>()(a_tuple, a_index);
              }
              else
              {
                static_assert(s_mid != _Min, "Range didn't shrink.");
                static_assert(s_mid > _Min, "Range didn't shrink.");
                return Tuple_Index_Binary_Search_Constant<s_mid, _Max>()(a_tuple, a_index);
              }
            }
          };
          template <std::size_t _Min, std::size_t _Max>
          struct Execute_End
          {
            base_type const& operator()(tuple_type const& a_tuple, std::size_t a_index) const
            {
              assert(a_index >= s_begin);
              assert(a_index < s_end);
              assert(a_index == _Min);
              if (a_index == _Min)
              {
                return static_cast<base_type const&>(std::get<_Min>(a_tuple));
              }
              else
              {
                throw std::range_error("Bad member index.");
              }
            }
          };

          base_type const& operator()(tuple_type const& a_tuple, std::size_t a_index) const
          {
            assert(a_index >= s_begin);
            assert(a_index < s_end);
            // get a new midpoint that is halfway between Min and Max

            return typename std::conditional<Max == Min + 1, Execute_End<Min,Max>, Execute_Loop<Min,Max>>::type()(a_tuple, a_index);
          }
        };
      };

    } // namespace v1
  } // namespace rt
} // namespace dclib

#endif // DCLIB_RT_V1_POLYMORHPIC_TUPLE_HPP
