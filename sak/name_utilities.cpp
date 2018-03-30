#include "name_utilities.hpp"

#include <algorithm>
#include <limits>

// Take the supplied name and alter it as necessary to be unique among the names that
// are already in the supplied vector.
void sak::uniqueify_name(std::string& a_name, std::vector<std::string> const& a_names)
{
  auto l_name_found = std::find(a_names.cbegin(), a_names.cend(), a_name);

  // if it was found we have to edit it.
  if (l_name_found != a_names.cend())
  {
    // append a number to the name and test it and keep doing this until we get to one we haven't found.
    for (int l_postfix = 1, l_end = std::numeric_limits<int>::max(); l_postfix != l_end; ++l_postfix)
    {
      std::string l_fixed_name{a_name};
      l_fixed_name += std::to_string(l_postfix);
      if (std::find(a_names.cbegin(), a_names.cend(), l_fixed_name) == a_names.cend())
      {
        a_name = l_fixed_name;
        break;
      }
    }
  }
}
