#ifndef FLOAT_CLASS_HPP
#define FLOAT_CLASS_HPP

#include "fwd/float_class.hpp"
#include <type_traits>

namespace dclib
{
  namespace litype
  {
    namespace v1
    {
      //---------------------------------------------------------------------------
      // floating_point<T, Mantissa, Exponent, Sign>
      //---------------------------------------------------------------------------
      // Class that wraps a float literal making it useable as a template parameter
      // type.

      using float_mantissa_type = unsigned long long;
      using float_exponent_type = int;
      using float_sign_type = bool;

      template
      <
          typename T_Float
         ,float_mantissa_type Mantissa
         ,float_exponent_type Exponent
         ,float_sign_type Sign
      >
      class floating_point
      {
        static_assert(std::is_floating_point<T_Float>::value,
                      "Attempted to instantiate Floating_Point_Literal_Type with a T_Float argument that was not a floating point type. "
                      "You may only use the types 'float', 'double', or 'long double'.");
      public:
        using this_type = floating_point<T_Float, Mantissa, Exponent, Sign>;
        using value_type = T_Float;
        using mantissa_type = float_mantissa_type;
        using exponent_type = float_exponent_type;
        using sign_type = float_sign_type;

        // Return the float value at runtime.
        static value_type value() noexcept
        {
          return s_value;
        }

        // Return the templated mantissa value at compile or runtime.
        static constexpr mantissa_type mantissa() noexcept
        {
          return s_mantissa;
        }

        // Return the templated exponent value at compile or runtime.
        static constexpr exponent_type exponent() noexcept
        {
          return s_exponent;
        }

        // Return the templated sign bit value at compile or runtime.
        static constexpr sign_type sign() noexcept
        {
          return s_sign;
        }

      private:
        static value_type const s_value;
        static constexpr mantissa_type s_mantissa{ Mantissa };
        static constexpr exponent_type s_exponent{ Exponent };
        static constexpr sign_type s_sign{ Sign };
      };

      // is this even used?
      /*
      template
      <
        typename T_Float_Target
       ,typename T_Float
       ,float_mantissa_type Mantissa
       ,float_exponent_type Exponent
       ,float_sign_type Sign
      >
      T_Float_Target float_compiletime_cast(floating_point<T_Float,Mantissa,Exponent,Sign> )
      {
        return floating_point<T_Float_Target,Mantissa,Exponent,Sign>::value();
      }
      */
    } // namespace v1
  } // namespace litype
} // namespace dclib


template
<
    typename T_Float
   ,dclib::litype::v1::float_mantissa_type Mantissa
   ,dclib::litype::v1::float_exponent_type Exponent
   ,dclib::litype::v1::float_sign_type Sign
>
typename dclib::litype::v1::floating_point<T_Float,Mantissa,Exponent,Sign>::value_type const dclib::litype::v1::floating_point<T_Float,Mantissa,Exponent,Sign>::s_value = { dclib::litype::v1::make_float_type<value_type>(Mantissa, Exponent, Sign) };




#endif // FLOAT_CLASS_HPP
