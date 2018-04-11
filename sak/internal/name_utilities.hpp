#ifndef SAK_NAME_UTILITIES_HPP
#define SAK_NAME_UTILITIES_HPP

#ifndef SAK_STRING_FWD_HPP
#include "string_fwd.hpp"
#endif

// Standard Headers
//============================================================
#ifndef INCLUDE_STD_VECTOR
#define INCLUDE_STD_VECTOR
#include <vector>
#endif

namespace sak
{
  // Take the supplied name and alter it as necessary to be unique among the names that
  // are already in the supplied vector.
  void uniqueify_name(String& a_name, std::vector<String> const& a_names);
}

#endif // SAK_NAME_UTILITIES_HPP
