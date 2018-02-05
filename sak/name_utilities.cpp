#include "name_utilities.hpp"

#include <QString>
#include <algorithm>
#include <limits>

// Take the supplied name and alter it as necessary to be unique among the names that
// are already in the supplied vector.
void sak::uniqueify_name(QString& a_name, std::vector<QString> const& a_names)
{
  auto l_name_found = std::find(a_names.cbegin(), a_names.cend(), a_name);

  // if it wasn't found we can use it
  if (l_name_found != a_names.cend())
  {
    // append a number to the name and test it and keep doing this until we get to one we haven't found.
    for (int l_postfix = 1, l_end = std::numeric_limits<int>::max(); l_postfix != l_end; ++l_postfix)
    {
      QString l_fixed_name{a_name};
      l_fixed_name.append(QString::number(l_postfix));
      if (std::find(a_names.cbegin(), a_names.cend(), l_fixed_name) == a_names.end())
      {
          a_name = l_fixed_name;
          break;
      }
    }
  }
}
