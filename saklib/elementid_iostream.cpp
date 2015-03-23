#include "elementid_iostream.h"
#include "elementid.h"

std::ostream& Saklib::operator<<(std::ostream& stream, ElementID id)
{
    stream << id.value();
    return stream;
}

std::istream& Saklib::operator>>(std::istream& stream, ElementID id)
{
    return stream;
}
