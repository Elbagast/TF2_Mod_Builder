#ifndef NAME_UTILITIES_HPP
#define NAME_UTILITIES_HPP

#include <vector>
class QString;

namespace sak
{
    // Take the supplied name and alter it as necessary to be unique among the names that
    // are already in the supplied vector.
    void uniqueify_name(QString& a_name, std::vector<QString> const& a_names);
}

#endif // NAME_UTILITIES_HPP
