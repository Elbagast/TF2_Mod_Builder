﻿#ifndef SAK_NAME_UTILITIES_HPP
#define SAK_NAME_UTILITIES_HPP

#ifndef INCLUDE_STD_VECTOR
#define INCLUDE_STD_VECTOR
#include <vector>
#endif

#ifndef INCLUDE_STD_STRING
#define INCLUDE_STD_STRING
#include <string>
#endif

namespace sak
{
  // Take the supplied name and alter it as necessary to be unique among the names that
  // are already in the supplied vector.
  void uniqueify_name(std::string& a_name, std::vector<std::string> const& a_names);
}

#endif // SAK_NAME_UTILITIES_HPP
