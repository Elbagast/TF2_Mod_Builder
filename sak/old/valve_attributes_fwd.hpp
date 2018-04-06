#ifndef SAK_VALVE_ATTRIBUTES_FWD_HPP
#define SAK_VALVE_ATTRIBUTES_FWD_HPP

namespace sak
{
  // Valve filenames and dirnames can only contain the following characters:
  // a...z,A...Z,0...9,_,-
  class Valve_Filename;
  class Valve_Dirname;

  // Made up of valid directry names seperated by '/'. '\' is automatically replaced
  // with '/' on input completion.
  class Valve_Filepath;
  class Valve_Dirpath;

  class Valve_Buildpath;

  class Valve_Bool;
  class Valve_Int;
  class Valve_Float;
  class Valve_ColourRGB;
  class Valve_ColourRGBA;
  class Valve_String;
}

#endif // SAK_VALVE_ATTRIBUTES_FWD_HPP
