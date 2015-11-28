#ifndef COMMON_TRAITS_H
#define COMMON_TRAITS_H

#include "types.h"
#include "elementid.h"

#define COMMON_TRAITS_TYPEDEFS_T \
    using stored_type = typename saklib::Common_Traits<T>::stored_type; \
    using value_type = typename saklib::Common_Traits<T>::value_type; \
    \
    using stored_type_const_arg = typename saklib::Common_Traits<T>::stored_type_const_arg; \
    using stored_type_const_return = typename saklib::Common_Traits<T>::stored_type_const_return; \
    \
    using value_type_const_arg = typename saklib::Common_Traits<T>::value_type_const_arg; \
    using value_type_const_return = typename saklib::Common_Traits<T>::value_type_const_return;

#define COMMON_TRAITS_TYPEDEFS(t_type) \
    using stored_type = saklib::Common_Traits<t_type>::stored_type; \
    using value_type = saklib::Common_Traits<t_type>::value_type; \
    \
    using stored_type_const_arg = saklib::Common_Traits<t_type>::stored_type_const_arg; \
    using stored_type_const_return = saklib::Common_Traits<t_type>::stored_type_const_return; \
    \
    using value_type_const_arg = saklib::Common_Traits<t_type>::value_type_const_arg; \
    using value_type_const_return = saklib::Common_Traits<t_type>::value_type_const_return;


namespace saklib
{
    /*
    Common_Traits<T>
    ====================================================================================================
    Class which contains functions relating to operations on T using std::string as the string
    class. This string class is regarded as the common data type.

    */
    template <typename T>
    struct Common_Traits
    {
    public:
        using stored_type = Undefined;
        using value_type = stored_type;

        using stored_type_const_arg = Undefined const&;
        using stored_type_const_return = Undefined const&;

        using value_type_const_arg = Undefined const&;
        using value_type_const_return = Undefined const&;

        //static_assert(false, "Cannot instantiate Common_Traits<T> when template is not specialised.");
        static bool const is_specialised{ false };
        static bool const is_specialized{ false };

        static Type_Enum const type_enum_value{ Type_Enum::Undefined };

        static Type_Enum type_enum()                            { return type_enum_value; }
        static String type_string()                             { return "Undefined"; }
        static void set_to_default_value(stored_type& value)    { value = stored_type(); }
        static stored_type make_default_value()                 { return stored_type(); }
    };

    template <typename T>
    using Common_Traits_st = typename Common_Traits<T>::stored_type;
    template <typename T>
    using Common_Traits_vt = typename Common_Traits<T>::value_type;
    

    /*
    Type_Holder<TypeID>
    ====================================================================================================
    Class which allows going from the enum value to the stored type without having to know specifically
    what the stored type is.

    */
    template <Type_Enum TE>
    struct Type_Holder
    {
        using traits_type = Common_Traits < Undefined >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const type_enum_value{ Type_Enum::Undefined };
    };

    template <Type_Enum TE>
    using Type_Holder_traits = typename Type_Holder<TE>::traits_type;
    template <Type_Enum TE>
    using Type_Holder_st = typename Type_Holder<TE>::stored_type;
    template <Type_Enum TE>
    using Type_Holder_vt = typename Type_Holder<TE>::value_type;



    /*
    Common_Traits<Bool> and Common_Traits<Vector<Bool>>
    ====================================================================================================
    */
    template <>
    struct Common_Traits<Bool>
    {
    public:
        using stored_type = Bool;
        using value_type = stored_type;

        using stored_type_const_arg = stored_type;
        using stored_type_const_return = stored_type;

        using value_type_const_arg = value_type;
        using value_type_const_return = value_type;

        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static Type_Enum const type_enum_value{ Type_Enum::Bool };

        static Type_Enum type_enum()                            { return type_enum_value; }
        static String type_string()                             { return "Bool"; }
        static void set_to_default_value(stored_type& value)    { value = false; }
        static stored_type make_default_value()                 { return stored_type(false); }
    };

    template <>
    struct Type_Holder<Type_Enum::Bool>
    {
        using traits_type = Common_Traits < Bool >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const typeid_value{ Type_Enum::Int };
    };

    template <>
    struct Common_Traits<std::vector<Bool>>
    {
    public:
        using stored_type = std::vector<Bool>;
        using value_type = Bool;

        using stored_type_const_arg = stored_type const&;
        using stored_type_const_return = stored_type const&;

        using value_type_const_arg = value_type;
        using value_type_const_return = value_type;

        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static Type_Enum const type_enum_value{ Type_Enum::Vector_Bool };

        static Type_Enum type_enum()                            { return type_enum_value; }
        static String type_string()                             { return "Vector_Bool"; }
        static void set_to_default_value(stored_type& value)    { value.clear(); }
        static stored_type make_default_value()                 { return stored_type(); }
    };

    template <>
    struct Type_Holder<Type_Enum::Vector_Bool>
    {
        using traits_type = Common_Traits < std::vector<Bool> >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const type_enum_value{ Type_Enum::Vector_Bool };
    };



    /*
    Common_Traits<Int> and Common_Traits<Vector<Int>>
    ====================================================================================================
    */
    template <>
    struct Common_Traits<Int>
    {
    public:
        using stored_type = Int;
        using value_type = stored_type;

        using stored_type_const_arg = stored_type;
        using stored_type_const_return = stored_type;

        using value_type_const_arg = value_type;
        using value_type_const_return = value_type;

        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static Type_Enum const type_enum_value{ Type_Enum::Int };

        static Type_Enum type_enum()                            { return type_enum_value; }
        static String type_string()                             { return "Int"; }
        static void set_to_default_value(stored_type& value)    { value = 0; }
        static stored_type make_default_value()                 { return stored_type(0); }
    };

    template <>
    struct Type_Holder<Type_Enum::Int>
    {
        using traits_type = Common_Traits < Int >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const typeid_value{ Type_Enum::Int };
    };

    template <>
    struct Common_Traits<std::vector<Int>>
    {
    public:
        using stored_type = std::vector<Int>;
        using value_type = Int;

        using stored_type_const_arg = stored_type const&;
        using stored_type_const_return = stored_type const&;

        using value_type_const_arg = value_type;
        using value_type_const_return = value_type;

        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static Type_Enum const type_enum_value{ Type_Enum::Vector_Int };

        static Type_Enum type_enum()                            { return type_enum_value; }
        static String type_string()                             { return "Vector_Int"; }
        static void set_to_default_value(stored_type& value)    { value.clear(); }
        static stored_type make_default_value()                 { return stored_type(); }
    };

    template <>
    struct Type_Holder<Type_Enum::Vector_Int>
    {
        using traits_type = Common_Traits < std::vector<Int> >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const type_enum_value{ Type_Enum::Vector_Int };
    };



    /*
    Common_Traits<Double> and Common_Traits<Vector<Double>>
    ====================================================================================================
    */
    template <>
    struct Common_Traits<Double>
    {
    public:
        using stored_type = Double;
        using value_type = stored_type;

        using stored_type_const_arg = stored_type;
        using stored_type_const_return = stored_type;

        using value_type_const_arg = value_type;
        using value_type_const_return = value_type;

        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static Type_Enum const type_enum_value{ Type_Enum::Double };

        static Type_Enum type_enum()                            { return type_enum_value; }
        static String type_string()                             { return "Double"; }
        static void set_to_default_value(stored_type& value)    { value = 0.0; }
        static stored_type make_default_value()                 { return stored_type(0.0); }
    };

    template <>
    struct Type_Holder<Type_Enum::Double>
    {
        using traits_type = Common_Traits < Double >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const typeid_value{ Type_Enum::Double };
    };

    template <>
    struct Common_Traits<std::vector<Double>>
    {
    public:
        using stored_type = std::vector<Double>;
        using value_type = Double;

        using stored_type_const_arg = stored_type const&;
        using stored_type_const_return = stored_type const&;

        using value_type_const_arg = value_type;
        using value_type_const_return = value_type;

        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static Type_Enum const type_enum_value{ Type_Enum::Vector_Double };

        static Type_Enum type_enum()                            { return type_enum_value; }
        static String type_string()                             { return "Vector_Double"; }
        static void set_to_default_value(stored_type& value)    { value.clear(); }
        static stored_type make_default_value()                 { return stored_type(); }
    };

    template <>
    struct Type_Holder<Type_Enum::Vector_Double>
    {
        using traits_type = Common_Traits < std::vector<Double> >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const type_enum_value{ Type_Enum::Vector_Double };
    };



    /*
    Common_Traits<String> and Common_Traits<Vector<String>>
    ====================================================================================================
    */
    template <>
    struct Common_Traits<String>
    {
    public:
        using stored_type = String;
        using value_type = stored_type;

        using stored_type_const_arg = stored_type const&;
        using stored_type_const_return = stored_type const&;

        using value_type_const_arg = value_type const&;
        using value_type_const_return = value_type const&;

        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static Type_Enum const type_enum_value{ Type_Enum::String };

        static Type_Enum type_enum()                            { return type_enum_value; }
        static String type_string()                             { return "String"; }
        static void set_to_default_value(stored_type& value)    { value.clear(); }
        static stored_type make_default_value()                 { return stored_type(); }
    };

    template <>
    struct Type_Holder<Type_Enum::String>
    {
        using traits_type = Common_Traits < String >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const typeid_value{ Type_Enum::String };
    };

    template <>
    struct Common_Traits<std::vector<String>>
    {
    public:
        using stored_type = std::vector<String>;
        using value_type = String;

        using stored_type_const_arg = stored_type const&;
        using stored_type_const_return = stored_type const&;

        using value_type_const_arg = value_type const&;
        using value_type_const_return = value_type const&;

        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static Type_Enum const type_enum_value{ Type_Enum::Vector_String };

        static Type_Enum type_enum()                            { return type_enum_value; }
        static String type_string()                             { return "Vector_String"; }
        static void set_to_default_value(stored_type& value)    { value.clear(); }
        static stored_type make_default_value()                 { return stored_type(); }
    };

    template <>
    struct Type_Holder<Type_Enum::Vector_String>
    {
        using traits_type = Common_Traits < std::vector<String> >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const type_enum_value{ Type_Enum::Vector_String };
    };




    /*
    Common_Traits<Path> and Common_Traits<Vector<Path>>
    ====================================================================================================
    */
    template <>
    struct Common_Traits<Path>
    {
    public:
        using stored_type = Path;
        using value_type = stored_type;

        using stored_type_const_arg = stored_type const&;
        using stored_type_const_return = stored_type const&;

        using value_type_const_arg = value_type const&;
        using value_type_const_return = value_type const&;

        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static Type_Enum const type_enum_value{ Type_Enum::Path };

        static Type_Enum type_enum()                            { return type_enum_value; }
        static String type_string()                             { return "Path"; }
        static void set_to_default_value(stored_type& value)    { value.clear(); }
        static stored_type make_default_value()                 { return stored_type(); }
    };

    template <>
    struct Type_Holder<Type_Enum::Path>
    {
        using traits_type = Common_Traits < Path >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const typeid_value{ Type_Enum::Path };
    };

    template <>
    struct Common_Traits<std::vector<Path>>
    {
    public:
        using stored_type = std::vector<Path>;
        using value_type = Path;

        using stored_type_const_arg = stored_type const&;
        using stored_type_const_return = stored_type const&;

        using value_type_const_arg = value_type const&;
        using value_type_const_return = value_type const&;

        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static Type_Enum const type_enum_value{ Type_Enum::Vector_Path };

        static Type_Enum type_enum()                            { return type_enum_value; }
        static String type_string()                             { return "Vector_Path"; }
        static void set_to_default_value(stored_type& value)    { value.clear(); }
        static stored_type make_default_value()                 { return stored_type(); }
    };

    template <>
    struct Type_Holder<Type_Enum::Vector_Path>
    {
        using traits_type = Common_Traits < std::vector<Path> >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const type_enum_value{ Type_Enum::Vector_Path };
    };




    /*
    Common_Traits<ElementID> and Common_Traits<Vector<ElementID>>
    ====================================================================================================
    */
    template <>
    struct Common_Traits<ElementID>
    {
    public:
        using stored_type = ElementID;
        using value_type = stored_type;

        using stored_type_const_arg = stored_type const&;
        using stored_type_const_return = stored_type const&;

        using value_type_const_arg = value_type const&;
        using value_type_const_return = value_type const&;

        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static Type_Enum const type_enum_value{ Type_Enum::ElementID };

        static Type_Enum type_enum()                            { return type_enum_value; }
        static String type_string()                             { return "ElementID"; }
        static void set_to_default_value(stored_type& value)    { value = ElementID(); }
        static stored_type make_default_value()                 { return stored_type(); }
    };

    template <>
    struct Type_Holder<Type_Enum::ElementID>
    {
        using traits_type = Common_Traits < ElementID >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const typeid_value{ Type_Enum::ElementID };
    };

    template <>
    struct Common_Traits<std::vector<ElementID>>
    {
    public:
        using stored_type = std::vector<ElementID>;
        using value_type = ElementID;

        using stored_type_const_arg = stored_type const&;
        using stored_type_const_return = stored_type const&;

        using value_type_const_arg = value_type const&;
        using value_type_const_return = value_type const&;

        static bool const is_specialised{ true };
        static bool const is_specialized{ true };

        static Type_Enum const type_enum_value{ Type_Enum::Vector_ElementID };

        static Type_Enum type_enum()                            { return type_enum_value; }
        static String type_string()                             { return "Vector_ElementID"; }
        static void set_to_default_value(stored_type& value)    { value.clear(); }
        static stored_type make_default_value()                 { return stored_type(); }
    };

    template <>
    struct Type_Holder<Type_Enum::Vector_ElementID>
    {
        using traits_type = Common_Traits < std::vector<ElementID> >;
        using stored_type = traits_type::stored_type;
        using value_type = traits_type::value_type;
        static Type_Enum const type_enum_value{ Type_Enum::Vector_ElementID };
    };


} // namespace saklib

#endif // COMMON_TRAITS_H
