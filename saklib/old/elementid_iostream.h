#ifndef ELEMENTID_IOSTREAM_H
#define ELEMENTID_IOSTREAM_H

#include <iosfwd>

namespace saklib
{
    class ElementID;

    std::ostream& operator<<(std::ostream& stream, ElementID id);
    std::istream& operator>>(std::istream& stream, ElementID id);
} // namespace saklib

#endif // ELEMENTID_IOSTREAM_H
