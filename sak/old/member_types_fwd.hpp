#ifndef SAK_MEMBER_TYPES_FWD_HPP
#define SAK_MEMBER_TYPES_FWD_HPP

namespace sak
{
  // all of the types that members can be.
  // Mostly planning right now

  class Int8;
  class Int16;
  class Int32;
  class Int64;

  class Uint8;
  class Uit16;
  class Uint32;
  class Uint64;

  class Float32;
  class Float64;

  // Constrained versions of the above

  class ColourRGB;
  class ColourRGBA;

  // A string of any ascii characters
  class Ascii_String;
  // A string of any ascii characters that constitute readable text.
  // No control characters except newline.
  class Ascii_Text;
  // A string of any ascii characters that constitute readable text and fits on a line.
  // No control characters.
  class Ascii_Text_Line;

  // Same restrictions as ascii
  class Unicode_String;
  class Unicode_Text;
  class Unicode_Text_Line;

  class File_Name;
  class File_Path;

  class Directory_Name;
  class Directory_Path;



  class Valve_Bool;
  class Valve_Int;
  class Valve_Float;
  class Valve_String;
  class Valve_Colour;

}

#endif // SAK_MEMBER_TYPES_FWD_HPP
