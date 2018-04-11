#ifndef SAK_VARIANT_HPP
#define SAK_VARIANT_HPP

// This Header's Forward Header
//============================================================
#ifndef SAK_VARIANT_FWD_HPP
#include "variant_fwd.hpp"
#endif

// SAK Forwarding Headers
//============================================================
#ifndef SAK_NUMERIC_FWD_HPP
#include "numeric_fwd.hpp"
#endif

// SAK Headers
//============================================================
#ifndef SAK_DATA_TYPE_HPP
#include "data_type.hpp"
#endif

#ifndef SAK_ENTITY_ID_HPP
#include "entity_id.hpp"
#endif

#ifndef SAK_FILEPATH_HPP
#include "filepath.hpp"
#endif

#ifndef SAK_STRING_HPP
#include "string.hpp"
#endif

// Standard Headers
//============================================================
// It's there but msvc won't let me use it...
//#ifndef INCLUDE_STD_VARIANT
//#define INCLUDE_STD_VARIANT
//#include <variant>
//#endif

// Boost Headers
//============================================================
#ifndef INCLUDE_BOOST_VARIANT
#define INCLUDE_BOOST_VARIANT
#include <boost/variant.hpp>
#endif

namespace sak
{

  class Unknown_Type
  {
  public:
    Unknown_Type() = default;
  };
  //---------------------------------------------------------------------------
  // Variant
  //---------------------------------------------------------------------------
  // Class that can contain one of any of the values for Entity data members or
  // parts of those members, or may contain no value. A Variant that contains
  // no value is invalid.

  class Variant
  {
  private:
    // Data Members
    //============================================================
    Data_Type m_type;
    boost::variant
    <
    Unknown_Type,
    Bool,
    Int8,
    Int16,
    Int32,
    Int64,
    Uint8,
    Uint16,
    Uint32,
    Uint64,
    Float32,
    Float64,
    //ColourRGB,
    //ColourRGBA,
    String,
    Filepath,
    //Enumeration,
    Entity_ID
    > m_data;

  public:
    // Special 6
    //============================================================
    Variant();
    explicit Variant(Bool a_value);
    explicit Variant(Int8 a_value);
    explicit Variant(Int16 a_value);
    explicit Variant(Int32 a_value);
    explicit Variant(Int64 a_value);
    explicit Variant(Uint8 a_value);
    explicit Variant(Uint16 a_value);
    explicit Variant(Uint32 a_value);
    explicit Variant(Uint64 a_value);
    explicit Variant(Float32 a_value);
    explicit Variant(Float64 a_value);
    //explicit Variant(ColourRGB a_value);
    //explicit Variant(ColourRGBA a_value);
    explicit Variant(String const& a_value);
    explicit Variant(Filepath const& a_value);
    //explicit Variant(Enumeration const& a_value);
    explicit Variant(Entity_ID a_value);

    Variant(Variant const& a_other);
    Variant& operator=(Variant const& a_other);

    Variant(Variant && a_other);
    Variant& operator=(Variant && a_other);


    // Interface
    //============================================================
    bool is_valid() const noexcept;
    Data_Type type() const noexcept;

    Bool get_bool() const;
    Int8 get_int8() const;
    Int16 get_int16() const;
    Int32 get_int32() const;
    Int64 get_int64() const;
    Uint8 get_uint8() const;
    Uint16 get_uint16() const;
    Uint32 get_uint32() const;
    Uint64 get_uint64() const;
    Float32 get_float32() const;
    Float64 get_float64() const;
    //ColourRGB get_colour_rgb() const;
    //ColourRGBA get_colour_rgba() const;
    String get_string() const;
    Filepath get_filepath() const;
    //Enumeration get_enumeration() const;
    Entity_ID  get_entity_id() const;
  };
}

#endif // SAK_VARIANT_HPP
