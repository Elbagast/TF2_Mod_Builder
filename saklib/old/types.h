#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <vector>
#include <memory>
//#include "vector.h"

#ifndef Q_MOC_RUN
#define BOOST_FILESYSTEM_NO_DEPRECATED
#define BOOST_SYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
#endif // Q_MOC_RUN

namespace saklib
{
    /*
    class Undefined
    ====================================================================================================
    Dummy class to block instantiation of unspecialised Common_Traits templates
    */

    class Undefined
    {
    public:
        Undefined() = delete;
        ~Undefined() = delete;
        Undefined(Undefined const& other) = delete;
        Undefined& operator=(Undefined const& other) = delete;
        Undefined(Undefined && other) = delete;
        Undefined& operator=(Undefined && other) = delete;
    };

    /*
    Using Declarations
    ====================================================================================================
    Since this all recures so much, lets just put it all in a header so we don't have to repeat it all
    over the place.

    */

    // Utility
    using Char = char;
    using id_type = std::size_t;
    using size_type = std::size_t;

    inline id_type invalid_id() { return 0; }

    // Attribute Types
    using Bool = bool;
    using Int = int;
    using Double = double;
    //using String = std::basic_string < Char >;  // can't forward declare
    using String = std::string;  // can't forward declare
    using Path = boost::filesystem::path;
    class ElementID;
    class AttributeID;
    class ProxyID;
    /*
    // String Conversions
    inline String to_String(size_type value)        { return std::to_string(value); }

    inline String to_String(Bool value)             { return std::to_string(value); }
    inline String to_String(Int value)              { return std::to_string(value); }
    inline String to_String(Double value)           { return std::to_string(value); }
    inline String to_String(String const& value)    { return value; }                   // kinda pointless, but here for consistency
    inline String to_String(Path const& value)      { return value.string(); }
    //inline String to_String(ElementID const& value);

    inline Bool to_Bool(String const& value)        { return std::stoi(value) > 0 ? true : false; }
    inline Int to_Int(String const& value)          { return std::stoi(value); }
    inline Double to_Double(String const& value)    { return std::stod(value); }
    //inline String to_String(String const& value)    { return value; }
    inline Path to_Path(String const& value)        { return Path(value); }
    //inline ElementID to_ElementID(String const& value);
    */
    /*
    Type_Enum
    ====================================================================================================
    All configured data types get a value in this enum for external type-checking.

    */
    enum class Type_Enum : int
    {
        Undefined = 0,

        First_Simple_Type,
        Bool = First_Simple_Type,
        Int,
        Double,
        String,
        Path,
        ElementID,
        Last_Simple_Type = ElementID,

        First_Vector_Type,
        Vector_Bool = First_Vector_Type,
        Vector_Int,
        Vector_Double,
        Vector_String,
        Vector_Path,
        Vector_ElementID,
        Last_Vector_Type = Vector_ElementID
    };

    inline bool is_simple_type(Type_Enum type) { return type >= Type_Enum::First_Simple_Type && type <= Type_Enum::Last_Simple_Type; }
    inline bool is_vector_type(Type_Enum type) { return type >= Type_Enum::First_Vector_Type && type <= Type_Enum::Last_Vector_Type; }

    inline bool is_element_type(Type_Enum type) { return type == Type_Enum::ElementID || type == Type_Enum::Vector_ElementID; }
    
} // namespace saklib

#endif // TYPES_H
