#ifndef SAK_ABSTRACT_SIGNAL_HPP
#define SAK_ABSTRACT_SIGNAL_HPP

#ifndef SAK_ABSTRACT_SIGNAL_FWD_HPP
#include "abstract_signal_fwd.hpp"
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Abstract_Signal
  //---------------------------------------------------------------------------
  // Base class for all Project signals. It has enough information to identify
  // its true type, which holds enough data to process the signal.

  // change:
  // Class to wrap the idendity of a signal and the Entityit acts on. If the
  // signal

  class Abstract_Signal
  {
  private:
    // Data Members
    //============================================================
    Signal_Source m_source;
    Signal_Type m_type;

  public:
    // Special 6
    //============================================================
    Abstract_Signal(Signal_Source a_source, Signal_Type a_type);
    virtual ~Abstract_Signal() = 0;

    // Interface
    //============================================================
    Signal_Source source() const noexcept;
    Signal_Type type() const noexcept;
  };

  //---------------------------------------------------------------------------
  // Signal_Source
  //---------------------------------------------------------------------------
  // Enum for identifying the origin of a signal.
  enum class Signal_Source
  {
    Unknown,

    System,
    User,
    Editor,
    Outliner,
    Redo,
    Undo
  };

  //---------------------------------------------------------------------------
  // Signal_Type
  //---------------------------------------------------------------------------
  // Enum for identifying a signal's true type.

  enum class Signal_Type
  {
    Unknown,

    Entity_Outliner_Request,
    Entity_Editor_Request,

    Entity_Added,
    Entity_Removed,

    Entity_Name_Changed
  };
/*
  // Determine if something like this is even necessary...
  enum class Data_Type
  {
    Invalid = 0,

    Bool = 1 << 0,
    Int8 = 1 << 1,
    Int16 = 1 << 2,
    Int32 = 1 << 3,
    Int64 = 1 << 4,
    UInt8 = 1 << 5,
    UInt16 = 1 << 6,
    UInt32 = 1 << 7,
    UInt64 = 1 << 8,
    Float32 = 1 << 9,
    Float64 = 1 << 10,
    ColourRGB = 1 << 11,
    ColourRGBA = 1 << 12,
    Ascii_String = 1 << 13,
    Unicode_String = 1 << 14,
    Ascii_Path = 1 << 15,
    Unicode_Path = 1 << 16,
    Entity_ID = 1 << 17,

    Array_Flag = 1 << 30,
    Vector_Flag = 1 << 31,

    Array_Bool = (Data_Type::Bool |= Data_Type::Array_Flag),
    Array_Int8 = (Int8 |= Array_Flag),
    Array_Int16 = (Int16 |= Array_Flag),
    Array_Int32 = (Int32 |= Array_Flag),
    Array_Int64 = (Int64 |= Array_Flag),
    Array_UInt8 = (UInt8 |= Array_Flag),
    Array_UInt16 = (UInt16 |= Array_Flag),
    Array_UInt32 = (UInt32 |= Array_Flag),
    Array_UInt64 = (UInt64 |= Array_Flag),
    Array_Float32 = (Float32 |= Array_Flag),
    Array_Float64 = (Float64 |= Array_Flag),
    Array_ColourRGB = (ColourRGB |= Array_Flag),
    Array_ColourRGBA = (ColourRGBA |= Array_Flag),
    Array_Ascii_String = (Ascii_String |= Array_Flag),
    Array_Unicode_String = (Unicode_String |= Array_Flag),
    Array_Entity_ID = (Entity_ID |= Array_Flag),

    Vector_Bool = (Bool |= Vector_Flag),
    Vector_Int8 = (Int8 |= Vector_Flag),
    Vector_Int16 = (Int16 |= Vector_Flag),
    Vector_Int32 = (Int32 |= Vector_Flag),
    Vector_Int64 = (Int64 |= Vector_Flag),
    Vector_UInt8 = (UInt8 |= Vector_Flag),
    Vector_UInt16 = (UInt16 |= Vector_Flag),
    Vector_UInt32 = (UInt32 |= Vector_Flag),
    Vector_UInt64 = (UInt64 |= Vector_Flag),
    Vector_Float32 = (Float32 |= Vector_Flag),
    Vector_Float64 = (Float64 |= Vector_Flag),
    Vector_ColourRGB = (ColourRGB |= Vector_Flag),
    Vector_ColourRGBA = (ColourRGBA |= Vector_Flag),
    Vector_Ascii_String = (Ascii_String |= Vector_Flag),
    Vector_Unicode_String = (Unicode_String |= Vector_Flag),
    Vector_Entity_ID = (Entity_ID |= Vector_Flag)

  };

  bool is_simple(Data_Type a_type) noexcept;
  bool is_array(Data_Type a_type) noexcept;
  bool is_vector(Data_Type a_type) noexcept;

  bool is_entity(Data_Type a_type) noexcept;
  bool is_entity_array(Data_Type a_type) noexcept;
  bool is_entity_vector(Data_Type a_type) noexcept;
*/
}

#endif // SAK_ABSTRACT_SIGNAL_HPP
