#ifndef SAK_NAME_UTILITIES_HPP
#define SAK_NAME_UTILITIES_HPP

#ifndef INCLUDE_STD_VECTOR
#define INCLUDE_STD_VECTOR
#include <vector>
#endif

class QString;

namespace sak
{
  // Take the supplied name and alter it as necessary to be unique among the names that
  // are already in the supplied vector.
  void uniqueify_name(QString& a_name, std::vector<QString> const& a_names);
}

#endif // SAK_NAME_UTILITIES_HPP
