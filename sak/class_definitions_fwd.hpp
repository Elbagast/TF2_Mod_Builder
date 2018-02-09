#ifndef SAK_CLASS_DEFINITIONS_FWD_HPP
#define SAK_CLASS_DEFINITIONS_FWD_HPP

namespace sak
{
  template <typename T_Data_Def, typename T_Name>
  class Member_Definition;

  template
  <
    typename T_Typestring,
    typename T_Typestring_Plural,
    typename T_Default_Name,
    typename T_Iconpath,
    typename...T_Member_Defs
  >
  class Class_Definition;

  class File_Definition;
  class Texture_Definition;
  class Material_Definition;
} // namespace sak

#endif // SAK_CLASS_DEFINITIONS_FWD_HPP
