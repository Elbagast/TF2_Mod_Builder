#include "data_type.hpp"

// Is this a valid type? i.e. is equal to one of the enum values that
// represent a data type. This accounts for invalid enum values.
bool sak::is_valid(Data_Type a_type) noexcept
{
  switch(a_type)
  {
    case Data_Type::Bool:               return true;
    case Data_Type::Int8:               return true;
    case Data_Type::Int16:              return true;
    case Data_Type::Int32:              return true;
    case Data_Type::Int64:              return true;
    case Data_Type::Uint8:              return true;
    case Data_Type::Uint16:             return true;
    case Data_Type::Uint32:             return true;
    case Data_Type::Uint64:             return true;
    case Data_Type::Float32:            return true;
    case Data_Type::Float64:            return true;
    case Data_Type::ColourRGB:          return true;
    case Data_Type::ColourRGBA:         return true;
    case Data_Type::String:             return true;
    case Data_Type::Filepath:               return true;
    case Data_Type::Enumeration:        return true;
    case Data_Type::Entity_ID:          return true;
    case Data_Type::Vector_Bool:        return true;
    case Data_Type::Vector_Int8:        return true;
    case Data_Type::Vector_Int16:       return true;
    case Data_Type::Vector_Int32:       return true;
    case Data_Type::Vector_Int64:       return true;
    case Data_Type::Vector_Uint8:       return true;
    case Data_Type::Vector_Uint16:      return true;
    case Data_Type::Vector_Uint32:      return true;
    case Data_Type::Vector_Uint64:      return true;
    case Data_Type::Vector_Float32:     return true;
    case Data_Type::Vector_Float64:     return true;
    case Data_Type::Vector_ColourRGB:   return true;
    case Data_Type::Vector_ColourRGBA:  return true;
    case Data_Type::Vector_String:      return true;
    case Data_Type::Vector_Filepath:        return true;
    case Data_Type::Vector_Enumeration: return true;
    case Data_Type::Vector_Entity_ID:   return true;
    default:                            return false;
  }
}

// Inverse of is_valid.
bool sak::not_valid(Data_Type a_type) noexcept
{
  return !is_valid(a_type);
}

// Is this a single value type?
bool sak::is_single_type(Data_Type a_type) noexcept
{
  switch(a_type)
  {
    case Data_Type::Bool:               return true;
    case Data_Type::Int8:               return true;
    case Data_Type::Int16:              return true;
    case Data_Type::Int32:              return true;
    case Data_Type::Int64:              return true;
    case Data_Type::Uint8:              return true;
    case Data_Type::Uint16:             return true;
    case Data_Type::Uint32:             return true;
    case Data_Type::Uint64:             return true;
    case Data_Type::Float32:            return true;
    case Data_Type::Float64:            return true;
    case Data_Type::ColourRGB:          return true;
    case Data_Type::ColourRGBA:         return true;
    case Data_Type::String:             return true;
    case Data_Type::Filepath:               return true;
    case Data_Type::Enumeration:        return true;
    case Data_Type::Entity_ID:          return true;
    default:                            return false;
  }
}

// Inverse of is_single_type.
bool sak::not_single_type(Data_Type a_type) noexcept
{
  return !is_single_type(a_type);
}

// Is this a vector of values type?
bool sak::is_vector_type(Data_Type a_type) noexcept
{
  switch(a_type)
  {
    case Data_Type::Vector_Bool:        return true;
    case Data_Type::Vector_Int8:        return true;
    case Data_Type::Vector_Int16:       return true;
    case Data_Type::Vector_Int32:       return true;
    case Data_Type::Vector_Int64:       return true;
    case Data_Type::Vector_Uint8:       return true;
    case Data_Type::Vector_Uint16:      return true;
    case Data_Type::Vector_Uint32:      return true;
    case Data_Type::Vector_Uint64:      return true;
    case Data_Type::Vector_Float32:     return true;
    case Data_Type::Vector_Float64:     return true;
    case Data_Type::Vector_ColourRGB:   return true;
    case Data_Type::Vector_ColourRGBA:  return true;
    case Data_Type::Vector_String:      return true;
    case Data_Type::Vector_Filepath:        return true;
    case Data_Type::Vector_Enumeration: return true;
    case Data_Type::Vector_Entity_ID:   return true;
    default:                            return false;
  }
}

// Inverse of is_vector_type.
bool sak::not_vector_type(Data_Type a_type) noexcept
{
  return !is_vector_type(a_type);
}

// Is this a type that stores entities?
bool sak::is_entity_type(Data_Type a_type) noexcept
{
  switch(a_type)
  {
    case Data_Type::Entity_ID:        return true;
    case Data_Type::Vector_Entity_ID: return true;
    default:                          return false;
  }
}

// Inverse of is_entity_type.
bool sak::not_entity_type(Data_Type a_type) noexcept
{
  return !is_entity_type(a_type);
}

// Get the data type of a vector type e.g. Data_Type::Vector_Bool results in
// Data_Type::Bool. If the type supplied is not a vector type, the returned
// value is Data_Type::Unknown.
sak::Data_Type sak::vector_single_type(Data_Type a_type) noexcept
{
  switch(a_type)
  {
    case Data_Type::Vector_Bool:        return Data_Type::Bool;
    case Data_Type::Vector_Int8:        return Data_Type::Int8;
    case Data_Type::Vector_Int16:       return Data_Type::Int16;
    case Data_Type::Vector_Int32:       return Data_Type::Int32;
    case Data_Type::Vector_Int64:       return Data_Type::Int64;
    case Data_Type::Vector_Uint8:       return Data_Type::Uint8;
    case Data_Type::Vector_Uint16:      return Data_Type::Uint16;
    case Data_Type::Vector_Uint32:      return Data_Type::Uint32;
    case Data_Type::Vector_Uint64:      return Data_Type::Uint64;
    case Data_Type::Vector_Float32:     return Data_Type::Float32;
    case Data_Type::Vector_Float64:     return Data_Type::Float64;
    case Data_Type::Vector_ColourRGB:   return Data_Type::ColourRGB;
    case Data_Type::Vector_ColourRGBA:  return Data_Type::ColourRGBA;
    case Data_Type::Vector_String:      return Data_Type::String;
    case Data_Type::Vector_Filepath:        return Data_Type::Filepath;
    case Data_Type::Vector_Enumeration: return Data_Type::Enumeration;
    case Data_Type::Vector_Entity_ID:   return Data_Type::Entity_ID;
    default:                            return Data_Type::Unknown;
  }
}
