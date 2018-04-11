#ifndef SAK_DATA_TYPE_HPP
#define SAK_DATA_TYPE_HPP

// This Header's Forward Header
//============================================================
#ifndef SAK_DATA_TYPE_FWD_HPP
#include "data_type_fwd.hpp"
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Data_Type
  //---------------------------------------------------------------------------
  // Enum for identifying the type of data stored in a Variant, and the type of
  // data stored in an entities data member.

  enum class Data_Type
  {
    Unknown = 0,

    Bool,           // constraints: default,
    Int8,           // constraints: default, min, max
    Int16,          // constraints: default, min, max
    Int32,          // constraints: default, min, max
    Int64,          // constraints: default, min, max
    Uint8,          // constraints: default, min, max
    Uint16,         // constraints: default, min, max
    Uint32,         // constraints: default, min, max
    Uint64,         // constraints: default, min, max
    Float32,        // constraints: default, min, max, significant figures
    Float64,        // constraints: default, min, max, significant figures
    ColourRGB,      // constraints: default
    ColourRGBA,     // constraints: default
    String,         // constraints: default, max length, ascii?, control chars?, whitespace?, blacklist chars?
    Filepath,           // constraints: default, ascii?, must pe partial or full?, whitespace?, file or directory?, filetype?
    Enumeration,    // constraints: default, int:string value pairs
    Entity_ID,      // constraints: default, must exist?, entity types/categories?

    Vector_Bool,    // constraints(all vectors): is array?, single element constraint
    Vector_Int8,
    Vector_Int16,
    Vector_Int32,
    Vector_Int64,
    Vector_Uint8,
    Vector_Uint16,
    Vector_Uint32,
    Vector_Uint64,
    Vector_Float32,
    Vector_Float64,
    Vector_ColourRGB,
    Vector_ColourRGBA,
    Vector_String,
    Vector_Filepath,
    Vector_Enumeration,
    Vector_Entity_ID,
  };

  // Is this a valid type? i.e. is equal to one of the enum values that
  // represent a data type. This accounts for invalid enum values.
  bool is_valid(Data_Type a_type) noexcept;

  // Inverse of is_valid.
  bool not_valid(Data_Type a_type) noexcept;

  // Is this a single value type?
  bool is_single_type(Data_Type a_type) noexcept;

  // Inverse of is_single_type.
  bool not_single_type(Data_Type a_type) noexcept;

  // Is this a vector of values type?
  bool is_vector_type(Data_Type a_type) noexcept;

  // Inverse of is_vector_type.
  bool not_vector_type(Data_Type a_type) noexcept;

  // Is this a type that stores entities?
  bool is_entity_type(Data_Type a_type) noexcept;

  // Inverse of is_entity_type.
  bool not_entity_type(Data_Type a_type) noexcept;

  // Get the data type of a vector type e.g. Data_Type::Vector_Bool results in
  // Data_Type::Bool. If the type supplied is not a vector type, the returned
  // value is Data_Type::Unknown.
  Data_Type vector_single_type(Data_Type a_type) noexcept;
}

#endif // SAK_DATA_TYPE_HPP
