#ifndef TYPE_TRAITS_H
#define TYPE_TRAITS_H

#include "types.h"

namespace Saklib
{
    /*
    Type_Traits<T>
    ====================================================================================================
    Class which contains functions relating to operations on T using std::string as the string
    class. This string class is regarded as the common data type.

    */
    template <typename T>
    struct Type_Traits
    {
    public:
        using stored_type = Undefined;
	    using value_type = stored_type;

        //static_assert(false, "Cannot instantiate Type_Traits<T> when template is not specialised.");

        static Type_Enum const type_enum_value{ Type_Enum::Undefined };

        static Type_Enum type_enum()
	    {
            return type_enum_value;
	    }
        static String type_string()
        {
            return "Undefined";
        }
	    static void set_to_default_value(stored_type& value)
	    {
		    value = stored_type();
	    }
    };

    template <typename T>
    using Type_Traits_st = typename Type_Traits<T>::stored_type;
    template <typename T>
    using Type_Traits_vt = typename Type_Traits<T>::value_type;
    

    /*
    TypeHolder<TypeID>
    ====================================================================================================
    Class which allows going from the enum value to the stored type without having to know specifically
    what the stored type is.

    */
    template <Type_Enum TE>
    struct TypeHolder
    {
        using traits_type = Type_Traits < Undefined >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const type_enum_value{ Type_Enum::Undefined };
    };

    template <Type_Enum TE>
    using TypeHolder_traits = typename TypeHolder<TE>::traits_type;
    template <Type_Enum TE>
    using TypeHolder_st = typename TypeHolder<TE>::stored_type;
    template <Type_Enum TE>
    using TypeHolder_vt = typename TypeHolder<TE>::value_type;

} // namespace Saklib

#endif // TYPE_TRAITS_H
