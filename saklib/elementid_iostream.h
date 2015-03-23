#ifndef ELEMENTID_IOSTREAM_H
#define ELEMENTID_IOSTREAM_H

#include <iosfwd>

namespace Saklib
{
    class ElementID;

    std::ostream& operator<<(std::ostream& stream, ElementID id);
    std::istream& operator>>(std::istream& stream, ElementID id);
} // namespace Saklib

#endif // ELEMENTID_IOSTREAM_H
